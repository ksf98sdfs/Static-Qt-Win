cmake_minimum_required( VERSION 3.30.3 )

set( library_name Static-Qt-Test )

project( ${library_name} CXX )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( QT_FULL_VERSION 5.15.15 )
if( CMAKE_SYSTEM_NAME STREQUAL "Windows" )
	set( QT_DIRECTORY "C:/Qt/Qt-${QT_FULL_VERSION}/lib/cmake/Qt5" )
elseif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
	set( QT_DIRECTORY "/usr/local/Qt-${QT_FULL_VERSION}/lib/cmake/Qt5" )
elseif( CMAKE_SYSTEM_NAME STREQUAL "Darwin" )
	set( QT_DIRECTORY "/usr/local/Qt-${QT_FULL_VERSION}/lib/cmake/Qt5" )
endif()

# Enable static linkage of runtime on MSVC
if ( MSVC )
  set( CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded" )
endif()

# Hide the console window in visual studio projects
if( MSVC )
	set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
	set( CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
endif()

list( APPEND Qt5_DIR ${QT_DIRECTORY} )

# Locate Qt's libraries and header files.
find_package( Qt5 REQUIRED COMPONENTS Core Gui Widgets )

file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.qrc )

add_executable( ${library_name} ${SRC_FILES} )

# Set the correct Visual Studio startup project.
if ( MSVC )
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${library_name} )
endif()

# Link against the Qt libraries, and add required include directories and compile definitions.
target_link_libraries( ${library_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets )

# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE ${CMAKE_CURRENT_BINARY_DIR} )
