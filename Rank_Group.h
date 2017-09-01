#ifndef CARDGAMES_RANKGROUP_H
#define CARDGAMES_RANKGROUP_H

namespace cardgames
{
	/*
	* A group of ranks which all have the same number of suits remaining.
	* Rank groups can also calculate how many ways to "pull" an amount of cards,
	* pairs, or a triple from the group of ranks.
	* This is done using combinatorics.
	* author: Sean Vincent.
	* date: 12/15/2015.
	*/
	struct Rank_Group
	{
		int rank_count;
		int suit_count;
		Rank_Group(int rc, int sc) :rank_count{rc}, suit_count{sc} {}
		
		int pull_cards(int, int less = 0);
		int pull_pairs(int, int less = 0);
		int pull_triple(int less = 0);
		int pull_quad(int less = 0);
	};
}
#endif