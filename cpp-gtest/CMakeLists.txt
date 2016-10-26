cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
PROJECT(demo)

add_subdirectory(googletest)
add_subdirectory(test)

add_executable(${PROJECT_NAME}
	main.cpp
	)
