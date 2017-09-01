#include "choose.h"

namespace prob
{
	/*
	* Probability combinatorics choose method.
	* Number of ways to choose r items from n, in which order is not important.
	* Param n - Number of items in "universe" or problem space.
	* Param r - Number of items to choose from universe or space.
	* Return - Number of ways to choose r items from n, in which order is not
	*  important.
	*/
	double choose(int n, int r)
	{
		double c{1.0};
		for(auto i = 0; i != r; ++i)
		{
			c *= (n - i);
			c /= (r - i);
		}
		return c;
	}
}