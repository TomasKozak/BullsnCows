/*
	This is the console executable, that makes use of the BullCow class
*/

#include <iostream>
#include <string> 
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //this is instantiation -> creation of instance of class


// the entry point for our application
int main()
{
	
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		
	} 
	while (AskToPlayAgain() == 1);
	
	system("pause");
	return 0; // exit the application
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {	// TODO change from FOR to WHILE loop once we have validating tries
		FText Guess = GetValidGuess(); // TODO check for valid guesses		

		// submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
	
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarise a game
	return;
}

//introduce the game
void PrintIntro()
{	// TODO write more appropriate intro
	
	
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) {
		std::cout << "CONGRATULATIONS, you won!!!\n";
	}
	if (!BCGame.IsGameWon()) {
		std::cout << "Bad luck, try it next time!\n";
	}

}

// loop continually untill user gets a valid guess
FText GetValidGuess()
{	

	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". ";
		std::cout << "Enter your guess: ";
		Guess = "";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lower case letters.\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while ( Status != EGuessStatus::OK); // keep looping until we get no errors

	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with same hidden word ?(y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return 	(Response[0] == 'y'  ||  Response[0] == 'Y');
}

