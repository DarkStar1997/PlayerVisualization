set(SOURCES
    game.cpp
    entity.cpp
    )

add_library(${LIB_NAME} SHARED ${SOURCES})
target_include_directories(${LIB_NAME} PRIVATE 
    ${SFMLGame_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PUBLIC fmt::fmt sfml-graphics)
install(TARGETS ${LIB_NAME} fmt EXPORT PlayerVizTargets DESTINATION lib)
