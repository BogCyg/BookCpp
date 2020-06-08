cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME CurrencyCalc_GUI )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )



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
include_directories( ../CurrencyCalc_Lib/include )
include_directories( ./include )
include_directories( ../../FLTK )



# Automatically add all *.cpp files to the project
file ( GLOB SOURCES "./src/*.cpp" )

# Add source file to the build executable
add_executable( ${PROJECT_NAME} ${SOURCES} )


# Some system libraries
if( WIN32 )

# Assuming Windows SDK is installed, so we do not need to call find_library()

	target_link_libraries( 	${PROJECT_NAME} 
				PUBLIC 
					wsock32
					comctl32
			)

elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

	find_library( COCOA_LIB Cocoa )
	target_link_libraries( ${PROJECT_NAME} PUBLIC ${COCOA_LIB} )

endif()



# Currency Calc library
find_library( 	CURRENCY_CALC_LIB 
		NAMES 			CurrencyCalc_Lib 
		PATHS 			../CurrencyCalc_Lib/lib )

# FLTK libraries
find_library( 	FLTK_LIBRARY
		NAMES 			fltkd fltk
		PATHS 			../../FLTK/lib/Debug 	../../FLTK/lib/Release 	../../FLTK/lib )


target_link_libraries( 	${PROJECT_NAME} 
			PUBLIC 
				${CURRENCY_CALC_LIB} 
				${FLTK_LIBRARY} 
		)



# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )



