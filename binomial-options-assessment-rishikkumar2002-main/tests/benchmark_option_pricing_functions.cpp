#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

extern "C"
{
#include "OptionPricingFunctions.h"
}

TEST_CASE("Benchmark recursion vs induction", "[benchmark]")
{
    double S0 = 100.0;
    double volatility = 0.05;
    double strike_price = 95;
    double dividend_yield = 0.05;
    double risk_free_rate = 0.02;
    double expiration_time = 1;

    //////////////////////////////////////////
    // Induction
    //////////////////////////////////////////
    
    BENCHMARK("induction european depth 5")
    {
        return price_vanilla_option_european_induction_call(5, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    BENCHMARK("induction european depth 10")
    {
        return price_vanilla_option_european_induction_call(10, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("induction european depth 15")
    {
        return price_vanilla_option_european_induction_call(15, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("induction european depth 20")
    {
        return price_vanilla_option_european_induction_call(20, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    //////////////////////////////////////////
    // recursion
    //////////////////////////////////////////

    BENCHMARK("recursion european depth 5")
    {
        return price_vanilla_option_european_recursion_call(5, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    BENCHMARK("recursion european depth 10")
    {
        return price_vanilla_option_european_recursion_call(10, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("recursion european depth 15")
    {
        return price_vanilla_option_european_recursion_call(15, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
     BENCHMARK("recursion european depth 20")
    {
        return price_vanilla_option_european_recursion_call(20, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    //////////////////////////////////////////
    // Induction
    //////////////////////////////////////////
    
    BENCHMARK("induction american depth 5")
    {
        return price_vanilla_option_american_induction_call(5, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    BENCHMARK("induction american depth 10")
    {
        return price_vanilla_option_american_induction_call(10, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("induction american depth 15")
    {
        return price_vanilla_option_american_induction_call(15, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("induction american depth 20")
    {
        return price_vanilla_option_american_induction_call(20, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    //////////////////////////////////////////
    // recursion
    //////////////////////////////////////////

    BENCHMARK("recursion american depth 5")
    {
        return price_vanilla_option_american_recursion_call(5, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };

    BENCHMARK("recursion american depth 10")
    {
        return price_vanilla_option_american_recursion_call(10, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
    BENCHMARK("recursion american depth 15")
    {
        return price_vanilla_option_american_recursion_call(15, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
     BENCHMARK("recursion american depth 20")
    {
        return price_vanilla_option_american_recursion_call(20, S0, risk_free_rate,
                                                            volatility, strike_price, dividend_yield,
                                                            expiration_time);
    };
}