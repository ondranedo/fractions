add_executable(demo main.c)

target_link_libraries(demo frac)
target_include_directories(demo PRIVATE "${PROJECT_SOURCE_DIR}/include")