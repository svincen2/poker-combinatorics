/************************************************************************************
* Rank.cpp
************************************************************************************/
#include "Rank.h"

namespace cardgames
{
	// Ranks
	Rank Rank::ranks[]
	{
		{0, 0, "None"},
		{1, 1, "Ace"},
		{2, 2, "Deuce"},
		{3, 3, "Three"},
		{4, 4, "Four"}, 
		{5, 5, "Five"}, 
		{6, 6, "Six"}, 
		{7, 7, "Seven"},
		{8, 8, "Eight"},
		{9, 9, "Nine"},
		{10, 10, "Ten"},
		{11, 11, "Jack"},
		{12, 12, "Queen"},
		{13, 13, "King"},
		{14, 14, "Joker"}
	};
	
	// Rank constant references.
	const Rank& Rank::Ace{ranks[1]};
	const Rank& Rank::Deuce{ranks[2]};
	const Rank& Rank::Three{ranks[3]};
	const Rank& Rank::Four{ranks[4]};
	const Rank& Rank::Five{ranks[5]};
	const Rank& Rank::Six{ranks[6]};
	const Rank& Rank::Seven{ranks[7]};
	const Rank& Rank::Eight{ranks[8]};
	const Rank& Rank::Nine{ranks[9]};
	const Rank& Rank::Ten{ranks[10]};
	const Rank& Rank::Jack{ranks[11]};
	const Rank& Rank::Queen{ranks[12]};
	const Rank& Rank::King{ranks[13]};
	const Rank& Rank::Joker{ranks[14]};
	
	
	/*
	* Output a rank to [os].
	* Param os - Output stream to output rank to.
	* Param r - Rank to output to.
	* Return std::ostream& - Reference of output stream.
	*/
	std::ostream& operator<<(std::ostream& os, const Rank& r)
	{
		return os << r.str_rep;
	}
}