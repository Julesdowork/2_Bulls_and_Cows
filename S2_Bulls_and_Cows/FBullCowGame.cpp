#include "FBullCowGame.h"
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>

// make syntax more like Unreal
#define TMap std::map
using int32 = int;

// Default Constructor
FBullCowGame::FBullCowGame()
{}

int32 FBullCowGame::GetCurrentTry() const { return m_currentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return m_hiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return b_gameWon; }

FString FBullCowGame::GetHiddenWord() const
{
	return m_hiddenWord;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> wordLengthToMaxTries{ 
		{4,6}, {5,7},
		{6,10}, {7,13},
		{8,16}, {9,20}
	};
	return wordLengthToMaxTries[m_hiddenWord.length()];
}

void FBullCowGame::Reset()
{
	m_difficulty = EDifficulty::Not_Set;
	b_gameWon = false;
	m_currentTry = 1;

	ChooseDifficulty();
	InitializeHiddenWord();
	PrintInstructions();
}

void FBullCowGame::ChooseDifficulty()
{
	std::cout << "Difficulty levels:\n"
		<< "\t1: Easy (4-5 letter words)\n"
		<< "\t2: Medium (6-7 letter words)\n"
		<< "\t3: Hard (8-9 letter words)\n";
	std::cout << "Choose your difficulty level (1-3): ";

	int difficulty;

	while (!(std::cin >> difficulty) || difficulty < 1 || difficulty > 3) {
		std::cin.clear();
		while (std::cin.get() != '\n')
			continue;
		std::cout << "Please enter a number between 1-3: ";
	}
	std::cin.get();		// get newline character out of inputstream

	switch (difficulty) {
	case 1:
		m_difficulty = EDifficulty::Easy;
		break;
	case 2:
		m_difficulty = EDifficulty::Medium;
		break;
	case 3:
		m_difficulty = EDifficulty::Hard;
		break;
	default:
		std::cout << "There was a problem setting your difficulty mode.\n";
	}
}

void FBullCowGame::InitializeHiddenWord()
{
	std::ifstream inFile;
	constexpr int32 LENGTH = 54;
	FString filename;

	switch (m_difficulty) {
	case Easy:
		filename = "easy_words.txt";
		break;
	case Medium:
		filename = "medium_words.txt";
		break;
	case Hard:
		filename = "hard_words.txt";
		break;
	default:
		std::cout << "Unable to find appropriate file name.\n";
	}

	inFile.open(filename);
	if (!inFile.is_open()) {
		std::cout << "Couldn't open file. Exiting program.\n";
		exit(EXIT_FAILURE);
	}

	srand(static_cast<unsigned int>(time(0)));	// seed random number generator
	int randomNumber = rand() % LENGTH;
	int count = 0;
	while (count <= randomNumber) {
		inFile >> m_hiddenWord;					// get the randomNumber - 1 word in file
		count++;
	}

	inFile.close();		// finished with file
}

void FBullCowGame::PrintInstructions() const
{
	std::cout << "\nOkay, enter the " << GetHiddenWordLength() << "-letter "
		<< "word I'm thinking of.\n";
}

bool FBullCowGame::IsIsogram(FString word) const
{
	// treat 0- and 1-letter words as isograms
	if (word.length() <= 1) { return true; }

	TMap<char, bool> letterSeen;
	for (auto letter : word)
	{
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		}
		else {
			letterSeen[letter] = true;
		}
	}

	return true;	// for example, in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString word) const
{
	if (word.length() == 0) { return true; }

	for (auto letter : word) {
		if (letter == '\0' || letter == ' ')
			return false;
		else if (!islower(letter))
			return false;
	}

	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess))	// if the guess isn't all lowercased
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength())	// if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// counts bulls & cows and increases try number, assuming valid guess
// Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	m_currentTry++;
	FBullCowCount bullCowCount;
	int32 wordLength = m_hiddenWord.length();	// assuming the same length as guess

	// loop through all letters in the hidden word
	for (int32 i = 0; i < wordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < wordLength; j++)
		{
			// if they match, then
			if (guess[j] == m_hiddenWord[i])
			{
				// if they're in the same place
				if (j == i)
					bullCowCount.bulls++;
				else
					bullCowCount.cows++;
			}
		}
	}
	if (bullCowCount.bulls == wordLength)
		b_gameWon = true;
	return bullCowCount;
}