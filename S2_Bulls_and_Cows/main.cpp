/*
	This is the console executable that makes use of the BullCow class.
	This acts as the View in the MVC pattern, and is responsible for all
	user interaction. For game logic, see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// make syntax more like Unreal
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame;	// instantiate a new game

int main()
{
	bool b_playAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		b_playAgain = AskToPlayAgain();
	} while (b_playAgain);
	return 0;
}

/*
	Introduce the game.
*/
void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "          }   {        \\___/ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Welcome to Bulls and Cows, a really fun word game\n"
		<< "(but that's just my opinion)\n";
	std::cout << "Can you guess the mystery word I'm thinking of?\n";
	std::cout << std::endl;
}

/*
	Plays a single game to completion.
*/
void PlayGame()
{
	BCGame.Reset();
	int32 maxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= maxTries) {
		FText guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount bullCowCount = BCGame.SubmitValidGuess(guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << " Cows = " << bullCowCount.cows << "\n\n";
	}

	PrintGameSummary();
}

/*
	Loop continually until the user gives a valid guess
*/
FText GetValidGuess()
{
	FText guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 currentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without any repeating letters.\n\n";
			break;
		default:
			// assuming the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors

	return guess;
}

/*
	Prints the final results of the game.
*/
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Well done! You win!!";
	}
	else {
		std::cout << "The word you were looking for is: " << BCGame.GetHiddenWord() << std::endl;
		std::cout << "Sorry...better luck next time!";
	}
	std::cout << std::endl;
}

/*
	Ask the player if they want to play again.
*/
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'Y') || (response[0] == 'y');
}
