cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME ComplexQuadEq )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )


#[[ADD_DEFINITIONS(-g++ -O2 -fsigned-char -freg-struct-return -Wall -W -Wshadow -Wstrict-prototypes -Wpointer-arith -Wcast-qual -Winline -Werror)]]

if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /D_UNICODE /DUNICODE" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /D_UNICODE /DUNICODE" )
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Mac settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Linux settings chosen..." )
endif()


# Inform CMake where the header files are
# We also need to add sources from other projects: Complex and QuadEq
include_directories( include "./../Complex/include" "./../QuadEq/include" )


# Automatically add all *.cpp and *.h files to the project
# We also need to add sources from other projects: Complex and QuadEq
file ( GLOB SOURCES "./src/*.cpp" "./../Complex/src/Complex.cpp" "./../QuadEq/src/QuadEq.cpp" "./include/*.h" )
add_executable( ${PROJECT_NAME} ${SOURCES} )


# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )
