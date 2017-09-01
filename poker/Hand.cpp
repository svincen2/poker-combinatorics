#include "Hand.h"

#include <iostream>

namespace cardgames
{
	namespace poker
	{
		/*
		* Hand::Analysis constructor.
		*/
		Hand::Analysis::Analysis(Hand* hp)
			:ranks{new int[NUM_RANKS]}, hand{hp}
		{
			for(auto i = 0; i != NUM_RANKS; ++i)
				ranks[i] = 0;
		}
		
		/*
		* Hand::Analysis move constructor.
		*/
		Hand::Analysis::Analysis(Analysis&& a)
			:high_card{a.high_card}, low_card{a.low_card},
			num_pairs{a.num_pairs}, pair{a.pair},
			triple{a.triple}, quad{a.quad},
			straight{a.straight}, flush{a.flush},
			ranks{a.ranks}, hand{a.hand}
		{
			a.ranks = nullptr;
		}
		
		
		/*
		*
		*/
		void Hand::Analysis::analyze_ranks()
		{
			
		}
		
		
		/*
		*
		*/
		void Hand::Analysis::check_straight()
		{
			
		}
		
		
		/*
		* Count the ranks in the hand associated with this Analysis object.
		*/
		void Hand::Analysis::count_ranks_and_check_flush()
		{
			int suits[NUM_SUITS];
			for(auto i = 0; i != NUM_SUITS; ++i) suits[i] = 0;
			
			for(auto c : *hand)
			{
				ranks[static_cast<int>(c->rank()) - 1]++;
				int s{static_cast<int>(c->suit()) - 1};
				suits[s]++;
				if(suits[s] == 5) flush = true;
			}
		}
		
		
		/*
		*
		*/
		//Hand::Hand(const std::vector<Card*>& vcp) :cards{vcp} {}
		
		
		/*
		* Analyze the hand and return the analysis results.
		*/
		Hand::Analysis Hand::analysis()
		{
			std::cout << "analysis()\n";
			Analysis results{this};
			results.count_ranks_and_check_flush();
			results.analyze_ranks();
			results.check_straight();
			//results.check_flush();
			return results;
		}
	}
}