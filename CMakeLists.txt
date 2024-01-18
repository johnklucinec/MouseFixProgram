cmake_minimum_required(VERSION 3.5)

project(MouseFixProgram VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
       main.cpp
       widget.cpp
       widget.h
       widget.ui
       custommessagebox.ui
       custommessagebox.h
       custommessagebox.cpp
       ./src/code/markC.cpp
       ./src/code/markC.h
       ./src/code/MouseTweaks.cpp
       ./src/code/MouseTweaks.h
       ./src/code/RegistryManager.cpp
       ./src/code/RegistryManager.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
   qt_add_executable(MouseFixProgram
       MANUAL_FINALIZATION
       ${PROJECT_SOURCES}
       resource.qrc
   )
else()
   if(ANDROID)
       add_library(MouseFixProgram SHARED
           ${PROJECT_SOURCES}
       )
   else()
       add_executable(MouseFixProgram
           ${PROJECT_SOURCES}
       )
   endif()
endif()

target_link_libraries(MouseFixProgram PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
 set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MouseFixProgram)
endif()
set_target_properties(MouseFixProgram PROPERTIES
   ${BUNDLE_ID_OPTION}
   MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
   MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
   MACOSX_BUNDLE TRUE
   WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MouseFixProgram
   BUNDLE DESTINATION .
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

# Add this line to enable static linking
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

if(QT_VERSION_MAJOR EQUAL 6)
   qt_finalize_executable(MouseFixProgram)
endif()
