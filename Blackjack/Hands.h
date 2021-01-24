/// \file Hands.h
/// \brief Contains hand structure and related functions for blackjack
/// \author George Smith

#ifndef _HANDS_H_
#define _HANDS_H_

//File Includes
#include "Cards.h"

//Header Contents

struct Hand
{
	Card** m_hand{ nullptr };
	int m_handSize{ 0 };
	int m_handValue{ 0 };
};

bool InitialiseHand(Hand& _hand);

void ResetHand(Hand& _hand);

void FreeHand(Hand& _hand);

bool PullCard(Hand& _hand, Card**& _deck, Card**& _discard);

void PrintHand(Hand& _hand);

#endif  // _HANDS_H_