#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for calculating exercise profit
//////////////////////////////////////////////////////////////////////////////////////////////////////

double call_exercise_profit(double strike_price, double spot_price);

double put_exercise_profit(double strike_price, double spot_price);

// This allows us to pass call and put exercise profit calculation functions as option_fxn type arguments
typedef double (*option_fxn)(double, double);

//////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions for pricing european and american options
//////////////////////////////////////////////////////////////////////////////////////////////////////

// Use Black-Scholes analytical formuala to price european options
// 
// Input:
// Initial asset price, S0
// Risk free rate, r
// Asset volatility, volatility
// Strike price of option, strike_price
// Yearly % yield from asset dividends, dividend_yield
// Option expiry time, expiration_time
// 
// Output
// The value of a call option, call_price
// The value of a put option, put_price
//

void price_vanilla_option_european_bs(double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time, double* call_price, double* put_price);

// Use recursion method to price european/american options
//
// Input:
// Depth of the binomial tree, depth
// Initial asset price, S0
// Risk free rate, r
// Asset volatility, volatility
// Strike price of option, strike_price
// Yearly % yield from asset dividends, dividend_yield
// Option expiry time, expiration_time
//

double price_vanilla_option_european_recursion_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_european_recursion_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_american_recursion_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_american_recursion_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

// Use backward induction method to price european/american options
//
// Input:
// Depth of the binomial tree, depth
// Initial asset price, S0
// Risk free rate, r
// Asset volatility, volatility
// Strike price of option, strike_price
// Yearly % yield from asset dividends, dividend_yield
// Option expiry time, expiration_time
//

double price_vanilla_option_european_induction_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_european_induction_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_american_induction_call(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);

double price_vanilla_option_american_induction_put(
	unsigned int depth, double S0, double r,
	double volatility, double strike_price, double dividend_yield,
	double expiration_time);