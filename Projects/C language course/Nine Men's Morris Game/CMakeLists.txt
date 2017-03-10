cmake_minimum_required(VERSION 2.8.4)
project(MlynekGra)

SET(CMAKE_C_FLAGS "-std=gnu99")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SOURCE_FILES
    dots.h
    dots.c
    function.c
    function.h
    GTK.c
    GTK.h
    main.c
    widget.h
    line.png
    line1.png
    line2.png
    )

add_executable(MlynekGra ${SOURCE_FILES})

target_link_libraries(MlynekGra ${GTK3_LIBRARIES} m)