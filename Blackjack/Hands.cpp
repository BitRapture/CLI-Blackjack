///  @file Hands.cpp
///  @brief Declarations for hand related functions

#include <iostream>
#include "Hands.h"

// Module Contents
bool InitialiseHand(Hand& _hand)
{
	_hand.m_hand = new Card * [14]{ nullptr };

	return _hand.m_hand != nullptr;
}

void PullCard(Hand& _hand, Card**& _deck)
{
	if (_deck[0] != nullptr)
	{ 
		_hand.m_hand[_hand.m_handSize++] = _deck[0]; 

		for (int i = 0; i < 51; ++i)
		{
			_deck[i] = _deck[i + 1];
		}
		_deck[51] = nullptr;
	}
}

void PrintHand(Hand& _hand)
{
	for (int i = 0; i < _hand.m_handSize; ++i)
	{
		std::cout << "[" << i + 1 << "]: " << _hand.m_hand[i]->m_cardName << " of " 
			<< _hand.m_hand[i]->m_cardSuit << std::endl;
	}
}