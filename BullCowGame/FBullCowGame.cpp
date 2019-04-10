 #include "FBullCowGame.h"
 #include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset(){ 

	constexpr int32 MAX_TRIES = 20;	
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "makeup";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// recieves a VALID guess, incriments turn, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	FString	UserGuess = Guess;
	MyCurrentTry++;
	int32 WordLength = MyHiddenWord.length(); // assuming the same lenght as guess

	FBullCowCount BullCowCount;
	// loop trough all letters in the guess
	
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			if (UserGuess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; // incriment bulls if theyre in same place
				}
				else {
					BullCowCount.Cows++; // incriment cows if not
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon == false;
	}
	return BullCowCount ;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true;	}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //for all letters of the word 
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) {
			return false; // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true;
		}

	}


	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	for (auto Letter : Word) {
		
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const{
	// if the guess isnt an isogram 
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_isogram;
	}
	// if the gues isnt all lowercase
	else if (!IsLowercase(Guess)) {

		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Lenght;
	}
	else {
		return EGuessStatus::OK;
	}
		//return error
	// if the guess length si wrong
		//return error
	// otherwise
		// return OK
}


