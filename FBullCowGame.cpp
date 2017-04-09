#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); } // <-- constructor definition. see reset for variable settings

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return Isogram.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }


int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> IsogramLengthToMaxTries{ {3,5}, {4,6}, {5,8}, {6,10}, {7,13}, {8,17}, {9,23} };
	return IsogramLengthToMaxTries[Isogram.length()];
}


FString FBullCowGame::GetIsogram(int32 UserInputD)
{
	TMap<int32, FString> WordLengthtoIsogram{ { 3,"ant" },{ 4,"plan" },{ 5,"plane" },{ 6,"planet" },{ 7,"planets" } };
	Isogram = WordLengthtoIsogram[UserInputD];
	return Isogram;
}



void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsoGram(Guess))
	{
		return EGuessStatus::Not_Isogram;	// if the guess length is wrong, return an error
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;	// if the guess isn't all lowercase, return an error TODO function
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;			// otherwise (else) return OK
	}
}


// receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	// set up a return variable
	FBullCowCount BullCowCount;
	int32 WordLength = Isogram.length(); // assuming guess and hidden word are same length. hence 'WordLength' used for both. 

	// loop through all letters in the hidden word

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess 
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == Isogram[MHWChar]) {
				// if they are in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else { bGameIsWon = false;
	}
	return BullCowCount;
	}

bool FBullCowGame::IsIsoGram(FString Word) const
{
	if (Word.length() <= 1) { return true; }	// treat 0 and 1 letter strings as isograms

	TMap<char, bool> LetterSeen;	// set up the map
	for (auto Letter : Word)		// for all letters of the word
	{
		Letter = tolower(Letter);	// to handle mixed case

		if (LetterSeen[Letter]) {	// if the letter is in the map
			return false;			// we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true;  // add the letter to the map as seen
		}
	}
	return true;	// for example in cases where /0 is entered
}


bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() <= 1) { return true; }	// treat 0 and 1 letter strings as isograms


	for (auto Letter : Word)				// for all letters of the word
	{
		if (!islower(Letter))
		{
			return false;
		}
		return true;
	}
}




