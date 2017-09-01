#include "Hand_Counter.h"
#include "choose.h"
#include <algorithm>
#include <iostream>

namespace fivedraw
{
	/*
	* The number of straights each rank can appear in.
	* For example, the Ace appears in two straights, the lowest and the highest.
	*/
	const std::vector<int> Hand_Counter::STRAIGHTS_PER_RANK
	{
		1, 2, 3, 4, 5, 5, 5, 5, 5, 4, 3, 2, 1
	};
	
	
	/*
	* Construct a hand counter with the given initial cards.
	* Param cards - Initial cards.
	*/
	Hand_Counter::Hand_Counter(const std::vector<cardgames::Card>& vc)
		:cards{vc},
		ranks_left(cardgames::NUM_RANKS, cardgames::NUM_SUITS),
		suits_left(cardgames::NUM_SUITS, cardgames::NUM_RANKS - 1),
		royals_left(cardgames::NUM_SUITS, true),
		rank_groups{}, suit_groups{},
		counts(cardgames::poker::Hand::NUM_TYPES, 0)
	{
		remove_from_counts(cards);
		rank_groups = get_rank_groups();
		suit_groups = get_suit_groups();
	}
	
	
	/*
	* Count all possible hands. !
	*/
	void Hand_Counter::count_hands()
	{
		count_royal_flushes();
		count_straight_flushes();
		count_four_kinds();
		count_full_houses();
		count_flushes();
		count_straights();
		count_three_kinds();
		count_two_pairs();
		count_pairs();
		count_highcards();
	}
	
	
	/*
	* Count the number of possible high cards. (replace 5 only) !
	* The number of high card hands is the total number of possible hands
	* less every other type of hand.
	* Return - Number of high card hands possible. !
	*/
	void Hand_Counter::count_highcards()
	{
		using namespace cardgames::poker;
		int total{0};
		for(auto i = 1; i != cardgames::poker::Hand::NUM_TYPES; ++i)
		{
			total += counts[i];
		}
		counts[static_cast<int>(Hand::Type::High_Card)] = total_possible(5) - total;
	}
	
	
	/*
	* Count the number of flushes possible.
	* Currently only works for replacing all 5 cards. !
	* Return - Count of possible flushes replacing all 5 cards. !
	*/
	void Hand_Counter::count_flushes()
	{
		using namespace cardgames::poker;
		int count{0};
		for(auto group : suit_groups)
		{
			count += group.flushes(5);
		}
		count -= counts[static_cast<int>(Hand::Type::Straight_Flush)];
		count -= counts[static_cast<int>(Hand::Type::Royal_Flush)];
		counts[static_cast<int>(Hand::Type::Flush)] = count;
	}
	
	
	/*
	* Count the number of four of a kinds possible.
	* Currently only works for replacing all 5 cards. !
	*/
	void Hand_Counter::count_four_kinds()
	{
		using namespace cardgames::poker;
		for(auto i = 0; i != rank_groups.size(); ++i)
		{
			if(rank_groups[i].suit_count == cardgames::NUM_SUITS)
			{
				// Only rank group that can possibly make 4's.
				int four_count{rank_groups[i].pull_quad()};
				int card_count{0};
				for(auto j = 0; j != rank_groups.size(); ++j)
				{
					if(j == i) card_count += rank_groups[j].pull_cards(1, 1);
					else card_count += rank_groups[j].pull_cards(1);
				}
				int total{four_count * card_count};
				counts[static_cast<int>(Hand::Type::Four_Kind)] = total;
			}
		}
	}
	
	
	/*
	* Count the number of full houses possible.
	* Currently only works for replace 5 cards. !
	*/
	void Hand_Counter::count_full_houses()
	{
		int total{0};
		for(auto i = 0; i != rank_groups.size(); ++i)
		{
			int trips{rank_groups[i].pull_triple()};
			if(trips > 0)
			{
				int pair{0};
				for(auto j = 0; j != rank_groups.size(); ++j)
				{
					if(i == j) pair += rank_groups[j].pull_pairs(1, 1);
					else pair += rank_groups[j].pull_pairs(1);
				}
				total += trips * pair;
			}
		}
		counts[static_cast<int>(cardgames::poker::Hand::Type::Full_House)] = total;
	}
	
	
	/*
	* Return the count found by Hand_Counter for the given hand type.
	* Param type - Hand type, such as two pair or full house.
	* Return - Count of possible hand of the given type.
	*/
	int Hand_Counter::count_of(const cardgames::poker::Hand::Type& type)
	{
		return counts[static_cast<int>(type)];
	}
	
	
	/*
	* Count the number of pairs possible. (replace 5 only) !
	* Return - Total number of pairs possible. !
	*/
	void Hand_Counter::count_pairs()
	{
		// TODO !!!
	}
	
	
	/*
	* Count the number of royal flushes possible.
	* Currently works for replacing all 5 cards only. !
	*/
	void Hand_Counter::count_royal_flushes()
	{
		int count{RF_COUNT};
		for(auto i = 0; i != royals_left.size(); ++i)
			if(!royals_left[i]) --count;
		counts[static_cast<int>(cardgames::poker::Hand::Type::Royal_Flush)] = count;
	}
	
	
	/*
	* Count the number of straights possible.
	* Currently only works for replacing all 5 cards. !
	*/
	void Hand_Counter::count_straights()
	{
		using namespace cardgames::poker;
		int total{0};
		for(auto i = 1; i <= 10; ++i)
		{
			int count{1};
			for(auto j = 0; j != 5; ++j)
			{
				count *= (i + j == 14 ? ranks_left[1] : ranks_left[i + j]);
			}
			total += count;
		}
		total -= counts[static_cast<int>(Hand::Type::Straight_Flush)];
		total -= counts[static_cast<int>(Hand::Type::Royal_Flush)];
		counts[static_cast<int>(Hand::Type::Straight)] = total;
	}
	
	
	/*
	* Count the number of straight flushes possible.
	* Currently only works for replace all 5 cards. !
	*/
	void Hand_Counter::count_straight_flushes()
	{
		using namespace cardgames::poker;
		// Remaining straights grid.
		std::vector<std::vector<int>> straights
		{
			std::vector<int>{STRAIGHTS_PER_RANK},
			std::vector<int>{STRAIGHTS_PER_RANK},
			std::vector<int>{STRAIGHTS_PER_RANK},
			std::vector<int>{STRAIGHTS_PER_RANK}
		};
		int count{SF_COUNT};
		std::sort(cards.begin(), cards.end());
		for(auto c : cards)
		{
			int r{static_cast<int>(c.rank()) - 1};
			int s{static_cast<int>(c.suit()) - 1};
			int val{straights[s][r]};
			if(val < 0) continue;
			count -= val;
			for(auto i = 0; i != 5; ++i)
				if(r + i < straights[0].size())
					straights[s][r + i] -= val;
		}
		counts[static_cast<int>(Hand::Type::Straight_Flush)] = count;
	}
	
	
	/*
	* Count the number of three of a kinds possible.
	* Currently only works for replace all 5 cards. !
	*/
	void Hand_Counter::count_three_kinds()
	{
		int total{0};
		for(int i = 0; i != rank_groups.size(); ++i)
		{
			if(rank_groups[i].suit_count >= 3)
			{
				int trip{rank_groups[i].pull_triple()};
//				std::cout << "trip: " << trip << '\n';
				int cards{0};
				for(auto j = 0; j != rank_groups.size(); ++j)
				{
					for(auto k = 2; k > 0; --k)
					{
						int first_pull{0};
						if(i == j) first_pull = rank_groups[j].pull_cards(k, 1);
						else first_pull = rank_groups[j].pull_cards(k);
//						std::cout << "\tfirst_pull: " << first_pull << '\n';
						if(k == 2)
						{
							cards += first_pull;
						}
						if(j + 1 == rank_groups.size())
						{
//							std::cout << "\tj + 1 == rank_groups.size()\n";
							break;
						}
						for(auto m = j + 1; m < rank_groups.size(); ++m)
						{
							for(auto n = 2 - k; n > 0; --n)
							{
								int second_pull{0};
								if(i == m) 
									second_pull = rank_groups[m].pull_cards(n, 1);
								else second_pull = rank_groups[m].pull_cards(n);
//								std::cout << "\t\tsecond_pull: " << second_pull << '\n';
								cards += first_pull * second_pull;
//								std::cout << "\t\tfirst_pull * second_pull: " << (first_pull * second_pull) << '\n';
//								std::cout << "\t\tcards: " << cards << '\n';
							}
						}
					}
				}
				total += trip * cards;
			}
		}
		counts[static_cast<int>(cardgames::poker::Hand::Type::Three_Kind)] = total;
	}
	
	
	/*
	* Count the number of two pairs possible. !
	*/
	void Hand_Counter::count_two_pairs()
	{
		// TODO !!!
	}
	
	
	/*
	* Return a list of rank groups describing the remaining cards.
	* Return - Vector of rank groups.
	*/
	std::vector<cardgames::Rank_Group> Hand_Counter::get_rank_groups()
	{
		std::vector<int> remaining(5, 0);	// Index == # suits remaining.
		for(auto i = 1; i != ranks_left.size(); ++i)
		{
			remaining[ranks_left[i]]++;
		}
		std::vector<cardgames::Rank_Group> groups{};
		for(auto i = 0; i != remaining.size(); ++i)
		{
			if(remaining[i] > 0) groups.push_back({remaining[i], i});
		}
		return groups;
	}

	
	/*
	* Return a list of suit groups describing the remaining cards.
	* Return - Vector of suit groups.
	*/
	std::vector<cardgames::Suit_Group> Hand_Counter::get_suit_groups()
	{
		std::vector<int> remaining(14, 0);	// Index == # ranks remaining.
		for(auto i = 0; i != suits_left.size(); ++i)
		{
			remaining[suits_left[i]]++;
		}
		std::vector<cardgames::Suit_Group> groups{};
		for(auto i = 0; i != remaining.size(); ++i)
		{
			if(remaining[i] > 0) groups.push_back({remaining[i], i});
		}
		return groups;
	}
	
	
	/* !! Deprecated !!
	* Remove the cards from the count of ranks and suits left.
	* Param cards - Cards to remove.
	*/
	void Hand_Counter::remove_from_counts(const std::vector<cardgames::Card*>& vc)
	{
		for(auto c : vc)
		{
			ranks_left[static_cast<int>(c->rank())]--;
			suits_left[static_cast<int>(c->suit()) - 1]--;
			if(c->rank() == cardgames::Rank::Ace || 
			   c->rank() >= cardgames::Rank::Ten)
			{
				royals_left[static_cast<int>(c->suit()) - 1] = false;
			}
		}
	}
	
	
	/*
	* Remove the cards from the count of ranks and suits left.
	* Param cards - Cards to remove.
	*/
	void Hand_Counter::remove_from_counts(const std::vector<cardgames::Card>& vc)
	{
		for(auto c : vc)
		{
			ranks_left[static_cast<int>(c.rank())]--;
			suits_left[static_cast<int>(c.suit()) - 1]--;
			if(c.rank() == cardgames::Rank::Ace ||
			   c.rank() >= cardgames::Rank::Ten)
			{
				royals_left[static_cast<int>(c.suit()) - 1] = false;
			}
		}
	}

	
	/*
	* Return the total number of possible hands.
	*/
	int Hand_Counter::total_possible(int replace)
	{
		const int deck_size{52};
		int n{deck_size - static_cast<int>(cards.size())};
		return prob::choose(n, replace);
	}
}