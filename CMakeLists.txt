cmake_minimum_required(VERSION 3.5)

project(3d_viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


add_executable(3d_viewer
        main.cpp
        view/view.cpp
        view/view.h
        model/parser.h
        model/parser.cpp
        model/model_data.h
        model/model_data.h
        model/model_data.h
        model/model_data.cpp
        model/model.h
        model/model.cpp
)


target_link_libraries(3d_viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


