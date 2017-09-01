#ifndef CARDGAMES_POKER_PAYTABLE_H
#define CARDGAMES_POKER_PAYTABLE_H

#include "Poker.h"
#include <unordered_map>

namespace cardgames
{
	namespace poker
	{
		template<Hand::Type>
		struct Requirement
		{
			
		};
		
		class Pay_Table
		{
		public:
			virtual Hand::Analysis analyze(const Hand&);
			virtual Hand::Type evaluate(const Hand&);
			int pay(const Hand::Type& t) { return tbl[t]; }
			virtual int pay_out(const Hand&);
			
		private:
			std::unordered_map<Hand::Type, int> tbl{};
			
		};
	}
}
#endif