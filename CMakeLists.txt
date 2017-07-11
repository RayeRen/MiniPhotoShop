cmake_minimum_required(VERSION 3.0)
set(TARGET_NAME MiniPhotoShop)

project(${TARGET_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
#打开Qt的MOC功能和UI文件处理功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#查找Qt的库
find_package(Qt5Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Xml)
find_package(Qt5Widgets REQUIRED)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set(CMAKE_CXX_STANDARD 11)
file(GLOB_RECURSE SRC_LIST src/*.cpp src/*.h)

# User interfgit ace files
file(GLOB_RECURSE FORMS src/*.ui)

# Resource fileshgx
file(GLOB_RECURSE RESOURCES *.qrc)

# Shared libraries
set(LIBRARIES
        Qt5::Widgets
        )

qt5_wrap_ui(UIC_SOURCES ${FORMS})
qt5_add_resources(RCC_SOURCES ${RESOURCES})

add_executable(MiniPhotoShop
        ${SOURCE_FILES}
        ${UI_HEADERS}
        ${UIC_SOURCES}
        ${RCC_SOURCES}
        ${SRC_LIST}
        )

target_link_libraries(${TARGET_NAME} ${LIBRARIES})