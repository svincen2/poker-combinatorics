#include "Deck.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <stdexcept>


#include <iostream>

namespace cardgames
{
	/*
	* Construct a default, empty deck.
	*/
	Deck::Deck() :std::vector<Card>{}, top{nullptr}, bottom{nullptr}
	{
	}
	
	
	/*
	* Construct a deck.
	* Param jok - If true, the deck will contain jokers.
	*/
	Deck::Deck(bool jok) :std::vector<Card>{}
	{
		create_cards(jok);
		top = &operator[](0);
		bottom = &operator[](size());
	}
	
	
	/*
	* Copy construct a deck with the given cards.
	* Param cards - Vector of cards.
	*/
	Deck::Deck(const std::vector<Card>& cards) 
		:std::vector<Card>{cards},
		top{&operator[](0)},
		bottom{&operator[](cards.size())}
	{
	}
	
	
	/*
	* Move construct a deck with the given cards.
	* Param cards - Vector of cards.
	*/
	Deck::Deck(std::vector<Card>&& cards) 
		:std::vector<Card>{cards},
		top{&operator[](0)},
		bottom{&operator[](cards.size())}
	{
	}
	
	
	/*
	* Create a deck without the given cards, with or without jokers.
	* Param cards - Cards to be left out of the deck.
	* Param jokers - If true, jokers will be made.
	* Return - Newly created deck.
	*/
	Deck Deck::create_without(const std::vector<Card>& cards, bool jokers)
	{
		Deck d{};
		for(auto s = Suit::Clubs; s <= Suit::Spades; ++s)
			for(auto r = Rank::Ace; r <= Rank::King; ++r)
			{
				Card c{r, s};
				bool keep{true};
				for(auto card : cards) if(card == c) keep = false;
				if(keep) d.push_back(c);
			}
		d.top = &d[0];
		d.bottom = &d[d.size()];
		
		return d;
	}
	
	
	/*
	* Create a deck without the given cards, with or without jokers.
	* Param cards - Cards to be left out of the deck.
	* Param jokers - If true, jokers will be made.
	* Return - Newly created deck.
	*/
	Deck Deck::create_without(const std::vector<Card*>& cards, bool jokers)
	{
		Deck d{};
		for(auto s = Suit::Clubs; s <= Suit::Spades; ++s)
			for(auto r = Rank::Ace; r <= Rank::King; ++r)
			{
				Card c{r, s};
				bool keep{true};
				for(auto card : cards) if(*card == c) keep = false;
				if(keep) d.push_back(c);
			}
		d.top = &d[0];
		d.bottom = &d[d.size()];
		return d;
	}
	
	
	/*
	* Create the cards for the deck.
	* Param jok - If true, jokers will be created.
	*/
	void Deck::create_cards(bool jok)
	{
		for(auto s = Suit::Clubs; s <= Suit::Spades; ++s)
			for(auto r = Rank::Ace; r <= Rank::King; ++r)
				push_back(Card{r, s});
		if(jok)
		{
			push_back(Card::make_joker());
			push_back(Card::make_joker());
		}
	}
	
	
	/*
	* Deal the next card from the top of the deck.
	* If the deck is empty, returns nullptr.
	* Return - Pointer to card dealt, or nullptr if deck is empty.
	*/
//	Card* Deck::deal()
//	{
//		if(empty()) throw std::runtime_error{"Empty deck"};
//		return &operator[](top++);
//	}
	
	
	/*
	* Deal the next [count] cards from the top of the deck.
	* Param count - Number of cards to deal.
	* Return - The dealt cards.
	*/
	std::vector<Card*> Deck::deal(int count)
	{
		std::vector<Card*> cards(count);
		for(auto i = 0; i != count; ++i)
			cards[i] = deal();
		return cards;
	}
	
	
	/*
	* Rewind the deck to a previously marked state.
	* If no marks are found, rewinds to the beginning of the deck.
	*/
	void Deck::rewind()
	{
		if(!marks.empty())
		{
			top = marks.front();
			marks.pop_front();
		}
		else top = &operator[](0);
	}
	
	
	/*
	* Shuffle the entire deck.
	*/
	void Deck::shuffle()
	{
		using namespace std::chrono;
		auto seed{system_clock::now().time_since_epoch().count()};
		std::shuffle(
			begin(), 
			end(),
			std::default_random_engine{static_cast<unsigned int>(seed)});
		top = &operator[](0);
	}
	
}