/************************************************************************************
* Card.cpp
************************************************************************************/
#include "Card.h"

namespace cardgames
{
	/*
	* List of string representations of ranks.
	*/
	std::vector<std::string> rank_strings
	{
		"None", "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King", "Joker"
	};
	
	
	/*
	* Number of valid ranks, including joker.
	*/
	//const int NUM_RANKS{14};

	
	/*
	* Return a string representing the rank given.
	* Param r - Rank.
	* Return - String representation of rank [r].
	*/
	std::string to_string(const Rank& r)
	{
		if(r < Rank::Ace || r > Rank::Joker) return rank_strings[0];
		return rank_strings[static_cast<int>(r)];
	}
	
	
	/*
	* Read a rank from the input stream [is].
	* Param is - Input stream.
	* Param r - Rank.
	* Return - Reference to the input stream.
	*/
	std::istream& operator>>(std::istream& is, Rank& r)
	{
		std::string rank;
		if(is >> rank)
		{
			for(auto i = 0; i != rank_strings.size(); ++i)
				if(rank == rank_strings[i]) 
				{
					r = static_cast<Rank>(i);
					break;
				}
		}
		return is;
	}
	
	
	/*
	* Output the given rank to the given output stream.
	* Param os - Output stream to output rank.
	* Param r - Rank to output.
	* Return - Reference to rank.
	*/
	std::ostream& operator<<(std::ostream& os, const Rank& r)
	{
		return os << to_string(r);
	}


	/*
	* Pre-increment operator for ranks.
	* Does not loop around.
	*/
	Rank& operator++(Rank& r)
	{
		int irank{static_cast<int>(r) + 1};
		return (r = static_cast<Rank>(irank));
	}
	
	
	/*
	* List of string representations of suits.
	*/
	std::vector<std::string> suit_strings
	{
		"None", "Clubs", "Diamonds", "Hearts", "Spades"
	};
	
	
	/*
	* Number of suits.
	*/
	//const int NUM_SUITS = 4;
	
	
	/*
	* Return a string representation of the given suit.
	* Param s - Suit
	* Return - String representation of the suit [s].
	*/
	std::string to_string(const Suit& s)
	{
		if(s < Suit::Clubs || s > Suit::Spades) return suit_strings[0];
		return suit_strings[static_cast<int>(s)];
	}
	
	
	/*
	* Read a suit from the input stream.
	* Param is - Input stream.
	* Param s - Suit.
	* Return - Reference of the input stream.
	*/
	std::istream& operator>>(std::istream& is, Suit& s)
	{
		std::string str{};
		if(is >> str)
		{
			for(auto i = 1; i <= NUM_SUITS; ++i)
				if(str == suit_strings[i])
				{
					s = static_cast<Suit>(i);
					break;
				}
		}
		return is;
	}
	
	
	/*
	* Output the suit [s] to output stream [os].
	* Param os - Output stream.
	* Param s - Suit.
	* Return - Reference to output stream.
	*/
	std::ostream& operator<<(std::ostream& os, const Suit& s)
	{
		return os << to_string(s);
	}
	
	
	/*
	* Pre-increment operator for suits.
	* Does not loop around.
	*/
	Suit& operator++(Suit& s)
	{
		int isuit{static_cast<int>(s) + 1};
		return (s = static_cast<Suit>(isuit));
	}
	
	
	/*
	* Returns whether or not the card is a face card.
	* Return - True iff the rank is a jack, queen, or king.
	*/
	bool Card::is_face() const
	{
		return r == Rank::Jack || r == Rank::Queen || r == Rank::King;
	}
	
	
	/*
	* Equals comparison operator for cards.
	* Param c - Card to compare to.
	* Return - True iff this card's rank and suit are the same as [c]'s.
	*/
	bool Card::operator==(const Card& c)
	{
		return r == c.r && s == c.s;
	}
	
	
	/*
	* Less than comparison of ranks for cards.
	* Param c - Card to compare to.
	* Return - True iff this card's rank is less than c's rank.
	*/
	bool Card::operator<(const Card& c)
	{
		return r < c.r;
	}
	
	
	/*
	* Read a card from the input stream.
	* Param is - Input stream.
	* Param c - Card.
	* Return - Reference to the input stream.
	*/
	std::istream& operator>>(std::istream& is, Card& c)
	{
		is >> c.r >> c.s;
		return is;
	}
	
	
	/*
	* Output a card to the output stream [os].
	* Param os - Output stream.
	* Param c - Card to output.
	* Return std::ostream& - Reference to output stream.
	*/
	std::ostream& operator<<(std::ostream& os, const Card& c)
	{
		return os << c.rank() << ' ' << c.suit();
	}
}