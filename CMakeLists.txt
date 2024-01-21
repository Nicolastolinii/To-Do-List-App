cmake_minimum_required(VERSION 3.5)

project(To-Do-List VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

if(WIN32)
    # Definir la ruta al archivo de recursos
    set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/appicon.rc")
    # Agregar el archivo de recursos al conjunto de fuentes del proyecto
    list(APPEND PROJECT_SOURCES ${app_icon_resource_windows})
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(To-Do-List
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        taskwidget.h
        taskwidget.cpp
    )
else()
    if(ANDROID)
        add_library(To-Do-List SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(To-Do-List
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(To-Do-List PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(WIN32)
    # Configuraciones adicionales para Windows
    set_target_properties(To-Do-List PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Resto del código sin cambios
# ...
