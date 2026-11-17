include_guard(GLOBAL)

cmake_minimum_required(VERSION 3.24.0)

cmake_policy(SET CMP0097 NEW) # Policy for GIT_SUBMODULES with empty arguments - won't download submodules when cloning

# Turn off searching of CMAKE_INSTALL_PREFIX during calls to find_package
set(CMAKE_FIND_USE_INSTALL_PREFIX OFF CACHE BOOL "Disables find_package searching in CMAKE_INSTALL_PREFIX for dependencies")

find_package(Git REQUIRED)
include("shacl_FetchContent/relative_git_url")
include("shacl_FetchContent/directory_git_info")

include(FetchContent)

# The wrapped FetchContent_MakeAvailable function only adds print statements
# for CMake clone progress and to aid in debugging dependency origins and keep user
# informed when lots of clones are happening
macro(shacl_FetchContent_MakeAvailable_impl name)

  # Check if package was already found or if its source directory was specified.
  # If so, don't print diagnostic info.
  # Note - if a package specifies by hand any of these variables in its cmake
  # then the diagnostics may not get printed properly (i.e. pybind11)
  FetchContent_GetProperties(${name} POPULATED ${name}_pre_makeavailable_fetched)
  if (${name}_FOUND)
    set(${name}_pre_makeavailable_found TRUE)
  else()
    set(${name}_pre_makeavailable_found FALSE)
  endif()

  # Check if source directory was specified
  # FETCHCONTENT uses upper-case names for some variables
  string(TOUPPER ${name} uname)
  if("${FETCHCONTENT_SOURCE_DIR_${uname}}" STREQUAL "")
    set(sourceDirNotSpecified TRUE)
  else()
    set(sourceDirNotSpecified FALSE)
  endif()

  set(${name}_already_found ${${name}_pre_makeavailable_fetched} OR ${${name}_pre_makeavailable_found})

  if (${sourceDirNotSpecified} AND NOT (${${name}_already_found}}))
    message(STATUS "Finding or fetching and configuring ${name}")
  endif()

  FetchContent_MakeAvailable(${name})

  FetchContent_GetProperties(${name} 
    SOURCE_DIR ${name}_source_dir
    POPULATED ${name}_post_makeavailable_found
  )

  # It's possible that ${name}_post_makeavailable_found is TRUE because the package was found via find_package.
  # In that case ${name}_source_dir was not defined.  
  # If both ${name}_post_makeavailable_found is TRUE and ${name}_source_dir was defined then the package was fetched.
  set(${name}_post_makeavailable_found ${${name}_post_makeavailable_found} AND DEFINED ${name}_source_dir)
  
  if (${name_FOUND})
    if (${${name}_FOUND})
      set(${name}_found_via_find_package TRUE)
    else()
      set(${name}_found_via_find_package FALSE)
    endif()
  else()
    set(${name}_found_via_find_package FALSE)
  endif()

  if (NOT (${${name}_already_found}}))
    if( ${${name}_post_makeavailable_found} AND NOT ${${name}_found_via_find_package} )
      message(STATUS "${name} fetched and configured")
      # If Git information exists for the source directory then print and save it into cache variables
      # This enables printing even when FETCHCONTENT_SOURCE_DIR_${NAME} was defined and is a git repo
      cmake_path(APPEND ${name}_source_dir .git OUTPUT_VARIABLE ${name}_git_path)
      message(STATUS "  ${name} source dir: ${${name}_source_dir}")
      if (EXISTS ${${name}_git_path})
        get_git_info_for_directory(${${name}_source_dir} return_url return_hash return_branch)
        message(STATUS "  ${name} repository: ${return_url}")
        message(STATUS "  ${name} branch/tag: ${return_branch}")
        message(STATUS "  ${name} hash:       ${return_hash}")

        # Set cache variables and mark them as "ro" to indicate they're read-only
        set(shacl_FetchContent.${name}.repository.ro ${return_url} CACHE STRING "The repository of ${name} that was fetched. Read only." FORCE)
        set(shacl_FetchContent.${name}.tag.ro ${return_branch} CACHE STRING "The branch/tag of ${name} that was fetched, HEAD if hash was fetched. Read only." FORCE)
        set(shacl_FetchContent.${name}.hash.ro ${return_hash} CACHE STRING "The hash of ${name} that was fetched. Read only." FORCE)
        mark_as_advanced(shacl_FetchContent.${name}.repository.ro)
        mark_as_advanced(shacl_FetchContent.${name}.tag.ro)
        mark_as_advanced(shacl_FetchContent.${name}.hash.ro)
      else()
        message(STATUS "  ${name} repository information not available.")
      endif()

    elseif (${name}_FOUND)
      message(STATUS "${name} found via installation and configured")
      message(STATUS "  ${name} dir: ${${name}_DIR}")
    endif()
  endif()

endmacro()

macro(shacl_FetchContent_MakeAvailable)
  foreach(name ${ARGN})
    shacl_FetchContent_MakeAvailable_impl(${name})
  endforeach()
endmacro()


# The purpose of the wrapped FetchContent_Declare function is twofold:
# * Enabling relative GIT_REPOSITORY URLs to aid in automated testing or different host servers
# * Adding the appropriate arguments to FetchContent_Declare to avoid finding the dependency from different sources
function(shacl_FetchContent_Declare name)

  # FETCHCONTENT uses upper-case names for some variables
  string(TOUPPER ${name} uname)
  # Disable automatic post-fetch updates on a reconfigure for each package
  set(FETCHCONTENT_UPDATES_DISCONNECTED_${uname} ON CACHE BOOL "Enables UPDATE_DISCONNECTED just for population of ${name}")

  # Option to enable force fetching via configuration
  option(shacl_FetchContent.${name}.override_find_package "Force fetch of ${name} instead of first calling find_package" OFF)
  # Option to enable force finding of pckages for use in spack installations via configuration
  option(shacl_FetchContent.force_find_package "Disable fetching of all packages found via shacl_FetchContent by only using find_package instead" OFF)

  # copy argument list as methods like list(FIND...) don't work on ${ARGV}
  set (args ${ARGV})

  # Find where FIND_PACKAGE_ARGS is present in argument list (-1 if not present)
  list(FIND args FIND_PACKAGE_ARGS find_pkg_index)
  list(FIND args OVERRIDE_FIND_PACKAGE override_pkg_index)

  # If override_find_package (force fetching) is turned on then always fetch, never find.
  # If force fetching then first remove FIND_PACKAGE_ARGS and all of the arguments.
  # Then specify OVERRIDE_FIND_PACKAGE to force future calls to find_package to find the fetched version.
  # If not force fetching then specify FIND_PACKAGE_ARGS if it wasn't present in the argument list to 
  # first attempt finding the dependency via a call to find_paackage before trying to fetch it.
  # FIND_PACKAGE_ARGS also ensures that if the dependency was fetched then future calls to find_package will find the fetched dependency.
  # If OVERRIDE_FIND_PACKAGE was specified in FetchContent_Declare then FIND_PACKAGE_ARGS is not added 
  if (${shacl_FetchContent.${name}.override_find_package})
    # Ignore everything after FIND_PACKAGE_ARGS
    # FIND_PACKAGE_ARGS and its associated args must come at the end of 
    # the FetchContent_Declare function call so we can safely ignore everything after it
    # if ${find_pkg_index} is -1 then arg_subset is equal to args
    list(SUBLIST args 0 ${find_pkg_index} arg_subset)
    # if OVERRIDE_FIND_PACKAGE is not present then add it
    if (${override_pkg_index} EQUAL -1)
      list(APPEND arg_subset OVERRIDE_FIND_PACKAGE)
      list(FIND arg_subset OVERRIDE_FIND_PACKAGE override_pkg_index)
    endif()
  else() # if not force fetching then call find_package first
    set(arg_subset ${args})
    # if FIND_PACKAGE_ARGS is not present and OVERRIDE_FIND_PACKAGE was not specified then add FIND_PACKAGE_ARGS
    if (${find_pkg_index} EQUAL -1 AND ${override_pkg_index} EQUAL -1)
      list(APPEND arg_subset FIND_PACKAGE_ARGS)
    endif()
  endif()

  if (shacl_FetchContent.force_find_package)
    if(NOT override_pkg_index EQUAL -1)
      message(FATAL_ERROR "shacl_FetchContent - cannot use OVERRIDE_FIND_PACKAGE in conjunction with shacl_Fetchcontent.force_find_package")
    endif()
    list(APPEND arg_subset REQUIRED)
  endif()

  # If the dependency uses a relative path then it uses the same server as the host project.
  # This is useful for automated testing with gitlab CI tokens or if repos are hosted on different servers
  # e.g. if the project is hosted on github then pull all relative dependencies from github.

  # Find the GIT_REPOSITORY keyword then increment index to point to associated value.
  list(FIND arg_subset GIT_REPOSITORY git_repository_index)
  math(EXPR git_repository_index "${git_repository_index}+1")
  list(GET arg_subset ${git_repository_index} git_repository_url)

  # Update the git URL if it was a relative URL, otherwise return it unchanged.
  get_dependency_url(${git_repository_url} updated_url)

  # If the .git directory does not exist, then cmake will fail to resolve a relative url and throw an error.
  # In that case replace the relative URL with a value to avoid the error and force the use of find_package.
  if( NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/.git")
     if( "${updated_url}" MATCHES "^\\./|^\\.\\./" )
        message( WARNING "Could not find local .git directory to resolve a relative url, forcing the use of find_package")
        set( shacl_FetchContent.force_find_package ON )
        list(APPEND arg_subset REQUIRED)
        set( updated_url "unresolved_relative_url.git" )
     endif()
  endif()

  list(REMOVE_AT arg_subset ${git_repository_index})
  list(INSERT arg_subset ${git_repository_index} ${updated_url})

  FetchContent_Declare(${arg_subset})

endfunction()

# Installation of shacl_FetchContent module
if(shacl.cmake.installation)
  get_property(
    shacl.cmake.installed_modules GLOBAL PROPERTY shacl.cmake.installed_modules)

  if(NOT "Git/Submodule/Packages" IN_LIST shacl.cmake.installed_modules)
    set_property(GLOBAL APPEND PROPERTY
      shacl.cmake.installed_modules "shacl_FetchContent")

    install(FILES "${CMAKE_CURRENT_LIST_FILE}"
      DESTINATION share/cmake/shacl/.cmake)

    install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/shacl_FetchContent"
      DESTINATION share/cmake/shacl/.cmake)
  endif()

  unset(shacl.cmake.installed_modules)
endif()

