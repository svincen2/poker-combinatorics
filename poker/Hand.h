#ifndef CARDGAMES_POKER_HAND_H
#define CARDGAMES_POKER_HAND_H

#include "..\Card.h"

namespace cardgames
{
	namespace poker
	{
		class Hand
		{
		public:
			// Poker hand types.
			enum Type
			{
				High_Card, Pair, Two_Pair, Three_Kind, Straight, Flush,
				Full_House, Four_Kind, Straight_Flush, Royal_Flush, Five_Kind
			};
			
			// Hand analysis.
			class Analysis
			{
			public:
				int high_card{-1};
				int low_card{100};
				int num_pairs{0};
				int pair{-1};
				bool triple{false};
				bool quad{false};
				bool straight{false};
				bool flush{false};
				
				Analysis(Hand*);
				Analysis(Analysis&&);
				Analysis(const Analysis&) = delete;
				~Analysis() { delete[] ranks; }
				void analyze_ranks();
				void check_straight();
				void count_ranks_and_check_flush();
				int rank(int i) { return ranks[i]; }
				
			private:
				int* ranks;
				Hand* hand;
			};
			
			using iterator = std::vector<Card*>::iterator;
			Hand(const std::vector<Card*>& vcp) :cards{vcp} {}
			Analysis analysis();
			iterator begin() { return cards.begin(); }
			iterator end() { return cards.end(); }
			size_t size() { return cards.size(); }
			
		private:
			std::vector<Card*> cards{};
		};
	}
}
#endif