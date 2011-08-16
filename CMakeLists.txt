# CMake Build File for Sandstorms
# author: Tag Ashby <tgashby@calpoly.edu>

cmake_minimum_required(VERSION 2.8)

project(Sandstorms)

macro(ADD_FRAMEWORK fwname path appname)
	find_library(FRAMEWORK_${fwname}
		NAMES ${fwname}
		PATHS ${path}

		PATH_SUFFIXES Frameworks
		NO_DEFAULT_PATH
	)

	if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
		message(ERROR ": Framework ${fwname} not found")
	else()
		target_link_libraries(${appname} ${FRAMEWORK_${fwname}})
		message(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
	endif()
endmacro(ADD_FRAMEWORK)

# Sources
set(
   SOURCES
   src/Character.cpp
   src/Player.cpp
   src/SSMain.cpp
)

# Includes
set(
   INCLUDES
   include/Character.h
   include/Player.h
   include/SSMain.h
)

# Get everything together for the executable
add_executable(
   Sandstorms
   WIN32
   MACOSX_BUNDLE
   ${SOURCES}
   ${INCLUDES}
)

# Non-System Libraries

set(
	LIB_FOLDER
	${CMAKE_CURRENT_SOURCE_DIR}/lib
	CACHE STRING "Path to libraries" FORCE
)

# SDL
set(
	SDL_FOLDER
	${LIB_FOLDER}/sdl-1.3
	CACHE STRING "Path to SDL 1.3" FORCE
)

find_library(
	SDL_LIBRARY
	NAMES SDL-1.3.0 SDL
	PATHS ${SDL_FOLDER}
	PATH_SUFFIXES Apple Win32
	NO_DEFAULT_PATH
)

find_library(
	SDLMAIN_LIBRARY
	NAMES SDLmain
	PATHS ${SDL_FOLDER}
	PATH_SUFFIXES Apple Win32
	NO_DEFAULT_PATH
)

find_library(
	TGA_ENGINE_LIBRARY
	NAMES TGAEngine
	PATHS ${LIB_FOLDER}/TGAEngine
	PATH_SUFFIXES Apple Win32
	NO_DEFAULT_PATH
)

# SDL_Image
set(
	SDL_IMG_FOLDER
	${LIB_FOLDER}/SDL_image
	CACHE STRING "Path to SDL_image 1.2" FORCE
)

# System Libraries

# OpenGL
find_package(
	OpenGL REQUIRED
)

# Deal with Platform Specific things

if (APPLE)
    add_custom_command(TARGET Sandstorms
		PRE_LINK
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIB_FOLDER}/SDL_image.framework /Library/SDL_image.framework
	)
	
	ADD_FRAMEWORK(Cocoa /System/Libray/ Animation-Calibrator)
	ADD_FRAMEWORK(SDL_image /Library/ Animation-Calibrator)
endif()

if(WIN32)	
find_library(
	SDL_IMG_LIBRARY
	NAMES SDL_image
	PATHS ${SDL_IMG_FOLDER}
	PATH_SUFFIXES lib
	NO_DEFAULT_PATH
)
endif()

# Include the Includes
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${LIB_FOLDER}/TGAEngine/include
	${SDL_FOLDER}/include
	${SDL_IMG_FOLDER}/include
)

# Link all the libraries
target_link_libraries(
   Sandstorms
   ${OPENGL_LIBRARIES}
   ${SDL_LIBRARY}
   ${SDLMAIN_LIBRARY}
   ${SDL_IMG_LIBRARY}
   ${TGA_ENGINE_LIBRARY}
   ${EXTRA_LIBS}
)
