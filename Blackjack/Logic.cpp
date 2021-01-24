///  @file Logic.cpp
///  @brief Declarations for blackjack game logic related functions

#include <iostream>
#include <iomanip>
#include "Logic.h"

// Module Contents
bool YesOrNoQuery()
{
	bool queryLoop = true;
	bool ans = false;

	while (queryLoop)
	{
		char query[1000]{ 0 };
		std::cin.getline(query, 1000, '\n');
		_strupr_s(query);
		int queryLength = strnlen_s(query, 1000);
		int id = (queryLength <= 3 ? StrToID(query) : 0);
		switch (id)
		{
			case -89:	// y
			case -241:	// yes
			{
				ans = true;
				queryLoop = false;
				break;
			}
			case -78:	// n
			case -157:	// no
			{
				queryLoop = false;
				break;
			}
			default:
			{
				std::cout << "Please enter either [y] or [n]: ";
				if (queryLength >= 1000) { std::cin.clear(); }
			}
		}
	}
	return ans;
}

void ContinueQuery()
{
	std::cout << "\nPress enter to continue";
	std::cin.ignore();
}

int StrToID(char _string[])
{
	int strSize = strnlen_s(_string, 65535);
	int id = 0;
	for (int i = 0; i < strSize; ++i)
	{
		id -= _string[i];
	}
	return id;
}

void PrintScreen(Hand& _player, Hand& _dealer, bool& _holeCard, int& _betAmm, int& _balance)
{
	system("cls");
	std::cout << std::setfill('$') << std::setw(30) << "\n"
		<< "      CLI::Blackjack \n"
		<< std::setfill('$') << std::setw(31) << "\n\n"
		<< "Balance: $" << _balance << "\n"
		<< "Betting: $" << _betAmm << "\n\n"
		<< "Dealer's hand: ";
	if (_dealer.m_handSize > 0)
	{
		for (int i = 0; i < _dealer.m_handSize; ++i)
		{
			if (i == 0 && _holeCard)
			{
				std::cout << "Hole Card"
					<< (i + 1 >= _dealer.m_handSize ? "\n" : ", ");
			}
			else
			{
				std::cout << _dealer.m_hand[i]->m_cardName << " of " << _dealer.m_hand[i]->m_cardSuit
					<< (i + 1 >= _dealer.m_handSize ? "\n" : ", ");
			}
		}
		std::cout << "Dealer's hand value: " << (_holeCard ? _dealer.m_handValue - _dealer.m_hand[0]->m_cardValue : _dealer.m_handValue) << "\n" << std::endl;
	}
	else
	{
		std::cout << "Empty hand \nDealer's hand value: 0 \n" << std::endl;
	}

	std::cout << "Your hand: ";
	if (_player.m_handSize > 0)
	{
		for (int i = 0; i < _player.m_handSize; ++i)
		{
			std::cout << _player.m_hand[i]->m_cardName << " of " << _player.m_hand[i]->m_cardSuit
				<< (i + 1 >= _player.m_handSize ? "\n" : ", ");
		}
	}
	else
	{
		std::cout << "Empty hand" << std::endl;
	}
	std::cout << "Your hand value: " << _player.m_handValue 
		<< "\n\n------------------------------\n" << std::endl;
}

int CinToInt()
{
	char query[1000]{ 0 };
	std::cin.getline(query, 1000);
	if (strnlen_s(query, 1000) >= 1000)
	{
		std::cin.clear();
	}

	return atoi(query);
}

bool BetQuery(int& _betAmm, int& _balance)
{
	int amm = CinToInt();

	if (amm >= 1 && amm <= _balance)
	{
		_betAmm = amm;
		_balance -= amm;
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerCardPull(Hand& _player, Card**& _deck, Card**& _discard, Card*& _allCards)
{
	if (_deck[0] == nullptr)
	{
		MovePointerDeck(_deck, _discard);
		ShufflePointerDeck(_deck);
	}
	bool ace = PullCard(_player, _deck, _discard);
	std::cout << "You pulled " << (ace || _player.m_hand[_player.m_handSize - 1]->m_cardValue == 8 ? "an " : "a ")
		<< _player.m_hand[_player.m_handSize - 1]->m_cardName
		<< " of " << _player.m_hand[_player.m_handSize - 1]->m_cardSuit << "! ";

	if (ace)
	{
		std::cout << "Do you want to change its value to 11? (y/n): ";

		if (YesOrNoQuery())
		{
			_player.m_handValue += 10;
			std::cout << "\nChanged value to 11, your hand value is now " << _player.m_handValue;

		}
	}

	std::cout << std::endl;
	ContinueQuery();
	std::cout << std::endl;
}

void DealerCardPull(Hand& _dealer, bool& _holeCard, Card**& _deck, Card**& _discard, Card*& _allCards)
{
	if (_deck[0] == nullptr)
	{
		MovePointerDeck(_deck, _discard);
		ShufflePointerDeck(_deck);
	}
	bool ace = PullCard(_dealer, _deck, _discard);
	
	if (ace)
	{
		if (_dealer.m_handValue + 10 <= 21)
		{
			_dealer.m_handValue += 10;
		}
	}

	if (_holeCard && _dealer.m_handSize == 1)
	{
		std::cout << "Dealer pulled a Hole Card!";
	}
	else
	{
		std::cout << "Dealer pulled " << (ace || _dealer.m_hand[_dealer.m_handSize - 1]->m_cardValue == 8 ? "an " : "a ")
			<< _dealer.m_hand[_dealer.m_handSize - 1]->m_cardName
			<< " of " << _dealer.m_hand[_dealer.m_handSize - 1]->m_cardSuit << "! ";
	}

	std::cout << std::endl;
	ContinueQuery();
	std::cout << std::endl;
}

int ValidateHands(Hand& _player, Hand& _dealer, bool& _initialDraw)
{
	int winState = 0;

	if (_player.m_handValue == _dealer.m_handValue)
	{
		winState = (_initialDraw && _player.m_handValue == 21 ? -1 : (_initialDraw ? 0 : -1));
	}
	else if (_player.m_handValue == 21 || _player.m_handValue < 21 && _dealer.m_handValue > 21
		|| _player.m_handValue < 21 && _dealer.m_handValue < _player.m_handValue && !_initialDraw)
	{
		winState = 1;
	}
	else if (_dealer.m_handValue == 21 || _player.m_handValue > 21
		|| _dealer.m_handValue < 21 && _player.m_handValue < _dealer.m_handValue && !_initialDraw)
	{
		winState = 2;
	}

	return winState; // -1 = Draw (push), 0 = No winner, 1 = Player won, 2 = Dealer won
}

bool HitOrStandQuery()
{
	bool queryLoop = true;
	bool ans = false;

	while (queryLoop)
	{
		char query[1000]{ 0 };
		std::cin.getline(query, 1000, '\n');
		_strupr_s(query);
		int queryLength = strnlen_s(query, 1000);
		int id = (queryLength <= 5 ? StrToID(query) : 0);
		switch (id)
			{
			case -229:	// hit
			{
				ans = true;
				queryLoop = false;
				break;
			}
			case -378:	// stand
			{
				queryLoop = false;
				break;
			}
			default:
			{
				std::cout << "Please enter either [hit] or [stand]: ";
				if (queryLength >= 1000) { std::cin.clear(); }
			}
		}
	}
	return ans;
}

void PrintRules()
{
	std::cout << "\nHow to play Blackjack:\n"
		<< "The aim of the game is to get a hand value higher than the dealer's hand value. Your hand value \n"
		<< "can go up to 21, anything past that is a bust and you will lose. Every card has a defined value.\n"
		<< "Ace cards can be either 1 or 11, cards 2 through 10 are their face value, all court cards have \n"
		<< "a value of 10. All cards in your hand give you a total hand value.\n"
		<< "At the start of the game, you and the dealer will be given two cards. It is possible to get a \n"
		<< "natural 21 which is also known as a blackjack! You will win immediately unless the dealer ties. \n"
		<< "If you get a blackjack and the dealer is bust, you get a bet bonus.\n"
		<< "After this initial drawing stage, you will then either [hit] or [stand]; hitting lets you add \n"
		<< "more cards to your hand so you can increase your hand total, however if you draw too many you \n"
		<< "can go bust and lose your bet. Once you're happy with your hand total you can [stand] which \n"
		<< "lets the dealer take their turn, they will draw up to a soft 17 hand total." << std::endl;
}