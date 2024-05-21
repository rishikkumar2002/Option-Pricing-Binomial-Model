# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(MyProgram)

# Set C/C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra)

set(SRC_FILES src/main.c src/OptionPricingFunctions.c)
add_executable(my_program ${SRC_FILES})
target_link_libraries(my_program m)

set(SRC_FILES ${CMAKE_SOURCE_DIR}/src/option_pricing_convergence.c ${CMAKE_SOURCE_DIR}/src/OptionPricingFunctions.c)
add_executable(option_pricing_convergence ${SRC_FILES})
target_include_directories(option_pricing_convergence PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(option_pricing_convergence m)

# expose project root directory to source code so it can find the files
add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
add_executable(generate_convergence_output ${CMAKE_SOURCE_DIR}/src/generate_convergence_output.cpp ${CMAKE_SOURCE_DIR}/src/capture_output.cpp)
target_include_directories(generate_convergence_output PUBLIC ${CMAKE_SOURCE_DIR}/src)

####################### TESTING STUFF STARTS HERE ###########################################################

enable_testing()
add_subdirectory(tests)