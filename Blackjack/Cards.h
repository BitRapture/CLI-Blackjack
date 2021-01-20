/// \file Cards.h
/// \brief Contains a card structure and related functions
/// \author George Smith

#ifndef _CARDS_H_
#define _CARDS_H_

//Header Contents
struct Card
{
	int m_cardValue{ 0 };
	char m_cardSuit[10]{ 0 };
	char m_cardName[10]{ 0 };
};

bool InitialiseCardDeck(Card*& _deck);

void PrintCardDeck(Card*& _deck);

#endif  // _CARDS_H_