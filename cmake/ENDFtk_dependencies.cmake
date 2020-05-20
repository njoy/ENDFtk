include( FetchContent )


#######################################################################
# Forward declarations
#######################################################################



#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( range-v3-adapter
    GIT_REPOSITORY  https://github.com/njoy/range-v3-adapter
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( catch-adapter
    GIT_REPOSITORY  https://github.com/njoy/catch-adapter
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( disco
    GIT_REPOSITORY  https://github.com/njoy/disco
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( hana-adapter
    GIT_REPOSITORY  https://github.com/njoy/hana-adapter
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( header-utilities
    GIT_REPOSITORY  https://github.com/njoy/header-utilities
    GIT_TAG         origin/build/fetchcontent
    )

FetchContent_Declare( Log
    GIT_REPOSITORY  https://github.com/njoy/Log
    GIT_TAG         origin/build/fetchcontent
    )


#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    range-v3-adapter
    catch-adapter
    disco
    hana-adapter
    header-utilities
    Log
    )

