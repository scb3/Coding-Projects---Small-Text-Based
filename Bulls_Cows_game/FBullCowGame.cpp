#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }//Default Constructor 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const{ return myHiddenWord.length(); }
bool FBullCowGame::isGameWon()const { return bGame_is_won; }


int32 FBullCowGame::GetMaxTries() const { 

	TMap<int32, int32>WordLengthToMaxTries{ {3,5}, {4,10}, {5,10}, {6,10},{7,15},{8,15},{9,20} };
	return WordLengthToMaxTries[myHiddenWord.length()];
}
	


void FBullCowGame::Reset()
{	
	const FString Hidden_Word = "planets";//This MUST be an Isogram

	myHiddenWord = Hidden_Word;
	MyCurrentTry = 1;
	bGame_is_won = false;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

FBullCowCount FBullCowGame::Submit_Vaild_Guess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 Word_Length = myHiddenWord.length();//Assuming Same length as guess

	//Loop through all the Letters in the Hidden Word
	for (int32 MHWChar = 0; MHWChar < Word_Length; MHWChar++)
	{
		//Compare Letters against the guess
		for (int32 GChar = 0; GChar < Word_Length; GChar++)
		{
			//If they Match then
			if (Guess[GChar] == myHiddenWord[MHWChar])
			{
				if (MHWChar == GChar) //In the Same Place
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == Word_Length)
	{
		bGame_is_won = true;
	}
	else
	{
		bGame_is_won = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 Letter Words as Isograms

	if (Word.length() <= 1) { return true; }

	TMap<char, bool>LetterSeen;

	for (auto letter : Word)
	{
		letter = tolower(letter);//Handle Mixed Case words

		if (LetterSeen[letter])
		{
			return false;
		}
		else 
		{
			LetterSeen[letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{

	for (auto letter : Word)
	{ 
		if (!islower(letter))
		{
			return false;
		}
	}
	return true;
}
