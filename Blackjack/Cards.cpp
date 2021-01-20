///  @file Cards.cpp
///  @brief Declerations for card related functions

#include <iostream>
#include "Cards.h"

// Module Contents
bool InitialiseCardDeck(Card*& _deck)
{
	_deck = new Card[52];
	if (_deck == nullptr) { return false; }

	for (int s = 0; s < 52; s += 13)
	{
		for (int i = 0; i < 13; ++i)
		{
			char faceValue[3]{ 0 };
			_itoa_s(i + 1, faceValue, 10);
			_deck[s + i].m_cardValue = i + 1;
			switch (i)
			{
				case 0: { strcpy_s(_deck[s + i].m_cardName, "Ace"); break; }
				case 10: { strcpy_s(_deck[s + i].m_cardName, "Jack"); break; }
				case 11: { strcpy_s(_deck[s + i].m_cardName, "Queen"); break; }
				case 12: { strcpy_s(_deck[s + i].m_cardName, "King"); break; }
				default: { strcpy_s(_deck[s + i].m_cardName, faceValue); break; }
			}
			switch (s)
			{
				case 0: { strcpy_s(_deck[s + i].m_cardSuit, "Clubs"); break; }
				case 13: { strcpy_s(_deck[s + i].m_cardSuit, "Diamonds"); break; }
				case 26: { strcpy_s(_deck[s + i].m_cardSuit, "Hearts"); break; }
				case 39: { strcpy_s(_deck[s + i].m_cardSuit, "Spades"); break; }
				default: { return false; }
			}
		}
	}

	return true;
}

void PrintCardDeck(Card*& _deck)
{
	for (int i = 0; i < 52; ++i)
	{
		std::cout << "[" << i + 1 << "]: " << _deck[i].m_cardName << " of " 
			<< _deck[i].m_cardSuit << std::endl;
	}
}