function(add_code name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE fmt sfml-audio sfml-graphics ${LIB_NAME})
    target_include_directories(${name} PRIVATE ${SFMLGame_SOURCE_DIR}/include)
endfunction()

add_code(test1)
add_code(main)
