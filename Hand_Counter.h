#ifndef POKER_FIVEDRAW_HANDCOUNTER_H
#define POKER_FIVEDRAW_HANDCOUNTER_H

#include "Card.h"
#include "Poker.h"
#include "Rank_Group.h"
#include "Suit_Group.h"
#include <vector>

namespace fivedraw
{	
	/*
	* Counts possible hands from a given initial set of cards.
	*/
	class Hand_Counter
	{
	public:
		//Hand_Counter(const std::vector<cardgames::Card*>&);
		Hand_Counter(const std::vector<cardgames::Card>&);
		void count_hands();
		int count_of(const cardgames::poker::Hand::Type&);
		int total_possible(int);
		
	private:
		std::vector<cardgames::Card> cards;
		std::vector<int> ranks_left;	// [Ace, King]. 1 based (index 0 ignored).
		std::vector<int> suits_left;	// [Clubs, Spades]. 0 based.
		std::vector<int> counts;		// Type counts.
		std::vector<bool> royals_left;	// Royal flushes still possible.
		std::vector<cardgames::Rank_Group> rank_groups;	// Rank groups.
		std::vector<cardgames::Suit_Group> suit_groups;	// Suit groups.
		
		// Number of total straight and royal flushes.
		static const int SF_COUNT{36};
		static const int RF_COUNT{4};
		
		// Number of straights each rank participates in.
		// Does not account for different suits.
		static const std::vector<int> STRAIGHTS_PER_RANK;
		
		// Private functions.
		void count_highcards();
		void count_flushes();
		void count_four_kinds();
		void count_full_houses();
		void count_pairs();
		void count_royal_flushes();
		void count_straights();
		void count_straight_flushes();
		void count_three_kinds();
		void count_two_pairs();
		std::vector<cardgames::Rank_Group> get_rank_groups();
		std::vector<cardgames::Suit_Group> get_suit_groups();
		void remove_from_counts(const std::vector<cardgames::Card*>&);
		void remove_from_counts(const std::vector<cardgames::Card>&);
	};
}
#endif