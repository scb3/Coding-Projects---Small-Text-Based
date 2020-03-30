/*
This is the Console Exe that makes use of the BullCow Class, this acts as the view in a MVC Pattern and is responsable for all user interaction. 

For game logic sthye the FBullCowGame Class
*/

#pragma once

#include <string>
#include <iostream>
#include "FBullCowGame.h"

//To make Syntax Unreal Engine Friendly
using FText = std::string;
using int32 = int;

//Function Prototypes as outside a class
void print_Intro();
void play_game();
FText Get_Valid_Guess();
bool Ask_to_play_again();
void PrintGameSummery();

FBullCowGame BCGame; //Instatnsiate a new game, which we reuse across plays

//Entry point for the Application
int main()
{

	bool bPlay_again = false;
	do {
		print_Intro();
		play_game();
		bPlay_again = Ask_to_play_again();
	} 
	while (bPlay_again);
}

void print_Intro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()<< " ";
	std::cout << "letter isogram I'm thinking of?" << std::endl << std::endl;

}

//Plays a asingle game to completion
void play_game()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for Number of Guesses
	
	while (!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries){

		FText Guess = Get_Valid_Guess();
		FBullCowCount BullCowCount = BCGame.Submit_Vaild_Guess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows: " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummery();	
	
	return;
}

FText Get_Valid_Guess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";

	do {
		
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try: " << CurrentTry << " of " << BCGame.GetMaxTries() << "\n";
	//Get a Guess from the player
	std::cout << "Enter your Guess:";

	std::getline(std::cin, Guess);
	 Status = BCGame.CheckGuessValidity(Guess);

	switch (Status)
	{
	case EGuessStatus::Wrong_length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " Letter word. \n\n";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Please Enter a word without repeating letters \n\n";
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Please only enter lowercase letters\n\n";
		break;
		
	default: 
		//Assume Guess is valid
		break;
	} 
	
	} while (Status != EGuessStatus::OK);	
	return Guess;
}

bool Ask_to_play_again()
{
	std::cout << "Do you want to play again with the same hidden word?";
	FText response = "";
		std::getline(std::cin,response); 

		return (response[0]== 'y') || (response[0] == 'Y');
}

void PrintGameSummery() 
{
	if (BCGame.isGameWon())
	{
		std::cout << "Congratualations you got the correct word! \n";
	}
	else
	{
		std::cout << "Better luck next time \n";
	}
}
