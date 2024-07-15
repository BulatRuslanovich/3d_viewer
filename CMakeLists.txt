cmake_minimum_required(VERSION 3.23)

project(3dViewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

find_package(Qt6 COMPONENTS Widgets OpenGL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(GIF REQUIRED)


add_executable(3dViewer
        src/view/main.cpp
        src/view/view.cpp
        src/view/view.h
        src/model/parser.h
        src/model/parser.cpp
        src/model/model_data.h
        src/model/model_data.h
        src/model/model_data.h
        src/model/model.h
        src/model/model.cpp
        src/controller/controller.h
        src/view/glwidget.h
        src/view/glwidget.cpp
        src/model/set_center.h
        src/model/set_center.cpp
        src/model/affine_transformations.h
        src/model/affine_transformations.cpp

        src/view/QtGifImage/gifimage/qgifimage.h
        src/view/QtGifImage/gifimage/qgifimage.cpp
        src/view/QtGifImage/gifimage/qgifglobal.h
        src/view/QtGifImage/gifimage/qgifimage_p.h
        src/view/QtGifImage/3rdParty/giflib/gif_lib.h
        src/view/QtGifImage/3rdParty/giflib/gif_hash.h
        src/view/QtGifImage/3rdParty/giflib/dgif_lib.c
        src/view/QtGifImage/3rdParty/giflib/egif_lib.c
        src/view/QtGifImage/3rdParty/giflib/gif_err.c
        src/view/QtGifImage/3rdParty/giflib/gif_font.c
        src/view/QtGifImage/3rdParty/giflib/gif_hash.c
        src/view/QtGifImage/3rdParty/giflib/gifalloc.c
        src/view/QtGifImage/3rdParty/giflib/quantize.c
)

target_link_libraries(3dViewer PRIVATE Qt6::Widgets Qt6::OpenGLWidgets OpenGL::GLU gif)

