#include <iostream>
#include "Cards.h"

int main()
{
	Card* g_deck;
	bool g_errorHandling = false;

	g_errorHandling = !InitialiseCardDeck(g_deck);

	if (g_errorHandling)
	{
		std::cout << "There was an error!";
	}
	else
	{
		PrintCardDeck(g_deck);
	}
}
