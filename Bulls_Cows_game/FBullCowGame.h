/*
The game logic (no view code or direct user interaction)

The game is a simple word guessing game based on mastermind

*/
#pragma once

#include <string>

//To make Syntax Unreal Engine Friendly

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid,
	OK,
	Not_Isogram, 
	Wrong_length, 
	Not_Lowercase
};

class FBullCowGame 
{

public:
	
	FBullCowGame(); //Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength()const;
	
	bool isGameWon()const;
	EGuessStatus CheckGuessValidity(FString)const;

	void Reset();

	FBullCowCount Submit_Vaild_Guess(FString);
	//See constructor for values
	private:
		int32 MyCurrentTry;
		FString myHiddenWord;
		bool bGame_is_won;

		bool IsIsogram(FString) const;

		bool IsLowerCase(FString) const;
};