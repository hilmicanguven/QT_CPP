cmake_minimum_required(VERSION 3.14)

project(project_001 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

set(TS_FILES project_001_en_GB.ts)

add_executable(project_001
  main.cpp
  ${TS_FILES}
  test.h test.cpp
)
target_link_libraries(project_001 Qt${QT_VERSION_MAJOR}::Core)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

include(GNUInstallDirs)
install(TARGETS project_001
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
