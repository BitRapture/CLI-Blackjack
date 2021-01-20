#include <iostream>
#include <ctime>
#include "Hands.h"

int main()
{
	srand(time(NULL));
	bool g_errorHandling = false;

	Card* g_allCards = nullptr;
	Card** g_deck = new Card * [52]{ nullptr };
	Hand g_player, g_dealer;

	g_errorHandling = !InitialiseCardDeck(g_allCards);
	g_errorHandling |= g_deck == nullptr;
	g_errorHandling |= !InitialiseHand(g_player);
	g_errorHandling |= !InitialiseHand(g_dealer);

	if (g_errorHandling)
	{
		std::cout << "There was an error!";
	}
	else
	{
		FillPointerDeck(g_deck, g_allCards);
		ShufflePointerDeck(g_deck);

		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);
		PullCard(g_player, g_deck);

		PrintHand(g_player);
	}

	delete[] g_allCards;
	delete[] g_deck;
	return 0;
}
