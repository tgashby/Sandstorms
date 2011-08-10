# CMake Build File for Sandstorms
# author: Tag Ashby <tgashby@calpoly.edu>

cmake_minimum_required(VERSION 2.8)

project(Sandstorms)

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

# Non-System Libraries

# SDL
set(
   SDL_FOLDER
   ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl-1.3
   CACHE STRING "Path to SDL 1.3" FORCE
)

find_library(
   SDL_LIBRARY
   NAMES SDL-1.3.0 SDL
   PATHS ${SDL_FOLDER}
   PATH_SUFFIXES local/lib VisualC/SDL/Win32/Release
   NO_DEFAULT_PATH
)

find_library(
   SDLMAIN_LIBRARY
   NAMES SDLmain
   PATHS ${SDL_FOLDER}
   PATH_SUFFIXES local/lib VisualC/SDLmain/Win32/Release
   NO_DEFAULT_PATH
)

find_library(
	TGA_ENGINE_LIBRARY
	NAMES TGAEngine
	PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# SDL_Image
set(
   SDL_IMG_FOLDER
   ${SDL_IMG_FOLDER} ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL_image
   CACHE STRING "Path to SDL_image 1.2" FORCE
)

# System Libraries

# OpenGL
find_package(
   OpenGL REQUIRED
)

# Deal with Platform Specific things
set(
   EXTRA_LIBS
   ""
)

if (APPLE)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(SDL_IMG_LIBRARY SDL_image)
   MARK_AS_ADVANCED (
		COCOA_LIBRARY
		SDL_IMG_LIBRARY
   )
   SET(EXTRA_LIBS ${COCOA_LIBRARY} ${SDL_IMG_LIBRARY})
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
   ${CMAKE_CURRENT_SOURCE_DIR}/TGAEngine/include
   ${SDL_FOLDER}/include
   ${SDL_IMG_FOLDER}/include
   
)

# Get everything together for the executable
add_executable(
   Sandstorms
   WIN32
   MACOSX_BUNDLE
   ${SOURCES}
   ${INCLUDES}
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
