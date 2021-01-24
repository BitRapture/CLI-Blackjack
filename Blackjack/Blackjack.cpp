#include <iostream>
#include <ctime>
#include "Logic.h"

int main()
{
	srand(time(NULL));
	bool errorHandling = false;
	bool gameLoop = true;
	bool gameDebugMode = false;
	bool gameInitalDraw = true;
	int gameState = 0;

	Card* allCards = nullptr;
	Card** deck = new Card * [52]{ nullptr },
		** discard = new Card * [52]{ nullptr };
	Hand player, dealer;
	int betAmm = 0, balance = 1000;
	bool dealerHoleCard = true;

	errorHandling = !InitialiseCardDeck(allCards);
	errorHandling |= deck == nullptr;
	errorHandling |= discard == nullptr;
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
			<< "                                   CLI Edition                                         \n\n\n" << std::endl;

		while (gameLoop)
		{
			switch (gameState)
			{
				case 0: // Main menu
				{
					if (discard[0] != nullptr) { for (int i = 0; i < 52; ++i) { discard[i] = nullptr; } }
					FillPointerDeck(deck, allCards);
					ShufflePointerDeck(deck);
					gameDebugMode = true;

					bool menuLoop = true;
					std::cout << "[1] Play game \n[2] Debug mode \n[3] Read rules \n[4] Exit\n" << std::endl;
					
					while (menuLoop)
					{
						std::cout << "Choose an option (1 to 4): ";
						int query = CinToInt();
						switch (query)
						{
							case 1:
							{
								gameDebugMode = false;
							}
							case 2:
							{
								gameState = 1;
								menuLoop = false;
								break;
							}
							case 3:
							{
								PrintRules();
								ContinueQuery();
								std::cout << std::endl;
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
					if (deck[0] == nullptr)
					{
						MovePointerDeck(deck, discard);
						ShufflePointerDeck(deck);
					}
					ResetHand(player);
					ResetHand(dealer);
					PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					dealerHoleCard = !gameDebugMode;
					gameInitalDraw = true;
					++gameState;
					break;
				}

				case 2:	// Betting
				{
					std::cout << "How much do you want to bet? ($1 to $" << balance << "): $";
					if (BetQuery(betAmm, balance))
					{
						std::cout << "\nYou're betting $" << betAmm << std::endl;
						ContinueQuery();
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						++gameState;
					}
					else
					{
						std::cout << "Please specify an ammount between $1 to $" << balance << std::endl;
					}
					break;
				}

				case 3: // Pull initial cards
				{
					for (int i = 0; i < 2; ++i)
					{
						DealerCardPull(dealer, dealerHoleCard, deck, discard, allCards);
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						PlayerCardPull(player, deck, discard, allCards);
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					}
					++gameState;
					break;
				}

				case 4: // Winning validation
				{
					bool finished = true;
					switch (ValidateHands(player, dealer, gameInitalDraw))
					{
						case -1: // Tie
						{
							balance += betAmm;
							betAmm = 0;
							dealerHoleCard = false;
							PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
							std::cout << "Tied with the dealer, push! Your bet has been returned" << std::endl;
							ContinueQuery();
							std::cout << std::endl;
							break;
						}
						case 1: // Player wins
						{
							balance += betAmm * 2;
							dealerHoleCard = false;
							if (player.m_handValue == 21 && dealer.m_handValue > 21)
							{ 
								balance += betAmm / 2;
								betAmm = 0;
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								std::cout << "Blackjack hand, you win! The dealer is bust, you get a bet bonus!"; 

							} 
							else if (player.m_handValue == 21)
							{
								betAmm = 0;
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								std::cout << (gameInitalDraw ? "Blackjack, you win!" : "You win!"); 
							}
							else
							{
								betAmm = 0;
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								std::cout << (dealer.m_handValue > 21 ? "Dealer busted, you win!" : "You win!");
							}
							std::cout << std::endl;
							ContinueQuery();
							std::cout << std::endl;
							break;
						}
						case 2: // Dealer wins/Player loses
						{
							betAmm = 0;
							dealerHoleCard = false;
							if (gameInitalDraw && dealer.m_handValue == 21)
							{
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								std::cout << "Blackjack, you lost!";
							}
							else
							{
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								std::cout << (player.m_handValue > 21 ? "You busted, you lost!" : "You lost!");
							}
							std::cout << std::endl;
							ContinueQuery();
							std::cout << std::endl;
							break;
						}
						default:
						{
							gameInitalDraw = false;
							finished = false;
							++gameState;
						}
					}
					if (finished)
					{
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						if (balance > 0)
						{
							std::cout << "Would you like to play again? (y/n): ";
							if (YesOrNoQuery()) { gameState = 1; }
							else
							{
								std::cout << "\nYou finished, your winning total is $" << balance << "!" << std::endl;
								ContinueQuery();
								PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
								balance = 1000;
								gameState = 0;
							}
						}
						else
						{
							std::cout << "Game over! You ran out of money!" << std::endl;
							ContinueQuery();
							PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
							balance = 1000;
							gameState = 0;
						}
					}
					break;
				}

				case 5: // Hitting and standing
				{
					bool playerStanding = false;
					while (!playerStanding && player.m_handValue < 21) 
					{ 
						std::cout << "Do you want to [hit] or [stand]: ";
						if (HitOrStandQuery()) 
						{ 
							std::cout << std::endl;
							PlayerCardPull(player, deck, discard, allCards);
							PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
						}
						else 
						{ 
							playerStanding = true;
							std::cout << "\nYou're standing" << std::endl;;
							ContinueQuery();
						}
					}
					dealerHoleCard = false;
					PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					while (dealer.m_handValue < 17 && player.m_handValue <= 21)
					{ 
						DealerCardPull(dealer, dealerHoleCard, deck, discard, allCards);
						PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					}
					if (dealer.m_handValue < 21)
					{
						std::cout << "Dealer is standing" << std::endl;;
						ContinueQuery();
						std::cout << std::endl;
					}
					PrintScreen(player, dealer, dealerHoleCard, betAmm, balance);
					gameState = 4;
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
	delete[] discard;
	return 0;
}