
cmake_minimum_required( VERSION 3.2 )
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if ( NOT GIT_EXECUTABLE )
    find_package( Git 2.1 )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp 3.4 )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpreter installation was not found." )
            endif()
        endif()
        execute_process( COMMAND ${PYTHON_EXECUTABLE} "./metaconfigure/fetch_subprojects.py"
                         WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                         RESULT_VARIABLE fetch_failure )
        if ( NOT fetch_failure )
            set( fetched_subprojects TRUE CACHE BOOL "fetch script ran" )
        else()
            message( FATAL_ERROR "Failed to fetch dependencies" )
        endif()
    endif()
endif()

if( NOT is_subproject )
    if( NOT ROOT_DIRECTORY )
        set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    endif()
    if ( NOT PYTHON_EXECUTABLE )
        find_package( PythonInterp )
        if ( NOT PYTHONINTERP_FOUND )
            message( FATAL_ERROR "Python interpreter installation was not found." )
        endif()
    endif()
    execute_process( COMMAND ${PYTHON_EXECUTABLE} ./metaconfigure/signature.py ${CMAKE_BINARY_DIR}/signature
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE signature_failure )
    file( READ "${CMAKE_BINARY_DIR}/signature.json" SIGNATURE )
endif()

project( ENDFtk LANGUAGES CXX )
get_directory_property( is_subproject PARENT_DIRECTORY )
include( CMakeDependentOption REQUIRED )

set( ENDFtk_AppleClang_minimum_version 8.0 )
set( ENDFtk_GNU_minimum_version 6.2 )
set( ENDFtk_Clang_minimum_version 3.8 )

if( ENDFtk_${CMAKE_CXX_COMPILER_ID}_minimum_version )
    if( CMAKE_CXX_COMPILER_VERSION AND
        CMAKE_CXX_COMPILER_VERSION VERSION_LESS
        ${ENDFtk_${CMAKE_CXX_COMPILER_ID}_minimum_version} )
        message( FATAL_ERROR "${CMAKE_CXX_COMPILER_ID} version must be greater than ${ENDFtk_${CMAKE_CXX_COMPILER_ID}_minimum_version}" )
    endif()
endif()

# general properties
option( ENDFtk_strict "Compile time warnings are converted to errors" ON )

# binary instrumentation
option( coverage "Enable binary instrumentation to collect test coverage information in the DEBUG configuration" )
option( profile_generate "Enable binary instrumentation to generation execution profiles in the RELEASE configuration which may be used to guide later optimization" )

# additional optimizations
option( link_time_optimization "Enable link time optimization in the RELEASE configuration" )
option( profile_use "In the RELEASE configuration, leverage previously generated execution profile to inform optimization decisions" )
option( nonportable_optimization "Enable optimizations which compromise portability of resulting binary in the RELEASE configuration" )

# libraries and linking
option( static "Statically link component and environment libraries" OFF )
if ( static AND ( "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin" ) )
    message( FATAL_ERROR "Static binaries not supported on OSX" )
endif()

CMAKE_DEPENDENT_OPTION( static_libraries "Statically link component libraries" OFF "NOT static" ON )

option( unit_tests "Compile the ENDFtk unit tests and integrate with ctest" ON ) 

if ( profile_generate AND profile_use )
    message( FATAL_ERROR "Cannot both generate and use execution profile in the same configuration" )
endif()

if ( profile_generate )
    file( MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/profiling" )
endif()

set( ENDFtk_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_AppleClang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ENDFtk_AppleClang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_AppleClang_Darwin_strict_flags "-Werror" )
set( ENDFtk_AppleClang_Darwin_coverage_flags "--coverage" )
set( ENDFtk_AppleClang_Darwin_subproject_flags  )
set( ENDFtk_AppleClang_Darwin_base_project_flags  )
set( ENDFtk_AppleClang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_AppleClang_Darwin_link_time_optimization_flags "-flto" )
set( ENDFtk_AppleClang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_AppleClang_Darwin_nonportable_optimization_flags "-march=native" )
set( ENDFtk_AppleClang_Darwin_static_flags "-static" )
set( ENDFtk_GNU_Linux_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_GNU_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_GNU_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_GNU_Linux_strict_flags "-Werror" )
set( ENDFtk_GNU_Linux_coverage_flags "--coverage" )
set( ENDFtk_GNU_Linux_subproject_flags  )
set( ENDFtk_GNU_Linux_base_project_flags  )
set( ENDFtk_GNU_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Linux_link_time_optimization_flags "-flto" )
set( ENDFtk_GNU_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Linux_nonportable_optimization_flags "-march=native" )
set( ENDFtk_GNU_Linux_static_flags "-static" )
set( ENDFtk_GNU_Darwin_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_GNU_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_GNU_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_GNU_Darwin_strict_flags "-Werror" )
set( ENDFtk_GNU_Darwin_coverage_flags "--coverage" )
set( ENDFtk_GNU_Darwin_subproject_flags  )
set( ENDFtk_GNU_Darwin_base_project_flags  )
set( ENDFtk_GNU_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Darwin_link_time_optimization_flags "-flto" )
set( ENDFtk_GNU_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Darwin_nonportable_optimization_flags "-march=native" )
set( ENDFtk_GNU_Darwin_static_flags "-static" )
set( ENDFtk_GNU_Windows_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_GNU_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_GNU_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_GNU_Windows_strict_flags "-Werror" )
set( ENDFtk_GNU_Windows_coverage_flags "--coverage" )
set( ENDFtk_GNU_Windows_subproject_flags  )
set( ENDFtk_GNU_Windows_base_project_flags  )
set( ENDFtk_GNU_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Windows_link_time_optimization_flags "-flto" )
set( ENDFtk_GNU_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_Windows_nonportable_optimization_flags "-march=native" )
set( ENDFtk_GNU_Windows_static_flags "-static" )
set( ENDFtk_GNU_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( ENDFtk_GNU_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_GNU_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_GNU_CYGWIN_strict_flags "-Werror" )
set( ENDFtk_GNU_CYGWIN_coverage_flags "--coverage" )
set( ENDFtk_GNU_CYGWIN_subproject_flags  )
set( ENDFtk_GNU_CYGWIN_base_project_flags  )
set( ENDFtk_GNU_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_CYGWIN_link_time_optimization_flags "-flto" )
set( ENDFtk_GNU_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_CYGWIN_nonportable_optimization_flags "-march=native" )
set( ENDFtk_GNU_CYGWIN_static_flags "-static" )
set( ENDFtk_GNU_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_GNU_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_GNU_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_GNU_MinGW_strict_flags "-Werror" )
set( ENDFtk_GNU_MinGW_coverage_flags "--coverage" )
set( ENDFtk_GNU_MinGW_subproject_flags  )
set( ENDFtk_GNU_MinGW_base_project_flags  )
set( ENDFtk_GNU_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_MinGW_link_time_optimization_flags "-flto" )
set( ENDFtk_GNU_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_GNU_MinGW_nonportable_optimization_flags "-march=native" )
set( ENDFtk_GNU_MinGW_static_flags "-static" )
set( ENDFtk_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_Clang_Linux_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ENDFtk_Clang_Linux_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_Clang_Linux_strict_flags "-Werror" )
set( ENDFtk_Clang_Linux_coverage_flags "--coverage" )
set( ENDFtk_Clang_Linux_subproject_flags  )
set( ENDFtk_Clang_Linux_base_project_flags  )
set( ENDFtk_Clang_Linux_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Linux_link_time_optimization_flags "-flto" )
set( ENDFtk_Clang_Linux_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Linux_nonportable_optimization_flags "-march=native" )
set( ENDFtk_Clang_Linux_static_flags "-static" )
set( ENDFtk_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_Clang_Darwin_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ENDFtk_Clang_Darwin_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_Clang_Darwin_strict_flags "-Werror" )
set( ENDFtk_Clang_Darwin_coverage_flags "--coverage" )
set( ENDFtk_Clang_Darwin_subproject_flags  )
set( ENDFtk_Clang_Darwin_base_project_flags  )
set( ENDFtk_Clang_Darwin_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Darwin_link_time_optimization_flags "-flto" )
set( ENDFtk_Clang_Darwin_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Darwin_nonportable_optimization_flags "-march=native" )
set( ENDFtk_Clang_Darwin_static_flags "-static" )
set( ENDFtk_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_Clang_Windows_DEBUG_flags "-O0" "-g" "-gdwarf-3" )
set( ENDFtk_Clang_Windows_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_Clang_Windows_strict_flags "-Werror" )
set( ENDFtk_Clang_Windows_coverage_flags "--coverage" )
set( ENDFtk_Clang_Windows_subproject_flags  )
set( ENDFtk_Clang_Windows_base_project_flags  )
set( ENDFtk_Clang_Windows_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Windows_link_time_optimization_flags "-flto" )
set( ENDFtk_Clang_Windows_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_Windows_nonportable_optimization_flags "-march=native" )
set( ENDFtk_Clang_Windows_static_flags "-static" )
set( ENDFtk_Clang_CYGWIN_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=gnu++17" )
set( ENDFtk_Clang_CYGWIN_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_Clang_CYGWIN_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_Clang_CYGWIN_strict_flags "-Werror" )
set( ENDFtk_Clang_CYGWIN_coverage_flags "--coverage" )
set( ENDFtk_Clang_CYGWIN_subproject_flags  )
set( ENDFtk_Clang_CYGWIN_base_project_flags  )
set( ENDFtk_Clang_CYGWIN_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_CYGWIN_link_time_optimization_flags "-flto" )
set( ENDFtk_Clang_CYGWIN_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_CYGWIN_nonportable_optimization_flags "-march=native" )
set( ENDFtk_Clang_CYGWIN_static_flags "-static" )
set( ENDFtk_Clang_MinGW_common_flags "-Wno-subobject-linkage" "-Wall" "-Wextra" "-Wpedantic" "-std=c++17" )
set( ENDFtk_Clang_MinGW_DEBUG_flags "-O0" "-g" "-gdwarf-3" "-fsignaling-nans" )
set( ENDFtk_Clang_MinGW_RELEASE_flags "-O3" "-DNDEBUG" )
set( ENDFtk_Clang_MinGW_strict_flags "-Werror" )
set( ENDFtk_Clang_MinGW_coverage_flags "--coverage" )
set( ENDFtk_Clang_MinGW_subproject_flags  )
set( ENDFtk_Clang_MinGW_base_project_flags  )
set( ENDFtk_Clang_MinGW_profile_generate_flags "-fprofile-generate='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_MinGW_link_time_optimization_flags "-flto" )
set( ENDFtk_Clang_MinGW_profile_use_flags "-fprofile-use='${CMAKE_BINARY_DIR}/profiling'" )
set( ENDFtk_Clang_MinGW_nonportable_optimization_flags "-march=native" )
set( ENDFtk_Clang_MinGW_static_flags "-static" )
get_directory_property( is_subproject PARENT_DIRECTORY )

if( NOT TARGET range-v3-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/range-v3-adapter )
endif()

if( NOT TARGET catch-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/catch-adapter )
endif()

if( NOT TARGET disco )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/disco )
endif()

if( NOT TARGET hana-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/hana-adapter )
endif()

if( NOT TARGET fmt-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/fmt-adapter )
endif()

if( NOT TARGET spdlog-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/spdlog-adapter )
endif()

if( NOT TARGET Log )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/Log )
endif()

if( NOT TARGET header-utilities )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/header-utilities )
endif()


if ( NOT GIT_EXECUTABLE )
    find_package( Git )
    if ( NOT GIT_FOUND )
        message( FATAL_ERROR "git installation was not found." )
    endif()
endif()

execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
) 

message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )
message( STATUS "" )
message( STATUS "ENDFtk" )
message( STATUS "Git current branch: ${GIT_BRANCH}" )
message( STATUS "Git commit hash: ${GIT_HASH}" )
message( STATUS "" )
message( STATUS "-----------------------------------------------------------" )

add_library( ENDFtk INTERFACE )
target_sources( ENDFtk INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/StructureDivision.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/isRedundant.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TextRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TapeIdentification.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/types.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/HeadRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ControlRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/DirectoryRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Material.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/File.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Tape.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/makeTape.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Section/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Section/src/findEnd.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Section/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/File/src/sectionNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/File/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/File/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/File/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Tape/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Tape/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Tape/src/materialNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Material/src/fileNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Material/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/tree/Material/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/DirectoryRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/BaseWithoutMT.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/BaseWithoutMT/src/readSEND.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/BaseWithoutMT/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/EffectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/AnalyticalFunctions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/src/verifyBetaValues.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/src/generateTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/EffectiveTemperature/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/checkLLN.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/readScatteringLaw.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/checkValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/readSecondaryTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/verifySecondaryTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/IncoherentElastic.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/IncoherentElastic/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic/src/generateTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/CoherentElastic/src/verifyTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/src/readScatteringLaw.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/2/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NoLawDataGiven.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Unknown.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyRecoils.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/IsotropicDiscreteEmission.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Multiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DefinedElsewhere.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NBodyPhaseSpace.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Multiplicity/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NBodyPhaseSpace/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/src/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/verifyLAW.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/readDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/verifyNA.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/checkLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/verifyLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DefinedElsewhere/src/checkLAW.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DefinedElsewhere/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/verifyLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifyLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/src/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/verifySorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-458.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-460.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/description.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/makeDescription.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-452.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/makeParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-456.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-455.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/readParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayModes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayMode.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/AverageDecayEnergies.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DiscreteSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/ContinuousSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/ContinuousSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/verifyLCOV.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/verifyDiscreteSize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/readContinuous.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecaySpectrum/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayMode/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DiscreteSpectrum/src/returnArray.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DiscreteSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DiscreteSpectrum/src/verifyNT.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DiscreteSpectrum/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayModes/src/verifyNDK.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayModes/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/DecayModes/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/AverageDecayEnergies/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/AverageDecayEnergies/src/verifyNC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/AverageDecayEnergies/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/8/457/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/AngularDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/MixedDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/TabulatedDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/LegendreDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/TabulatedDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/Isotropic.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/MixedDistributions/src/angularDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/MixedDistributions/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/MixedDistributions/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/MixedDistributions/src/verifyBoundary.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/LegendreDistributions/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/AngularDistributions/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/TabulatedDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/TabulatedDistributions/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/src/readDistributions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/4/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TransitionProbabilities.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/PartialMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TotalMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities/src/verifyNK.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities/src/readTotalMultiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/Multiplicities/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TotalMultiplicity/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TransitionProbabilities/Transition.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TransitionProbabilities/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TransitionProbabilities/src/verifyLG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/TransitionProbabilities/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/PartialMultiplicity/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/12/src/readPhotonProduction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/Base/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ScatteringRadius.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/SingleLevelBreitWigner.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBaseWithoutSpin.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreLValueBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/SpecialCase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMooreLValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ResonanceRange.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMoore.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/MultiLevelBreitWigner.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerLValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedLValueBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/SpecialCase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/SpecialCase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBase/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/readScatteringRadius.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/readRanges.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/Isotope/src/readParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/MultiLevelBreitWigner/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ScatteringRadius/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ResonanceRange/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ResonanceRange/src/verifyOptions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ResonanceRange/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMooreLValue/Resonance.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMooreLValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMoore/src/verifyNLSC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/ReichMoore/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase/src/validate.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreBase/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBaseWithoutSpin/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedBaseWithoutSpin/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ParticlePairs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/SpinGroup.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/SpinGroup/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/SpinGroup/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/AP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/SPI.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/RMatrixLimited/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerLValue/Resonance.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerLValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/JValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/LValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/LValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedEnergyDependent/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/BreitWignerReichMooreLValueBase/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedLValueBase/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedLValueBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedLValueBase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/UnresolvedLValueBase/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/SingleLevelBreitWigner/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/151/src/verifyNIS.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/reaction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/152/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/TotalCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/PartialCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/TotalCrossSection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/PartialCrossSection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/src/verifyNK.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/src/readTotalCrossSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/13/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/PartialProbability.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/EvaporationSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/MadlandNixSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/MaxwellianFissionSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/TabulatedSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/EffectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/WattSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/GeneralEvaporationSpectrum.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/DistributionFunction.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Parameter.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/WattSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/WattSpectrum/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/WattSpectrum/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/WattSpectrum/src/readParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/DistributionFunction/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/MadlandNixSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/TabulatedSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/TabulatedSpectrum/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection/src/verifyLF.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Subsection/src/readSubsection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/PartialProbability/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/EffectiveTemperature/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/Parameter/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/GeneralEvaporationSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/GeneralEvaporationSpectrum/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/GeneralEvaporationSpectrum/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/EvaporationSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/MaxwellianFissionSpectrum/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/src/verifyNK.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/5/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/verifyNZ.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/readInterpolationSequenceRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Integer.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Sequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Real.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/skip.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Character.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Tail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/helper.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/TailVerifying.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/ReadingPack.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/makeIteratorTuple.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/expandReferencePack.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/Zipped.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/readLine.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/readPartialLine.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/unzip.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/verifyTail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/increment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/process.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/reserve.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Sequence/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyVectorSizes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/readMetadata.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/readRangeDescriptions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyN2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyBoundaryIndicesAreSorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyTail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/HeadRecord/src/asHead.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/8.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/details.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/13.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/12.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/6.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/7.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/5.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/4.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/3.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/7/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/7/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/details/src/sectionOf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/details/src/get.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/details/src/fileOf.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/8/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/8/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/insert.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/fill.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base/src/verifyEND.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base/src/section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base/src/fill.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Base/src/deduceMapType.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/2/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/2/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ControlRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyVectorSizes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyNP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyXValuesAreSorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/readPairs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TextRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TapeIdentification/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord/src/readMetadata.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationRecord/src/ctor.hpp" )

target_include_directories( ENDFtk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/src src/ )

set( PREFIX ENDFtk_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( ENDFtk INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:ENDFtk_appended_flags>:${ENDFtk_appended_flags};>" )

target_link_libraries( ENDFtk INTERFACE range-v3-adapter INTERFACE catch-adapter INTERFACE disco INTERFACE hana-adapter INTERFACE Log INTERFACE header-utilities )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
        add_subdirectory( src/ENDFtk/test )
        add_subdirectory( src/ENDFtk/ControlRecord/test )
        add_subdirectory( src/ENDFtk/DirectoryRecord/test )
        add_subdirectory( src/ENDFtk/HeadRecord/test )
        add_subdirectory( src/ENDFtk/InterpolationRecord/test )
        add_subdirectory( src/ENDFtk/InterpolationSequenceRecord/test )
        add_subdirectory( src/ENDFtk/ListRecord/test )
        add_subdirectory( src/ENDFtk/StructureDivision/test )
        add_subdirectory( src/ENDFtk/TabulationRecord/test )
        add_subdirectory( src/ENDFtk/TapeIdentification/test )
        add_subdirectory( src/ENDFtk/TextRecord/test )
        add_subdirectory( src/ENDFtk/file/1/test )
        add_subdirectory( src/ENDFtk/file/2/test )
        add_subdirectory( src/ENDFtk/file/7/test )
        add_subdirectory( src/ENDFtk/file/8/test )
        add_subdirectory( src/ENDFtk/file/Type/test )
        add_subdirectory( src/ENDFtk/record/test )
        add_subdirectory( src/ENDFtk/record/Base/test )
        add_subdirectory( src/ENDFtk/record/InterpolationBase/test )
        add_subdirectory( src/ENDFtk/record/Sequence/test )
        add_subdirectory( src/ENDFtk/record/Tail/test )
        add_subdirectory( src/ENDFtk/record/Zipper/test )
        add_subdirectory( src/ENDFtk/section/1/451/test )
        add_subdirectory( src/ENDFtk/section/12/test )
        add_subdirectory( src/ENDFtk/section/12/Multiplicities/test )
        add_subdirectory( src/ENDFtk/section/12/PartialMultiplicity/test )
        add_subdirectory( src/ENDFtk/section/12/TotalMultiplicity/test )
        add_subdirectory( src/ENDFtk/section/12/TransitionProbabilities/test )
        add_subdirectory( src/ENDFtk/section/12/TransitionProbabilities/Transition/test )
        add_subdirectory( src/ENDFtk/section/13/test )
        add_subdirectory( src/ENDFtk/section/13/PartialCrossSection/test )
        add_subdirectory( src/ENDFtk/section/13/TotalCrossSection/test )
        add_subdirectory( src/ENDFtk/section/2/151/test )
        add_subdirectory( src/ENDFtk/section/2/151/BreitWignerLValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/BreitWignerLValue/Resonance/test )
        add_subdirectory( src/ENDFtk/section/2/151/Isotope/test )
        add_subdirectory( src/ENDFtk/section/2/151/MultiLevelBreitWigner/test )
        add_subdirectory( src/ENDFtk/section/2/151/RMatrixLimited/test )
        add_subdirectory( src/ENDFtk/section/2/151/RMatrixLimited/ParticlePairs/test )
        add_subdirectory( src/ENDFtk/section/2/151/RMatrixLimited/ResonanceChannels/test )
        add_subdirectory( src/ENDFtk/section/2/151/RMatrixLimited/ResonanceParameters/test )
        add_subdirectory( src/ENDFtk/section/2/151/RMatrixLimited/SpinGroup/test )
        add_subdirectory( src/ENDFtk/section/2/151/ReichMoore/test )
        add_subdirectory( src/ENDFtk/section/2/151/ReichMooreLValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/ReichMooreLValue/Resonance/test )
        add_subdirectory( src/ENDFtk/section/2/151/ScatteringRadius/test )
        add_subdirectory( src/ENDFtk/section/2/151/SingleLevelBreitWigner/test )
        add_subdirectory( src/ENDFtk/section/2/151/SpecialCase/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependent/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependent/JValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependent/LValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/JValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths/LValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/JValue/test )
        add_subdirectory( src/ENDFtk/section/2/151/UnresolvedEnergyIndependent/LValue/test )
        add_subdirectory( src/ENDFtk/section/2/152/test )
        add_subdirectory( src/ENDFtk/section/3/test )
        add_subdirectory( src/ENDFtk/section/4/test )
        add_subdirectory( src/ENDFtk/section/4/Isotropic/test )
        add_subdirectory( src/ENDFtk/section/4/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/4/LegendreDistributions/test )
        add_subdirectory( src/ENDFtk/section/4/MixedDistributions/test )
        add_subdirectory( src/ENDFtk/section/4/TabulatedDistribution/test )
        add_subdirectory( src/ENDFtk/section/4/TabulatedDistributions/test )
        add_subdirectory( src/ENDFtk/section/5/test )
        add_subdirectory( src/ENDFtk/section/5/DistributionFunction/test )
        add_subdirectory( src/ENDFtk/section/5/EffectiveTemperature/test )
        add_subdirectory( src/ENDFtk/section/5/EvaporationSpectrum/test )
        add_subdirectory( src/ENDFtk/section/5/GeneralEvaporationSpectrum/test )
        add_subdirectory( src/ENDFtk/section/5/MadlandNixSpectrum/test )
        add_subdirectory( src/ENDFtk/section/5/MaxwellianFissionSpectrum/test )
        add_subdirectory( src/ENDFtk/section/5/Parameter/test )
        add_subdirectory( src/ENDFtk/section/5/PartialProbability/test )
        add_subdirectory( src/ENDFtk/section/5/Subsection/test )
        add_subdirectory( src/ENDFtk/section/5/TabulatedSpectrum/test )
        add_subdirectory( src/ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution/test )
        add_subdirectory( src/ENDFtk/section/5/WattSpectrum/test )
        add_subdirectory( src/ENDFtk/section/6/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/Base/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData/test )
        add_subdirectory( src/ENDFtk/section/6/DefinedElsewhere/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyRecoils/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/6/IsotropicDiscreteEmission/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution/test )
        add_subdirectory( src/ENDFtk/section/6/Multiplicity/test )
        add_subdirectory( src/ENDFtk/section/6/NBodyPhaseSpace/test )
        add_subdirectory( src/ENDFtk/section/6/NoLawDataGiven/test )
        add_subdirectory( src/ENDFtk/section/6/ReactionProduct/test )
        add_subdirectory( src/ENDFtk/section/6/Unknown/test )
        add_subdirectory( src/ENDFtk/section/7/2/test )
        add_subdirectory( src/ENDFtk/section/7/2/CoherentElastic/test )
        add_subdirectory( src/ENDFtk/section/7/2/IncoherentElastic/test )
        add_subdirectory( src/ENDFtk/section/7/4/test )
        add_subdirectory( src/ENDFtk/section/7/4/AnalyticalFunctions/test )
        add_subdirectory( src/ENDFtk/section/7/4/EffectiveTemperature/test )
        add_subdirectory( src/ENDFtk/section/7/4/ScatteringLawConstants/test )
        add_subdirectory( src/ENDFtk/section/7/4/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/7/4/Tabulated/ScatteringFunction/test )
        add_subdirectory( src/ENDFtk/section/8/457/test )
        add_subdirectory( src/ENDFtk/section/8/457/AverageDecayEnergies/test )
        add_subdirectory( src/ENDFtk/section/8/457/ContinuousSpectrum/test )
        add_subdirectory( src/ENDFtk/section/8/457/DecayMode/test )
        add_subdirectory( src/ENDFtk/section/8/457/DecayModes/test )
        add_subdirectory( src/ENDFtk/section/8/457/DecaySpectrum/test )
        add_subdirectory( src/ENDFtk/section/8/457/DiscreteSpectrum/test )
        add_subdirectory( src/ENDFtk/section/Base/test )
        add_subdirectory( src/ENDFtk/section/BaseWithoutMT/test )
        add_subdirectory( src/ENDFtk/tree/File/test )
        add_subdirectory( src/ENDFtk/tree/Material/test )
        add_subdirectory( src/ENDFtk/tree/Section/test )
        add_subdirectory( src/ENDFtk/tree/Tape/test )
    endif() 
endif()

install( FILES "${CMAKE_BINARY_DIR}/signature.json"
         DESTINATION share/${CMAKE_PROJECT_NAME}
         PERMISSIONS OWNER_READ OWNER_WRITE
                     GROUP_READ
                     WORLD_READ
)
install( DIRECTORY src// DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE
                          GROUP_READ
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE
                               GROUP_READ
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )

                    INCLUDE(CPack)
                    