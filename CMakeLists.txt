cmake_minimum_required(VERSION 3.5)

project(3d_viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(Qt6 COMPONENTS Widgets OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)


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
        controller/controller.h
        view/glwidget.h
        view/glwidget.cpp
)


target_link_libraries(3d_viewer PRIVATE Qt6::Widgets Qt6::OpenGLWidgets OpenGL::GLU)
#target_link_libraries(3d_viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


