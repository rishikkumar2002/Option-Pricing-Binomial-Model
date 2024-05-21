#define CATCH_CONFIG_MAIN
#include "catch.hpp"

extern "C"
{
#include "OptionPricingFunctions.h"
}

double function_which_uses_exercise_profit(double strike_price, double spot_price, option_fxn exercise_profit)
{
    return exercise_profit(strike_price, spot_price);
}

TEST_CASE("test call option calculator", "[tests]")
{
    REQUIRE(function_which_uses_exercise_profit(100, 110, &call_exercise_profit) == 10);
    REQUIRE(function_which_uses_exercise_profit(100, 90, &call_exercise_profit) == 0);
    REQUIRE(function_which_uses_exercise_profit(100, 100, &call_exercise_profit) == 0);
}

TEST_CASE("test put option calculator", "[tests]")
{
    REQUIRE(function_which_uses_exercise_profit(100, 110, &put_exercise_profit) == 0);
    REQUIRE(function_which_uses_exercise_profit(100, 90, &put_exercise_profit) == 10);
    REQUIRE(function_which_uses_exercise_profit(100, 100, &put_exercise_profit) == 0);
}
