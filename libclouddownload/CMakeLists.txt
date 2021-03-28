cmake_minimum_required(VERSION 3.17)

project(libclouddownloader VERSION 0.0.1 LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Network REQUIRED)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false CONFIGURE_DEPENDS src/*.hpp)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
target_include_directories(${PROJECT_NAME} PUBLIC src)
