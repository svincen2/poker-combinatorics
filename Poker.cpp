#include "Poker.h"

#include <chrono>
#include <iostream>

namespace cardgames
{
	namespace poker
	{
		/*
		* Copy construct from the given vector of card pointers [vcp].
		* Param vcp - Vector of card pointers.
		*/
		Hand::Hand(const std::vector<Card*>& vcp) 
			:std::vector<Card*>{vcp}
		{
		}
		
		
		/*
		*
		*/
		Hand::Hand(std::vector<Card>& vc)
			:std::vector<Card*>(vc.size())
		{
			for(auto i = 0; i != vc.size(); ++i)
				operator[](i) = &vc[i];
		}
		
		
		/*
		* Move construct from the given vector of card pointers [vcp].
		* Param vcp - Vector of card pointers.
		*/
		Hand::Hand(std::vector<Card*>&& vcp)
			:std::vector<Card*>{vcp}
		{
		}
		
		
		/*
		* Output the hand.
		* Param os - Output stream.
		* Param h - Hand.
		* Return - Reference to the output stream.
		*/
		std::ostream& operator<<(std::ostream& os, const Hand& h)
		{
			os << '{';
			for(auto i = 0; i != h.size(); )
			{
				os << *h[i];
				if(++i != h.size()) os << ", ";
				else os << '}';
			}
			return os;
		}
		
		
		/*
		* Output the hand type [ht].
		* Param os - Output stream.
		* Param ht - Hand type enum literal.
		* Return - Reference to the output stream.
		*/
		std::ostream& operator<<(std::ostream& os, const Hand::Type& ht)
		{
			switch(ht)
			{
			case Hand::Type::High_Card: os << "High card"; break;
			case Hand::Type::Pair: os << "Pair"; break;
			case Hand::Type::Two_Pair: os << "Two pair"; break;
			case Hand::Type::Three_Kind: os << "Three of a kind"; break;
			case Hand::Type::Straight: os << "Straight"; break;
			case Hand::Type::Flush: os << "Flush"; break;
			case Hand::Type::Full_House: os << "Full house"; break;
			case Hand::Type::Four_Kind: os << "Four of a kind"; break;
			case Hand::Type::Straight_Flush: os << "Straight flush"; break;
			case Hand::Type::Royal_Flush: os << "Royal flush"; break;
			case Hand::Type::Five_Kind: os << "Five of a kind"; break;
			default: os << "Unknown";
			}
			return os;
		}
		



		int Hand_Evaluator::rank_counts[];
		int Hand_Evaluator::suit_counts[];
		int Hand_Evaluator::high{-1};
		int Hand_Evaluator::low{100};
		int Hand_Evaluator::high_pair{-1};
		int Hand_Evaluator::num_pairs{0};
		bool Hand_Evaluator::triple{false};
		bool Hand_Evaluator::quad{false};
		bool Hand_Evaluator::straight{false};
		bool Hand_Evaluator::flush{false};
		
		
		void Hand_Evaluator::analyze_ranks()
		{
			// Analyze the rank counts.
			for(auto i = 1; i <= NUM_RANKS; ++i)
			{
				switch(rank_counts[i])
				{
				case 1:
					if(high < i) high = i;
					if(low > i) low = i;
					break;
				case 2:
					++num_pairs;
					if(high_pair < i) high_pair = i;
					break;
				case 3:
					triple = true;
					break;
				case 4:
					quad = true;
					break;
				}
			}
		}
		
		void Hand_Evaluator::analyze_suits()
		{
			for(auto i = 1; i <= NUM_SUITS; ++i)
			{
				if(suit_counts[i] == Hand::SIZE)
				{
					flush = true;
					break;
				}
			}
		}
		
		void Hand_Evaluator::check_straight()
		{
			int diff{high - low};
			if(diff == 4 ||
				(rank_counts[10] == 1 && rank_counts[11] == 1 &&
				 rank_counts[12] == 1 && rank_counts[13] == 1 &&
				 rank_counts[1] == 1))
			{
				straight = true;
			}
		}
		
		void Hand_Evaluator::clear_data()
		{
			for(auto i = 1; i <= NUM_RANKS; ++i) rank_counts[i] = 0;
			for(auto i = 1; i <= NUM_SUITS; ++i) suit_counts[i] = 0;
			high = high_pair = -1;
			low = 100;
			num_pairs = 0;
			triple = quad = straight = flush = false;
		}
		
		void Hand_Evaluator::count_ranks_suits(const Hand& h)
		{
			// Count ranks and suits.
			for(auto c : h)
			{
				rank_counts[static_cast<int>(c->rank())]++;
				suit_counts[static_cast<int>(c->suit())]++;
			}
		}

		
		/*
		* Evaluate the given hand.
		* Param h - Hand of cards to evaluate.
		* Return - Type of hand.
		*/
		Hand::Type Hand_Evaluator::evaluate(const Hand& h)
		{
			clear_data();
			count_ranks_suits(h);
			analyze_ranks();
			// Look at pairing hands first, most common (except 4 and house).
			if(num_pairs == 1)
			{
				if(triple) return Hand::Type::Full_House;
				return Hand::Type::Pair;
			}
			else if(num_pairs == 2) return Hand::Type::Two_Pair;
			if(triple) return Hand::Type::Three_Kind;
			if(quad) return Hand::Type::Four_Kind;
			// Flush, straight, straight flush, royal flush.
			analyze_suits();
			check_straight();
			if(straight)
			{
				if(flush)
				{
					if(low == 1 && high == 13) return Hand::Type::Royal_Flush;
					return Hand::Type::Straight_Flush;
				}
				return Hand::Type::Straight;
			}
			if(flush) return Hand::Type::Flush;
			return Hand::Type::High_Card;
		}
		
		
		/*
		* Count all possible hands given the initial hand and replace card indices.
		* Param h - Initial hand.
		* Param replace - Replace card indices.
		* Return - Hand type counts.
		*/
		std::vector<int> hand_counts(const Hand& h, const std::vector<int>& replace)
		{
			Deck d{Deck::create_without(h, false)};
			Hand h_copy{h};
			std::vector<int> counts(Hand::NUM_TYPES);
			if(replace.size() == 0)
			{
				Hand::Type type{Hand_Evaluator::evaluate(h)};
				counts[static_cast<int>(type)]++;
				return counts;
			}
			else
				hand_count_helper(h_copy, d, counts, replace, 0, replace.size());
			
			return counts;
		}


		/*
		* Recursive helper function for hand_counts function.
		*/
		void hand_count_helper(
			Hand& h,
			Deck& d,
			std::vector<int>& counts, 
			const std::vector<int>& replace,
			int replace_num,
			int size)
		{
			d.mark();
			while(!d.empty())
			{
				h[replace[replace_num]] = d.deal();
				if(replace_num + 1 < size)
					hand_count_helper(h, d, counts, replace, replace_num + 1, size);
				else
				{
					Hand::Type type{Hand_Evaluator::evaluate(h)};
					counts[static_cast<int>(type)]++;
				}
			}
			d.rewind();
		}
		
		
		/*
		* Return the indices associated with the play number.
		* A play number associates the 1's in the binary representation of an
		* integer in the range [0, 31], with the indices of cards to replace in [h].
		* Ex: Play number 3 would return indices 0, 1.
		* Ex: Play number 31 should return indices 0, 1, 2, 3, 4.
		* Param play_num - Play number, between 0 and 31.
		* Return - Indices of cards to hold for the given play number.
		*/
		std::vector<int> play_indices(int play_num)
		{
			std::vector<int> indices{};
			for(auto i = 0; i != 5; ++i)
			{
				if((play_num >> i) & 0x1 == 1) indices.push_back(i);
			}
			return indices;
		}
		
		
		/*
		* Recursive helper function for optimal_play function (below);
		* Param h - Hand used in evaluation.
		* Param rep - Replacement indices.
		*/
		void optimal_play_helper(Hand& h, std::vector<int>& rep, int count)
		{
			if(count > h.size()) return;
			
		}
		
		/*
		* Returns the optimal play for the hand.
		* Param h - Hand to evaluate.
		* Return - Indices indicating which cards to replace.
		*/
		std::vector<int> optimal_play(const Hand& h, Pay_Table& table)
		{
			std::vector<int> best{};
			double max{0.0};
			for(auto i = 0; i != 32; ++i)
			{
				std::vector<int> replace{play_indices(i)};
				std::vector<int> counts{hand_counts(h, replace)};
				int sum{0};
				int total{0};
				for(auto j = 0; j != Hand::NUM_TYPES; ++j)
				{
					total += counts[j];
					sum += counts[j] * table.get(static_cast<Hand::Type>(j));
				}
				double ave{sum / static_cast<double>(total)};
//				std::cout << "ave: " << ave << '\n';
				if(ave > max)
				{
					max = ave;
					best = replace;
				}
			}
			return best;
		}
		
		
	}	
}