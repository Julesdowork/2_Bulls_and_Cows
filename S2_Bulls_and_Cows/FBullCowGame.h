/*
	The game logic (no view code or direct user interaction).
	The game is a simple guess the word game based on Mastermind.
*/
#pragma once

#include <string>

// make syntax more like Unreal
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum EDifficulty {
	Not_Set,
	Easy,
	Medium,
	Hard
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	FString GetHiddenWord() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 m_currentTry;
	int32 m_maxTries;
	FString m_hiddenWord;
	bool b_gameWon;
	EDifficulty m_difficulty;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	void ChooseDifficulty();
	void InitializeHiddenWord();
	void PrintInstructions() const;
};