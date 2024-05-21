#define CATCH_CONFIG_MAIN
#include "catch.hpp"

extern "C"
{
#include "OptionPricingFunctions.h"
}

// error tolerance for floating point comparisons
#define EPSILON 1e-14

void european_call_error(double S0, double volatility, double strike_price, double risk_free_rate, double dividend_yield, double expiration_time, unsigned int depth)
{
	double delta_t = expiration_time / (double) depth;

    REQUIRE(delta_t < (volatility * volatility) / ((risk_free_rate - dividend_yield) * (risk_free_rate - dividend_yield)));

	// get induction and recursion answers for the same option pricing problem
	double induction_answer = price_vanilla_option_european_induction_call
	  (depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);
	double recursion_answer = price_vanilla_option_european_recursion_call(
		depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);

    // check answers are equal within the tolerance epsilon
    REQUIRE(induction_answer == Approx(recursion_answer).epsilon(EPSILON));
}

TEST_CASE("european call depth 1", "[tests]")
{
    european_call_error(100.0, 0.05, 95, 0.02, 0.05, 1, 2);
}





