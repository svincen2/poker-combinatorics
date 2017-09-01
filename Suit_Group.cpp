#include "Suit_Group.h"
#include "choose.h"

namespace cardgames
{
	/*
	* Return the number of ways to get a flush.
	* Param replace - Number of cards being replaced.
	*/
	int Suit_Group::flushes(int replace)
	{
		if(replace > rank_count) return 0;
		return suit_count * prob::choose(rank_count, replace);
	}
}