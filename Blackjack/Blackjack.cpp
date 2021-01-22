#include <iostream>
#include <ctime>
#include "Logic.h"

int main()
{
	srand(time(NULL));
	bool errorHandling = false;
	bool gameLoop = true;
	bool gameDebugMode = false;
	int gameState = 0;

	Card* allCards = nullptr;
	Card** deck = new Card * [52]{ nullptr };
	Hand player, dealer;
	int betAmm = 0, balance = 1000;
	bool dealerHoleCard = true;

	errorHandling = !InitialiseCardDeck(allCards);
	errorHandling |= deck == nullptr;
	errorHandling |= !InitialiseHand(player);
	errorHandling |= !InitialiseHand(dealer);

	if (errorHandling)
	{
		std::cout << "There was an error!";
	}
	else
	{
		std::cout << " _______   __                      __          _____                      __       \n"
			<< "|       \\ |  \\                    |  \\        |     \\                    |  \\      \n"
			<< "| $$$$$$$\\| $$  ______    _______ | $$   __    \\$$$$$  ______    _______ | $$   __ \n"
			<< "| $$__/ $$| $$ |      \\  /       \\| $$  /  \\     | $$ |      \\  /       \\| $$  /  \\\n"
			<< "| $$    $$| $$  \\$$$$$$\\|  $$$$$$$| $$_/  $$__   | $$  \\$$$$$$\\|  $$$$$$$| $$_/  $$\n"
			<< "| $$$$$$$\\| $$ /      $$| $$      | $$   $$|  \\  | $$ /      $$| $$      | $$   $$ \n"
			<< "| $$__/ $$| $$|  $$$$$$$| $$_____ | $$$$$$\\| $$__| $$|  $$$$$$$| $$_____ | $$$$$$\\ \n"
			<< "| $$    $$| $$ \\$$    $$ \\$$     \\| $$  \\$$ \\$$    $$ \\$$    $$ \\$$     \\| $$  \\$$\\\n"
			<< " \\$$$$$$$  \\$$  \\$$$$$$$  \\$$$$$$$ \\$$   \\$$ \\$$$$$$   \\$$$$$$$  \\$$$$$$$ \\$$   \\$$\n"
			<< "                                   Pog Edition                                         \n\n\n" << std::endl;

		while (gameLoop)
		{
			switch (gameState)
			{
				case 0: // Main menu
				{
					bool menuLoop = true;
					std::cout << "[1] Play game \n[2] Debug mode \n[3] Read rules \n[4] Exit\n" << std::endl;
					
					while (menuLoop)
					{
						std::cout << "Choose an option (1 to 4): ";
						int query = CinToInt();
						switch (query)
						{
							case 2:
							{
								gameDebugMode = true;
							}
							case 1:
							{
								gameState = 1;
								menuLoop = false;
								break;
							}
							case 3:
							{
								gameState = -1;
								menuLoop = false;
								break;
							}
							case 4:
							{
								gameLoop = false;
								menuLoop = false;
								break;
							}
						}
					}
					break;
				}
				case 1: // Reset game
				{
					FillPointerDeck(deck, allCards);
					ResetHand(player);
					ResetHand(dealer);
					ShufflePointerDeck(deck);
					PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					dealerHoleCard = !gameDebugMode;
					++gameState;
					break;
				}
				case 2:	// Betting
				{
					std::cout << "How much do you want to bet? ($10 to $" << balance << "): $";
					if (BetQuery(betAmm, balance))
					{
						std::cout << "You're betting $" << betAmm;
						ContinueQuery();
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						++gameState;
					}
					else
					{
						std::cout << "Please specify an ammount between $10 to $" << balance << std::endl;
					}
					break;
				}
				case 3: // Pull initial cards
				{
					for (int i = 0; i < 2; ++i)
					{
						DealerCardPull(dealer, dealerHoleCard, deck);
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						PlayerCardPull(player, deck);
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					}
					++gameState;
					break;
				}

				default:
				{
					gameLoop = false;
				}
			}
		}
		FreeHand(player);
		FreeHand(dealer);
	}

	delete[] allCards;
	delete[] deck;
	return 0;
}