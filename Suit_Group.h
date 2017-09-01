#ifndef CARDGAMES_SUITGROUP_H
#define CARDGAMES_SUITGROUP_H

#include "Card.h"

namespace cardgames
{
	/*
	*
	*/
	struct Suit_Group
	{
		int suit_count{cardgames::NUM_SUITS};
		int rank_count{cardgames::NUM_RANKS - 1};
		Suit_Group(int sc, int rc) :suit_count{sc}, rank_count{rc} {}
		int flushes(int);
	};
}
#endif