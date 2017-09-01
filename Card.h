/************************************************************************************
* Card.h
************************************************************************************/
#ifndef CARDGAMES_CARD_H
#define CARDGAMES_CARD_H

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace cardgames
{
	/*
	* Playing card rank.
	*/
	enum class Rank
	{
		Ace = 1, Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
		Jack, Queen, King, Joker
	};
	extern std::vector<std::string> rank_strings;
	//extern const int NUM_RANKS;
	std::string to_string(const Rank&);
	std::istream& operator>>(std::istream&, Rank&);
	std::ostream& operator<<(std::ostream&, const Rank&);
	Rank& operator++(Rank&);
	
	/*
	* Playing card suit.
	*/
	enum class Suit
	{
		Clubs = 1, Diamonds, Hearts, Spades
	};
	extern std::vector<std::string> suit_strings;
	//extern const int NUM_SUITS;
	std::string to_string(const Suit&);
	std::istream& operator>>(std::istream&, Suit&);
	std::ostream& operator<<(std::ostream&, const Suit&);
	Suit& operator++(Suit&);
	
	/*
	* Number of ranks and suits.
	*/
	enum {NUM_RANKS = 14, NUM_SUITS = 4};
	
	
	/*
	* A player card.
	* Author: Sean Vincent.
	* Date: 12/7/2015.
	*/
	class Card
	{
	public:
		Card() :r{}, s{} {}
		Card(const Rank& rr, const Suit& ss) :r{rr}, s{ss} {}
		bool is_ace() const { return r == Rank::Ace; }
		bool is_face() const;
		bool is_joker() const { return r == Rank::Joker; }
		const Rank& rank() const { return r; }
		const Suit& suit() const { return s; }
		static Card make_joker() { return Card{Rank::Joker, Suit{}}; }
		friend std::istream& operator>>(std::istream&, Card&);
		
		bool operator==(const Card&);
		bool operator<(const Card&);
		
	private:
		Rank r;
		Suit s;
	};
	
	// Helper functions.
	std::ostream& operator<<(std::ostream&, const Card&);
}
#endif