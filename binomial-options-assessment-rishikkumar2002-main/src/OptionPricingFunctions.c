#define ERROR -99999.0
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

#include "OptionPricingFunctions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ADD FUNCTIONS HERE IF REQUIRED
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double normal_CDF(double x)
{
	return 0.5 * erfc(-x * M_SQRT1_2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ADD FUNCTIONS HERE IF REQUIRED (END)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// IMPLEMENT THE FUNCTIONS IN THIS SECTION
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void price_vanilla_option_european_bs(double S0, double r,
									  double volatility, double strike_price, double dividend_yield,
									  double expiration_time, double *call_price, double *put_price) {
										// Calculate necessary parameters
    double d1 = (log(S0 / strike_price) + (r - dividend_yield + 0.5 * pow(volatility, 2)) * expiration_time)
                / (volatility * sqrt(expiration_time));
    double d2 = d1 - volatility * sqrt(expiration_time);

    // Calculate call and put prices using the Black-Scholes formula
    *call_price = S0 * exp(-dividend_yield * expiration_time) * normal_CDF(d1)
                - strike_price * exp(-r * expiration_time) * normal_CDF(d2);
    
    *put_price = strike_price * exp(-r * expiration_time) * normal_CDF(-d2)
                - S0 * exp(-dividend_yield * expiration_time) * normal_CDF(-d1);
									  }




double price_vanilla_option_european_recursion(unsigned int i, unsigned int j,
											   unsigned int depth, double S0, double r,
											   double volatility, double strike_price, double dividend_yield,
											   double expiration_time, option_fxn exercise_profit_calculator)
{
	// GENERAL NOTE about the option_fxn parameter - the code for this function will be the same whether pricing a call or a put option,
	// achieve this by calling exercise_profit_calculator variable like:
	// exercise_profit_calculator(strike_price, spot_price) whenever you need to calculate the exercise price.
	// For example if using for call option functions
	// -> exercise_profit_calculator(strike_price, spot_price) is equivalent to max(spot_price - strike_price, 0)

	//////////////// YOUR CODE HERE ////////////////
	double delta_t = expiration_time / depth;

	double up = exp(volatility * sqrt(delta_t));
	double down = 1 / up;
	double p = (exp((r - dividend_yield) * delta_t) - down) / (up - down);
	
	if(i == depth) {
		double j_down = (double) j;
		double spot_price = S0 * pow(up, 2 * j_down - depth);
		return exercise_profit_calculator(strike_price, spot_price);
	}

		double value_up = price_vanilla_option_european_recursion(i+1,j+1,depth,S0,r,volatility,strike_price,dividend_yield,expiration_time,exercise_profit_calculator);
		double value_down = price_vanilla_option_european_recursion(i+1,j,depth,S0,r,volatility,strike_price,dividend_yield,expiration_time,exercise_profit_calculator);

		return exp(-r * delta_t) * (p * value_up + (1 - p) * value_down);
}
	

	


double price_vanilla_option_american_recursion(unsigned int i, unsigned int j,
											   unsigned int depth, double S0, double r,
											   double volatility, double strike_price, double dividend_yield,
											   double expiration_time, option_fxn exercise_profit_calculator)
{
	//////////////// YOUR CODE HERE ////////////////
	{
    // GENERAL NOTE about the option_fxn parameter - the code for this function will be the same whether pricing a call or a put option,
    // achieve this by calling exercise_profit_calculator variable like:
    // exercise_profit_calculator(strike_price, spot_price) whenever you need to calculate the exercise price.
    // For example, if using for call option functions
    // -> exercise_profit_calculator(strike_price, spot_price) is equivalent to max(spot_price - strike_price, 0)

    ////////////////// YOUR CODE HERE ////////////////
    double delta_t = expiration_time / depth;

    double up = exp(volatility * sqrt(delta_t));
    double down = 1 / up;
    double p = (exp((r - dividend_yield) * delta_t) - down) / (up - down);

    if (i == depth)
    {
        double j_down = (double)j;
        double spot_price = S0 * pow(up, 2 * j_down - depth);
        return exercise_profit_calculator(strike_price, spot_price);
    }

    double value_up = price_vanilla_option_american_recursion(i + 1, j + 1, depth, S0, r, volatility, strike_price, dividend_yield, expiration_time, exercise_profit_calculator);
    double value_down = price_vanilla_option_american_recursion(i + 1, j, depth, S0, r, volatility, strike_price, dividend_yield, expiration_time, exercise_profit_calculator);

    // Calculate exercise value at the current node
	double j_down = (double)j;

    double exercise_value = exercise_profit_calculator(strike_price, S0 * pow(up, 2 * j_down - i));

    // Final option value at the current node is the maximum of continuation and exercise values
    return fmax(exp(-r * delta_t) * (p * value_up + (1 - p) * value_down), exercise_value);

	}
	

	
	 
}
	


double price_vanilla_option_european_induction(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time, option_fxn exercise_profit_calculator)
{
	// array to store the option values at each timestep
	double *depth_values = (double *)malloc((depth + 1) * sizeof(double));

	// return error code if memory allocation failed
	if (depth_values == NULL)
		return ERROR;

	//////////////// YOUR CODE HERE ////////////////
	double delta_t = expiration_time / depth;
    double u = exp(volatility * sqrt(delta_t));
    double d = 1 / u;
    double p = (exp((r - dividend_yield) * delta_t) - d) / (u - d);

    // Initialize values at maturity
    for (unsigned int j = 0; j <= depth; ++j) {
		double j_down = (double) j;
        double spot_price = S0 * pow(u, 2.0 * j_down - depth);
        depth_values[j] = exercise_profit_calculator(strike_price, spot_price);
    }

    // Backward induction
    for (int i = depth - 1; i >= 0; --i) {
        for (unsigned int j = 0; j <= i; ++j) {
            depth_values[j] = exp(-r * delta_t) * (p * depth_values[j + 1] + (1 - p) * depth_values[j]);
        }
    }

    double ret = depth_values[0];

    // free the memory allocated for the array
    free(depth_values);

    return ret;

	
}



double price_vanilla_option_american_induction(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time, option_fxn exercise_profit_calculator)
{
	// array to store the option values at each timestep
	double *depth_values = (double *)malloc((depth + 1) * sizeof(double));

	// return error code if memory allocation failed
	if (depth_values == NULL)
		return ERROR;

	//////////////// YOUR CODE HERE ////////////////
	double delta_t = expiration_time / depth;
    double up = exp(volatility * sqrt(delta_t));
    double down = 1 / up;
    double p = (exp((r - dividend_yield) * delta_t) - down) / (up - down);

    // Initialize values at maturity
    for (unsigned int j = 0; j <= depth; ++j)
    {
        double j_down = (double)j;
        double spot_price = S0 * pow(up, 2.0 * j_down - depth);
        depth_values[j] = exercise_profit_calculator(strike_price, spot_price);
    }

    // Backward induction
    for (int i = depth - 1; i >= 0; --i)
    {
        for (unsigned int j = 0; j <= i; ++j)
	
        {
			double j_d = (double) j;
            double spot_price = S0 * pow(up, 2 * j_d - i);
            double exercise_value = exercise_profit_calculator(strike_price, spot_price);
            depth_values[j] = fmax(exercise_value, exp(-r * delta_t) * (p * depth_values[j + 1] + (1 - p) * depth_values[j]));
        }
    }

	
	double ret = depth_values[0];

	// free the memory allocated for the array
	free(depth_values);

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DO NOT MODIFY ANYTHING BELOW THIS LINE
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double call_exercise_profit(double strike_price, double spot_price)
{
	return fmax(spot_price - strike_price, 0);
}

double put_exercise_profit(double strike_price, double spot_price)
{
	return fmax(strike_price - spot_price, 0);
}

double price_vanilla_option_european_recursion_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_european_recursion(0, 0,
												   depth, S0, r,
												   volatility, strike_price, dividend_yield,
												   expiration_time, &call_exercise_profit);
}

double price_vanilla_option_european_recursion_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_european_recursion(0, 0,
												   depth, S0, r,
												   volatility, strike_price, dividend_yield,
												   expiration_time, &put_exercise_profit);
}

double price_vanilla_option_american_recursion_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_american_recursion(0, 0,
												   depth, S0, r,
												   volatility, strike_price, dividend_yield,
												   expiration_time, &call_exercise_profit);
}

double price_vanilla_option_american_recursion_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_american_recursion(0, 0,
												   depth, S0, r,
												   volatility, strike_price, dividend_yield,
												   expiration_time, &put_exercise_profit);
}

double price_vanilla_option_european_induction_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_european_induction(
		depth, S0, r,
		volatility, strike_price, dividend_yield,
		expiration_time, &call_exercise_profit);
}

double price_vanilla_option_european_induction_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_european_induction(
		depth, S0, r,
		volatility, strike_price, dividend_yield,
		expiration_time, &put_exercise_profit);
}

double price_vanilla_option_american_induction_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_american_induction(
		depth, S0, r,
		volatility, strike_price, dividend_yield,
		expiration_time, &call_exercise_profit);
}

double price_vanilla_option_american_induction_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time)
{
	return price_vanilla_option_american_induction(
		depth, S0, r,
		volatility, strike_price, dividend_yield,
		expiration_time, &put_exercise_profit);
}