#ifndef POKER_H
#define POKER_H

#include "Card.h"
#include "Deck.h"
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace cardgames
{
	namespace poker
	{
		/*
		* Poker hand.
		*/
		class Hand : public std::vector<Card*>
		{
		public:
			enum class Type
			{
				High_Card, Pair, Two_Pair, Three_Kind, Straight, Flush, Full_House,
				Four_Kind, Straight_Flush, Royal_Flush, Five_Kind
			};
			static const int NUM_TYPES = 11;
			static const int SIZE = 5;
			static Hand::Type evaluate(const Hand&);
			
			Hand(const std::vector<Card*>&);
			Hand(std::vector<Card>&);
			Hand(std::vector<Card*>&&);
				
		private:
		};
		
		std::ostream& operator<<(std::ostream&, const Hand::Type&);
		std::ostream& operator<<(std::ostream&, const Hand&);

		
		class Hand_Evaluator
		{
		public:
			static Hand::Type evaluate(const Hand&);
		
		private:
			static int rank_counts[NUM_RANKS + 1];
			static int suit_counts[NUM_SUITS + 1];
			static int high;
			static int low;
			static int high_pair;
			static int num_pairs;
			static bool triple;
			static bool quad;
			static bool flush;
			static bool straight;

			static void clear_data();
			static void check_straight();
			static void count_ranks_suits(const Hand&);
			static void analyze_ranks();
			static void analyze_suits();
		};		
		
		
		std::vector<int> hand_counts(const Hand&, const std::vector<int>&);
		
		void hand_count_helper(Hand&,
		                       Deck&,
		                       std::vector<int>&, 
							   const std::vector<int>&, 
							   int,
							   int);
		

		class Pay_Table
		{
		public:
			Pay_Table() :tbl{} {}
			int get(const Hand::Type& k) { return tbl[k]; }
			void put(const Hand::Type& k, int v) { tbl[k] = v; }
		private:
			std::map<Hand::Type, int> tbl;
		};
		
		std::vector<int> optimal_play(const Hand&, Pay_Table&);
		
		
		
	}
}
#endif