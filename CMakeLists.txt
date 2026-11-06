cmake_minimum_required(VERSION 4.3)
project(NHZ_Snake C)

set(CMAKE_C_STANDARD 11)

list(APPEND CMAKE_PREFIX_PATH "C:/msys64/ucrt64")



find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(NHZ_Snake main.c)

target_link_libraries(NHZ_Snake PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf)


# Összekötjük a pkg-config által talált útvonalakat és könyvtárakat
target_include_directories(NHZ_Snake PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_directories(NHZ_Snake PRIVATE ${SDL2_LIBRARY_DIRS})
target_link_libraries(NHZ_Snake PRIVATE ${SDL2_LIBRARIES})

# Ez kell, hogy a konzolos ablak és a main() ne vessszen össze a MinGW-vel
target_link_options(NHZ_Snake PRIVATE "-mconsole")