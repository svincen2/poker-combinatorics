#include "Rank_Group.h"

#include "choose.h"

namespace cardgames
{
	/*
	* Return the number of ways to "pull" [count] number of cards from the rank
	* group, less the number of ranks [less].
	* Param count - Count of cards to pull from the rank group.
	* Param less - Number of ranks to be excluded or removed.
	* Return - Number of possible ways to "pull" the number of cards from the ranks.
	*/
	int Rank_Group::pull_cards(int count, int less)
	{
		int ranks{rank_count - less};
		if(count > ranks) return 0;
		int suits{1};
		for(auto i = 0; i != count; ++i)
			suits *= suit_count;
		return prob::choose(ranks, count) * suits;
	}
	
	/*
	* Return the number of ways to "pull" [count] number of pairs from the ranks.
	* Param count - Count of pairs to pull from the rank group.
	* Param less - Number of ranks to be excluded or removed before calculation.
	* Return - Number of possible ways to "pull" the number of cards from the ranks.
	*/
	int Rank_Group::pull_pairs(int count, int less)
	{
		if(suit_count < 2) return 0;
		int ranks{rank_count - less};
		if(count > ranks) return 0;
		int suits{static_cast<int>(prob::choose(suit_count, 2))};
		for(auto i = 1; i != count; ++i)
			suits *= suits;
		return prob::choose(ranks, count) * suits;
	}
	
	/*
	* Return the number of ways to "pull" a triple from the ranks.
	* Param less - Number of ranks to be excluded from the rank group.
	* Return - Number of ways to pull a triple from the rank group, less the
	* number of ranks [less].
	*/
	int Rank_Group::pull_triple(int less)
	{
		if(suit_count < 3) return 0;
		int ranks{rank_count - less};
		if(ranks < 1) return 0;
		return ranks * prob::choose(suit_count, 3);
	}
	
	/*
	* Return the number of ways to "pull" a quad (all four suits of a given rank) 
	* from the ranks.
	* Param less - Number of ranks to be excluded from the rank group.
	* Return - Number of ways to pull a quad from the rank group (less the number
	* of ranks [less]).
	*/
	int Rank_Group::pull_quad(int less)
	{
		if(suit_count < 4) return 0;
		int ranks{rank_count - less};
		if(ranks < 1) return 0;
		return ranks;
	}
}