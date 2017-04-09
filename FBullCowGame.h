#pragma once
#include <string>

using int32 = int;
using FString = std::string;

//all values initialised to zero
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
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor!

	void Reset(); // TODO - make a richer return value
	int32 GetMaxTries() const;
	FString GetIsogram(int32);
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;


	//counts bulls and cows and increases try number and assumes valid guess
	FBullCowCount SubmitValidGuess(FString);

	

// ^^ please try to ignore this and focus on the interface above
private:
	// see constructor
	int32 MyCurrentTry;	
	bool bGameIsWon;
	FString Isogram;

	bool IsIsoGram(FString) const;
	bool IsLowerCase(FString) const;
};