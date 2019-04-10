#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus {
	Invalid_Status,
	OK,
	Not_isogram,
	Wrong_Lenght,
	Not_Lowercase,
	Too_short,
	Too_long,
	Numbers,
};

class FBullCowGame {
public:	
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO make a more rich return value
	 //TODO make a more rich return value
	
									
	// counts bulls & cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);
	
// Ignore this untill right time
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
