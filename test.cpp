#include "Card.h"
#include "Deck.h"
#include "Poker.h"
#include "Hand_Counter.h"
#include "Suit_Group.h"


#include <chrono>
#include <fstream>
#include <iostream>

void run()
{
	using namespace cardgames;
	using namespace std::chrono;
	
	std::vector<Card> cards{};
	std::ifstream ifs{"Cards.txt"};
	cardgames::Card c{};
	for(auto i = 0; i != 5; ++i)
	{
		ifs >> c;
		cards.push_back(c);
	}
	for(auto card : cards) std::cout << "card: " << card << '\n';
	
	std::vector<int> replace{};
	int index{};
	while(ifs >> index) replace.push_back(index);


	poker::Hand h{cards};
	
	auto tp{system_clock::now()};
	std::vector<int> counts{hand_counts(h, replace)};	
	auto dur{system_clock::now() - tp};
	std::cout << "TIME: " << dur.count() << '\n';
	
	int total{0};
	for(auto i = 0; i != poker::Hand::NUM_TYPES; ++i)
	{
		std::cout << static_cast<poker::Hand::Type>(i) << ": " << counts[i] << '\n';
		total += counts[i];
	}
	std::cout << "total: " << total << "\n\n";

	fivedraw::Hand_Counter counter{cards};
	tp = system_clock::now();
	counter.count_hands();
	dur = system_clock::now() - tp;
	std::cout << "TIME: " << dur.count() << '\n';
	
	std::cout << "RF: " << counter.count_of(poker::Hand::Type::Royal_Flush) << '\n';
	std::cout << "SF: " << counter.count_of(poker::Hand::Type::Straight_Flush) << '\n';
	std::cout << "4: " << counter.count_of(poker::Hand::Type::Four_Kind) << '\n';
	std::cout << "FH: " << counter.count_of(poker::Hand::Type::Full_House) << '\n';
	std::cout << "F: " << counter.count_of(poker::Hand::Type::Flush) << '\n';
	std::cout << "S: " << counter.count_of(poker::Hand::Type::Straight) << '\n';
	std::cout << "3: " << counter.count_of(poker::Hand::Type::Three_Kind) << '\n';
	std::cout << "2: " << counter.count_of(poker::Hand::Type::Two_Pair) << '\n';
	std::cout << "1: " << counter.count_of(poker::Hand::Type::Pair) << '\n';
	std::cout << "HC: " << counter.count_of(poker::Hand::Type::High_Card) << '\n';
}



/*
* Main entry point into the program.
* Run the test by calling run() function.
*/
int main()
{
	try
	{
		run();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return 0;
}