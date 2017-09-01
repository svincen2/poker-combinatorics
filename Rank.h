/************************************************************************************
* Rank.h
************************************************************************************/
#ifndef CARDGAMES_RANK_H
#define CARDGAMES_RANK_H

#include <ostream>
#include <string>
#include <vector>

namespace cardgames
{
	/*
	* A Rank of a playing card.
	* Rank is essentially an enum, with separate ording and worth values, which also
	* stores the string printed when the rank is output to a std::ostream.
	*/
	class Rank
	{
	public:
		Rank(const Rank&) = delete;
		Rank(Rank&&) = delete;
		Rank& operator=(const Rank&) = delete;
		Rank& operator=(Rank&&) = delete;
		
		// Rank constant references.
		static const Rank& Ace;
		static const Rank& Deuce;
		static const Rank& Three;
		static const Rank& Four;
		static const Rank& Five;
		static const Rank& Six;
		static const Rank& Seven;
		static const Rank& Eight;
		static const Rank& Nine;
		static const Rank& Ten;
		static const Rank& Jack;
		static const Rank& Queen;
		static const Rank& King;
		static const Rank& Joker;
		
		static void set_value(const Rank& r, int v) {ranks[r.index].val = v;}
		static const size_t size = 14;
		
		const std::string& str() const { return str_rep; }
		int value() const { return val; }
		
		friend std::ostream& operator<<(std::ostream&, const Rank&);
		
	private:
		static Rank ranks[15];
		
		// Constructor.
		Rank(int i, int value, const std::string& str) 
			:index{i}, val{value}, str_rep{str}
		{
		}
		
		int index;
		int val;
		std::string str_rep;
	};
}
#endif