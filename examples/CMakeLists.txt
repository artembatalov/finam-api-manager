cmake_minimum_required(VERSION 3.20)

foreach(example account asset auth data metrics order report main)
    add_executable(example_${example} ${example}.cpp)
    target_link_libraries(example_${example} PRIVATE finam-api-manager)
endforeach()