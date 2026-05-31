cmake_minimum_required(VERSION 3.16)

project(FFmpegGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(FFmpegGUI
    main.cpp
    MainWindow.cpp
    MainWindow.h
)

target_link_libraries(FFmpegGUI PRIVATE Qt6::Widgets)
