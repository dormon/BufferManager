cmake_minimum_required (VERSION 2.6)
project (BufferManager)
set (ProjectName BufferManager)

add_library(${ProjectName} STATIC
	src/CBufferManager.cpp
	)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/modules/")

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
	message("GLEW found")
	include_directories(${GLEW_INCLUDE_DIR})
	target_link_libraries(${ProjectName} ${GLEW_LIBRARY})
else(GLEW_FOUND)
	message("GLEW not found")
endif(GLEW_FOUND)


install(FILES
	src/CBufferManager.hpp
	DESTINATION include/${ProjectName}
	)

install(TARGETS ${ProjectName}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)
