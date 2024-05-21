set(SRC_FILES test_exercise_price_calculator test_exercise_price_calculator.cpp ${CMAKE_SOURCE_DIR}/src/OptionPricingFunctions.c)
add_executable(test_exercise_price_calculator ${SRC_FILES})
target_include_directories(test_exercise_price_calculator PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern/catch2)
add_test(NAME test_exercise_price_calculator COMMAND test_exercise_price_calculator)

set(SRC_FILES test_option_pricing_functions test_option_pricing_functions.cpp ${CMAKE_SOURCE_DIR}/src/OptionPricingFunctions.c)
add_executable(test_option_pricing_functions ${SRC_FILES})
target_include_directories(test_option_pricing_functions PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern/catch2)
add_test(NAME test_option_pricing_functions COMMAND test_option_pricing_functions)

set(SRC_FILES benchmark_option_pricing_functions.cpp ${CMAKE_SOURCE_DIR}/src/OptionPricingFunctions.c)
add_executable(benchmark_option_pricing_functions ${SRC_FILES})
target_include_directories(benchmark_option_pricing_functions PUBLIC ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/extern/catch2)
add_test(NAME benchmark_option_pricing_functions COMMAND benchmark_option_pricing_functions -r console -o benchmark.txt) 