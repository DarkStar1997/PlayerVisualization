set(SOURCES
    game.cpp
    entity.cpp
    )

add_library(${LIB_NAME} SHARED ${SOURCES})
target_include_directories(${LIB_NAME} PRIVATE 
    ${SFMLGame_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE fmt::fmt sfml-graphics)
