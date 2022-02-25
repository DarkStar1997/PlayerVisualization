project(SFMLGame
    DESCRIPTION "Sample SFML Game"
    LANGUAGES C CXX
    )

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    MESSAGE("CCACHE support enabled")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_BUILD_TYPE "RELEASE")

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(sfml)

set(LIB_NAME "ecosystem_viz")

add_subdirectory(src)
add_subdirectory(run)
