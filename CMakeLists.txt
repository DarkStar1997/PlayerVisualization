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
get_filename_component(fc_cache "../.fetchcontent_cache"
                       REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(FETCHCONTENT_BASE_DIR ${fc_cache})

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML
    GIT_TAG 2.6.1
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(sfml)

FetchContent_Declare(
    fmtlib
    GIT_REPOSITORY "https://github.com/fmtlib/fmt"
    GIT_TAG 5c0d65640118e7e0b1350f28fab3243fd6ce35a0
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(fmtlib)

FetchContent_Declare(
    argh
    GIT_REPOSITORY "https://github.com/adishavit/argh"
    GIT_TAG 01b6a4a3b0991dc2f29e4ab55eb7da90c8189f80
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(argh)

FetchContent_Declare(
    box2d
    GIT_REPOSITORY "https://github.com/erincatto/box2d"
    GIT_TAG 9dc24a6fd4f32442c4bcf80791de47a0a7d25afb
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(box2d)

set(LIB_NAME "ecosystem_viz")

add_subdirectory(src)
add_subdirectory(run)

export(EXPORT PlayerVizTargets NAMESPACE RMG FILE "${CMAKE_CURRENT_BINARY_DIR}/PlayerVizTargets.cmake")
