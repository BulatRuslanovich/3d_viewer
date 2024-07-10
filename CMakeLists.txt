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
find_package(GIF REQUIRED)


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
        model/set_center.h
        model/set_center.cpp
        model/affine_transformations.h
        model/affine_transformations.cpp

        view/QtGifImage/gifimage/qgifimage.h
        view/QtGifImage/gifimage/qgifimage.cpp
        view/QtGifImage/gifimage/qgifglobal.h
        view/QtGifImage/gifimage/qgifimage_p.h
        view/QtGifImage/3rdParty/giflib/gif_lib.h
        view/QtGifImage/3rdParty/giflib/gif_hash.h
        view/QtGifImage/3rdParty/giflib/dgif_lib.c
        view/QtGifImage/3rdParty/giflib/egif_lib.c
        view/QtGifImage/3rdParty/giflib/gif_err.c
        view/QtGifImage/3rdParty/giflib/gif_font.c
        view/QtGifImage/3rdParty/giflib/gif_hash.c
        view/QtGifImage/3rdParty/giflib/gifalloc.c
        view/QtGifImage/3rdParty/giflib/quantize.c

)


target_link_libraries(3d_viewer PRIVATE Qt6::Widgets Qt6::OpenGLWidgets OpenGL::GLU gif)


