#include <stdio.h>
#include <math.h>
#include "OptionPricingFunctions.h"

void print_convergence_european_call(double S0, double volatility, double strike_price,
									 double dividend_yield, double risk_free_rate, double expiration_time,
									 unsigned int depth)
{
	double delta_t = expiration_time / (double)depth;

	// check that choice of delta t is valid
	if (delta_t >= (volatility * volatility) / ((risk_free_rate - dividend_yield) * (risk_free_rate - dividend_yield)))
	{
		printf("Chosen depth is too small\n");
		return;
	}

	double C_exact, P_exact;

	// price put and call options for the current params using black-scholes exact solution
	price_vanilla_option_european_bs(
		S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time, &C_exact, &P_exact);

	double C_numerical = price_vanilla_option_european_induction_call(depth, S0, risk_free_rate,
																	  volatility, strike_price, dividend_yield,
																	  expiration_time);

	double P_numerical = price_vanilla_option_european_induction_put(depth, S0, risk_free_rate,
																	 volatility, strike_price, dividend_yield,
																	 expiration_time);

	double C_error = fabs(C_exact - C_numerical);
	double P_error = fabs(P_exact - P_numerical);

	printf("%u,%f,%f,%f,%f,%f,%f\n", depth, C_numerical, C_exact, C_error, P_numerical, P_exact, P_error);
}

int main()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// set up variables
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// initial asset price
	double S0 = 100.0;

	double volatility = 0.05;

	double strike_price = 95;

	// annual yield proportion from dividend
	double dividend_yield = 0.05;

	// annual risk free yield proportion
	double risk_free_rate = 0.02;

	// 1 year expiration time
	double expiration_time = 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Check the accuracy with respect to Black Scholes solution as depth increases
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("Depth,Call Numerical,Call BS,Call error,Put Numerical,Put BS,Put error\n");
	for (int depth = 10; depth < 400; depth += 10)
		print_convergence_european_call(S0, volatility, strike_price,
										dividend_yield, risk_free_rate, expiration_time,
										depth);
}