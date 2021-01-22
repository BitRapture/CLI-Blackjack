/// \file Logic.h
/// \brief Contains blackjack game logic functions
/// \author George Smith

#ifndef _LOGIC_H_
#define _CA_LOGIC_H_RDS_H_

//File Includes
#include "Hands.h"

//Header Contents
bool YesOrNoQuery();

void ContinueQuery();

int StrToID(char _string[]);

void PrintScreen(Hand& _player, Hand& _dealer, bool& _holeCard, int& _betAmm, int& _balance);

int CinToInt();

bool BetQuery(int& _betAmm, int& _balance);

void PlayerCardPull(Hand& _player, Card**& _deck);

void DealerCardPull(Hand& _dealer, bool& _holeCard, Card**& _deck);

unsigned char ValidateHands(Hand& _player, Hand& _player);

#endif  // _CARDS_H_