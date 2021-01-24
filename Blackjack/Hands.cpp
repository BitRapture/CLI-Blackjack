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

void ResetHand(Hand& _hand)
{
	if (_hand.m_hand != nullptr)
	{
		for (int i = 0; i < 14; ++i)
		{
			_hand.m_hand[i] = nullptr;
		}
	}
	_hand.m_handSize = 0;
	_hand.m_handValue = 0;
}

void FreeHand(Hand& _hand)
{
	delete[] _hand.m_hand;
}

bool PullCard(Hand& _hand, Card**& _deck, Card**& _discard)
{
	if (_hand.m_handSize >= 14) { return false; }
	bool ace = false;
	_hand.m_hand[_hand.m_handSize++] = _deck[0]; 
	_hand.m_handValue += _deck[0]->m_cardValue;
	if (_deck[0]->m_cardValue == 1) { ace = true; }

	for (int i = 0; i < 52; ++i)
	{
		if (_discard[i] == nullptr) { _discard[i] = _deck[0]; break; }
	}

	for (int i = 0; i < 51; ++i)
	{
		_deck[i] = _deck[i + 1];
	}
	_deck[51] = nullptr;
	return ace;
}

void PrintHand(Hand& _hand)
{
	for (int i = 0; i < _hand.m_handSize; ++i)
	{
		std::cout << "[" << i + 1 << "]: " << _hand.m_hand[i]->m_cardName << " of " 
			<< _hand.m_hand[i]->m_cardSuit << std::endl;
	}
}