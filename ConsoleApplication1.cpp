// ConsoleApplication1.cpp : Defines the entry point for the console application.
/* this is the console executable that makes use of the BullCow class
this acts as the view in an nvc pattern and is responsible for all user interaction
for game logic see the FBullCowGame class
*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using int32 = int;
using FText = std::string;

void PrintIntro();
int32 SetDifficulty();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

//global variable
int32 Difficulty_Chosen;

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		SetDifficulty();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	return 0;
}


void PrintIntro()
{
	//Introduce the game

	std::cout << "    ________      .__  .__                             .___ _________\n";
	std::cout << "    \\______ \\__ __|  | |  |   ______ _____   ____    __| _/ \\_   ___ \\  ______  _  ________\n";
	std::cout << "    |   |  _/  |  \\  | |  |  /  ___/ \\__  \\ /    \\  / __ |  /    \\  \\/ /  _ \\ \\/ \\/ /  ___/\n";
	std::cout << "    |   |   \\  |  /  |_|  |__\\___ \\   / __ \\|  |  \\/ /_/ |  \\     \\___(  <_> )     /\\___ \\ \n";
	std::cout << "    |______ /____/|____/____/____  > (____ /___|  /\\____ |   \\______ / \\____/ \\/\\_//____  >  \n";
	std::cout << "          \\/                     \\/      \\/     \\/      \\/         \\/                   \\/  \n";


	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n\n";
	std::cout << "The aim of the game is to guess the correct word in a limited number of tries.\n";
	std::cout << "The only information you have to go on is the word length (an isogram [no repeating letters]).\n";
	std::cout << "Each turn you will be told how many letters that you guessed occur in the word.\n";
	std::cout << "You will also be told if they are in the correct position (a 'Bull') or incorrect position (a 'Cow').\n\n";
	return;
}

int32 SetDifficulty()
{
	do {
		std::cout << "Select your isogram length (4,5,6 or 7): ";
		std::cin >> Difficulty_Chosen;
	} while (Difficulty_Chosen != 4 && Difficulty_Chosen != 5 && Difficulty_Chosen != 6 && Difficulty_Chosen != 7);

	BCGame.GetIsogram(Difficulty_Chosen);
	std::cout << "\nGreat! You have " << BCGame.GetMaxTries() << " Tries. Can you guess the ";
	std::cout << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of?\n\n";
	
	std::cin.clear(); // clear cin buffer 
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear cin buffer 

	return Difficulty_Chosen;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	return;
}

FText GetValidGuess() // Loop continually until the user gives a valid guess
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your Guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a single word isogram using letters only. Do not repeat letters \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use lowercase letters only. \n\n";
			break;
		default:
			EGuessStatus::OK; // assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until no errors
	return Guess;
}



bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon()) { std::cout << "BOOM! YOU ARE AWESOME!\n\n"; }
	else { std::cout << "OH NO! YOU SUCK!\n\n"; }
	return;
}
