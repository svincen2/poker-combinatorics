#ifndef CARDGAMES_DECK_H
#define CARDGAMES_DECK_H

#include "Card.h"
#include <forward_list>
#include <vector>

#include <iostream>

namespace cardgames
{
	class Deck : public std::vector<Card>
	{
	public:
		Deck(bool);
		Deck(const std::vector<Card>&);
		Deck(std::vector<Card>&&);
		static Deck create_without(const std::vector<Card>&, bool);
		static Deck create_without(const std::vector<Card*>&, bool);
		Card* deal() { return top++; }
		std::vector<Card*> deal(int);
//		size_t dealt() const { return top; }
		bool empty() { return top == bottom; }
		void mark() { marks.push_front(top); }
//		size_t remaining() const { return size() - top; }
		void rewind();
		void shuffle();
		
	private:
		Deck();
		void create_cards(bool);
		
		Card* top;
		Card* bottom;
		std::forward_list<Card*> marks;
	};
}
#endif