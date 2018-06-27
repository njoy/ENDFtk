
cmake_minimum_required( VERSION 3.2 ) 
set( CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Supported configuration types" FORCE )
        
if( NOT ROOT_DIRECTORY )
    set( ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )
    if ( NOT fetched_subprojects )
        if ( NOT PYTHON_EXECUTABLE )
            find_package( PythonInterp )
            if ( NOT PYTHONINTERP_FOUND )
                message( FATAL_ERROR "Python interpeter installation was not found." )
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
option( profile_use "In the RELEASE configuration, leverage previously generated exeution profile to inform optimization decisions" )
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

set( ENDFtk_AppleClang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_GNU_Linux_common_flags "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_GNU_Windows_common_flags "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_GNU_Darwin_common_flags "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_Clang_Linux_common_flags "-stdlib=libstdc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_Clang_Windows_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
set( ENDFtk_Clang_Darwin_common_flags "-stdlib=libc++" "-Wall" "-Wextra" "-Wpedantic" "-std=c++14" )
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
get_directory_property( is_subproject PARENT_DIRECTORY )

if( NOT TARGET catch-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/catch-adapter )
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

if( NOT TARGET disco )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/disco )
endif()

if( NOT TARGET header-utilities )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/header-utilities )
endif()

if( NOT TARGET hopscotch-map-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/hopscotch-map-adapter )
endif()

if( NOT TARGET range-v3-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/range-v3-adapter )
endif()

if( NOT TARGET variant-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/variant-adapter )
endif()

if( NOT TARGET hana-adapter )
    add_subdirectory( ${ROOT_DIRECTORY}/subprojects/hana-adapter )
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
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ControlRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/DirectoryRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/HeadRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/StructureDivision.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TapeIdentification.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TextRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ControlRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/DirectoryRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/HeadRecord/src/asHead.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord/src/readMetadata.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/ListRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TapeIdentification/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TextRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/checkRedundant.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/collectMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/collectVector.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/sectionNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/Type/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/get.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/fill.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/file/1/src/sectionNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Character.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Integer.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Real.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Sequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Tail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/TailVerifying.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/helper.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/skip.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Sequence/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/ReadingPack.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/Zipped.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/expandReferencePack.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/increment.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/makeIteratorTuple.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/process.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/readLine.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/readPartialLine.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/reserve.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/unzip.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/Zipper/src/verifyTail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/readMetadata.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/readRangeDescriptions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyBoundaryIndicesAreSorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyN2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyTail.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/verifyVectorSizes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/record/InterpolationBase/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/Isotope.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/SpecialCase.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/Base/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/Isotope/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/Isotope/src/readRanges.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/SpecialCase/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/RMatrixLimited.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/MultilevelBreitWigner.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/SingleLevelBreitWigner.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/Lvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/src/readAPE.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/src/readLists.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/src/validate.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/BreitWigner/Lvalue/Resonance.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/MultilevelBreitWigner/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/RMatrixLimited/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore/Lvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore/src/validate.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/ReichMoore/Lvalue/Resonance.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/resolved/SingleLevelBreitWigner/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependent/Jvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependent/Lvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependent/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Jvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/Lvalue/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent/Jvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent/Lvalue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/src/read.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/src/readAPE.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/resonanceParameters/src/readLISTs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/2/src/readIsotopes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/3/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/Base/src/readSEND.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/Base/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/description.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/readRecords.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-452.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-455.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-456.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-458.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor-460.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/1/451/src/readParameters.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DefinedElsewhere.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyRecoils.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/IsotropicDiscreteEmission.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Multiplicity.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NBodyPhaseSpace.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NoLawDataGiven.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Unknown.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/SubSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifyLTP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/src/readSubSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ChargedParticleElasticScattering/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/SubSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Base/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/src/verifyNA.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/SubSection/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/checkLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/readInterpolationRecord.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ContinuumEnergyAngle/src/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DefinedElsewhere/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifyLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/src/readSubSection.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/verifyLANG.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/DiscreteTwoBodyScattering/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/CosineOutgoingEnergyDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyOutgoingCosineDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/CosineOutgoingEnergyDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyOutgoingCosineDistribution/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/LaboratoryAngleEnergy/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/Multiplicity/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/NBodyPhaseSpace/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/readDistribution.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/ReactionProduct/src/verifyLAW.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/6/src/readReactionProducts.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/AnalyticalFunctions.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/EffectiveTemperature.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/generateList.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/ScatteringLawConstants/src/verifySize.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/readTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/generateTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/Tabulated/BetaValue/src/verifyLT.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/EffectiveTemperature/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/readScatteringLaw.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/section/7/4/src/readSecondaryTemperatures.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Section.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Material.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Tape.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File/src/createVector.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/File/src/sectionNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Material/src/createVector.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Material/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Material/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Material/src/fileNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Section/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Section/src/findEnd.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Section/src/parse.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Tape/src/createVector.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Tape/src/createMap.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Tape/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/syntaxTree/Tape/src/materialNumber.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationRecord/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/readPairs.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyVectorSizes.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyXValuesAreSorted.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/TabulationRecord/src/verifyNP.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/NC.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/ctor.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/print.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/readSequence.hpp"
             "${CMAKE_CURRENT_SOURCE_DIR}/src/ENDFtk/InterpolationSequenceRecord/src/verifyNZ.hpp" )

target_include_directories( ENDFtk INTERFACE src )

set( PREFIX ENDFtk_${CMAKE_CXX_COMPILER_ID}_${CMAKE_SYSTEM_NAME} )

target_link_libraries( ENDFtk INTERFACE "$<$<AND:$<CONFIG:RELEASE>,$<BOOL:${link_time_optimization}>>:${${PREFIX}_RELEASE_flags};${${PREFIX}_link_time_optimization_flags}$<$<BOOL:${profile_generate}>:${${PREFIX}_profile_generate_flags};>$<$<BOOL:${profile_use}>:${${PREFIX}_profile_use_flags};>$<$<BOOL:${nonportable_optimization}>:${${PREFIX}_nonportable_optimization_flags};>>$<$<CONFIG:DEBUG>:$<$<BOOL:${coverage}>:${${PREFIX}_coverage_flags};>>$<$<BOOL:CXX_appended_flags>:${CXX_appended_flags};>$<$<BOOL:ENDFtk_appended_flags>:${ENDFtk_appended_flags};>" )

target_link_libraries( ENDFtk INTERFACE Log INTERFACE catch-adapter INTERFACE disco INTERFACE header-utilities INTERFACE hopscotch-map-adapter INTERFACE range-v3-adapter INTERFACE variant-adapter INTERFACE hana-adapter )

if( NOT is_subproject )
    enable_testing() 
    if ( unit_tests )
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
        add_subdirectory( src/ENDFtk/file/Type/test )
        add_subdirectory( src/ENDFtk/record/test )
        add_subdirectory( src/ENDFtk/record/Base/test )
        add_subdirectory( src/ENDFtk/record/InterpolationBase/test )
        add_subdirectory( src/ENDFtk/record/Sequence/test )
        add_subdirectory( src/ENDFtk/record/Tail/test )
        add_subdirectory( src/ENDFtk/record/Zipper/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/Base/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/Isotope/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/SpecialCase/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/BreitWigner/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/BreitWigner/Lvalue/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/MultilevelBreitWigner/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/RMatrixLimited/SpinGroup/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/ReichMoore/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/ReichMoore/Lvalue/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/resolved/SingleLevelBreitWigner/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/unresolved/EnergyDependent/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/unresolved/EnergyDependentFissionWidths/test )
        add_subdirectory( src/ENDFtk/resonanceParameters/unresolved/EnergyIndependent/test )
        add_subdirectory( src/ENDFtk/section/1/451/test )
        add_subdirectory( src/ENDFtk/section/2/test )
        add_subdirectory( src/ENDFtk/section/3/test )
        add_subdirectory( src/ENDFtk/section/6/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference/test )
        add_subdirectory( src/ENDFtk/section/6/ChargedParticleElasticScattering/SubSection/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/Base/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/SubSection/test )
        add_subdirectory( src/ENDFtk/section/6/ContinuumEnergyAngle/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/6/DefinedElsewhere/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyRecoils/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/SubSection/test )
        add_subdirectory( src/ENDFtk/section/6/DiscreteTwoBodyScattering/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/6/IsotropicDiscreteEmission/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/CosineOutgoingEnergyDistribution/test )
        add_subdirectory( src/ENDFtk/section/6/LaboratoryAngleEnergy/EnergyOutgoingCosineDistribution/test )
        add_subdirectory( src/ENDFtk/section/6/Multiplicity/test )
        add_subdirectory( src/ENDFtk/section/6/NBodyPhaseSpace/test )
        add_subdirectory( src/ENDFtk/section/6/NoLawDataGiven/test )
        add_subdirectory( src/ENDFtk/section/6/ReactionProduct/test )
        add_subdirectory( src/ENDFtk/section/6/Unknown/test )
        add_subdirectory( src/ENDFtk/section/7/4/test )
        add_subdirectory( src/ENDFtk/section/7/4/AnalyticalFunctions/test )
        add_subdirectory( src/ENDFtk/section/7/4/EffectiveTemperature/test )
        add_subdirectory( src/ENDFtk/section/7/4/ScatteringLawConstants/test )
        add_subdirectory( src/ENDFtk/section/7/4/Tabulated/test )
        add_subdirectory( src/ENDFtk/section/7/4/Tabulated/BetaValue/test )
        add_subdirectory( src/ENDFtk/section/Base/test )
        add_subdirectory( src/ENDFtk/syntaxTree/File/test )
        add_subdirectory( src/ENDFtk/syntaxTree/Material/test )
        add_subdirectory( src/ENDFtk/syntaxTree/Section/test )
        add_subdirectory( src/ENDFtk/syntaxTree/Tape/test )
    endif() 
endif()

install( DIRECTORY src/ DESTINATION include
         FILE_PERMISSIONS OWNER_READ OWNER_WRITE 
                          GROUP_READ 
                          WORLD_READ
         DIRECTORY_PERMISSIONS OWNER_READ OWNER_WRITE 
                               GROUP_READ 
                               WORLD_READ
         FILES_MATCHING REGEX ".*\.h[+][+]$|.*\.hxx$|.*\.hpp$|.*\.hh$|.*\.h$"  )
