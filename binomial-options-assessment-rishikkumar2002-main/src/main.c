#include <stdio.h>
#include <math.h>
#include "OptionPricingFunctions.h"

#define EPSILON 1e-14

int example_usage()
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

	// depth of binomial tree
	unsigned int depth = 20;

	// length of time steps in discretisation
	double delta_t = expiration_time / (double) depth;

	// check that choice of delta t is valid
	if (delta_t >= (volatility * volatility) / ((risk_free_rate - dividend_yield) * (risk_free_rate - dividend_yield)))
	{
		printf("Chosen depth is too small");
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Calculate european call option price with both methods
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double result1 = price_vanilla_option_european_induction_call
	  (depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);

	double result2 = price_vanilla_option_european_recursion_call(
		depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);

	double error_european_call = fabs(result2 - result1);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Print results
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("CALL OPTIONS\n");
	printf("error = %f\n",error_european_call);
	printf("Induction = %f\n",result1);
	printf("Recursion = %f\n",result2);

	if (error_european_call > EPSILON)
	{
		printf("TEST FAILED\n");
		return 1;
	}
	else
	{
		printf("TEST SUCCESS\n");
		return 0;
	}
	double result3 = price_vanilla_option_american_recursion_call
	  (depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);
	double result4 = price_vanilla_option_american_recursion_call(
		depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);
	double error_american_call = fabs(result4 - result3);
	printf("AMERICAN OPTIONS\n");
	printf("error = %f\n",error_american_call);
	printf("Induction = %f\n",result3);
	printf("Recursion = %f\n",result4);
	if (error_american_call > EPSILON)
	{
		printf("TEST FAILED\n");
		return 1;
	}
	else
	{
		printf("TEST SUCCESS\n");
		return 0;
	}
	

}
int example_usage2()
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

	// depth of binomial tree
	unsigned int depth = 20;

	// length of time steps in discretisation
	double delta_t = expiration_time / (double) depth;

	// check that choice of delta t is valid
	if (delta_t >= (volatility * volatility) / ((risk_free_rate - dividend_yield) * (risk_free_rate - dividend_yield)))
	{
		printf("Chosen depth is too small");
		return 1;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Calculate american call option price with both methods
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	double result3 = price_vanilla_option_american_induction_call
	  (depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);

	double result4 = price_vanilla_option_american_recursion_call(
		depth, S0, risk_free_rate,
		volatility, strike_price, dividend_yield,
		expiration_time);

	double error_american_call = fabs(result4 - result3);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Print results
	//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	printf("American OPTIONS\n");
	printf("error = %f\n",error_american_call);
	printf("Induction = %f\n",result3);
	printf("Recursion = %f\n",result4);

	if (error_american_call > EPSILON)
	{
		printf("TEST FAILED\n");
		return 1;
	}
	else
	{
		printf("TEST SUCCESS\n");
		return 0;
	}

}


int main()
{
	example_usage();
	example_usage2();
	
}

