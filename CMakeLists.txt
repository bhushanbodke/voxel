cmake_minimum_required(VERSION 3.10)
project (Voxel)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} src/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

if(MSVC)
    target_include_directories(${PROJECT_NAME} PRIVATE , ${CMAKE_SOURCE_DIR}/lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw3.lib)
else()
    find_package(glfw3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
endif()    
file(COPY ${CMAKE_SOURCE_DIR}/assets/  DESTINATION ${CMAKE_BINARY_DIR}/)
