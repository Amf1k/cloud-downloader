cmake_minimum_required(VERSION 3.14)

project(app LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)


file(GLOB_RECURSE HEADERS LIST_DIRECTORIES false CONFIGURE_DEPENDS src/*.hpp)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false CONFIGURE_DEPENDS src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} qml.qrc)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick libclouddownloader)
