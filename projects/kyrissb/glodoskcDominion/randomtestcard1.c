/* 
Author: Brandon P. Kyriss
Title: randomtestcard1.c
This is a random tester for the Dominion
smithy card for CS 362_400.
*/

#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>


#define ITERATIONS 100000


int randomInt(int min, int max)
{
   return min + rand() % (max+1 - min);
}



int main(int argc, char** argv)
{
	int isTesting = 0;  // Set to 1 for testing output
	srand(time(NULL));  // Seed randsom number generator from clock
	int i,j,l,m;
	int initFailedCount = 0;
	int cardFailedCount = 0;
	int failCount = 0;
	int testCount = 0;

	printf("\n****************************************\nBeginning Smithy Random Test\n****************************************\n");

	for(i = 0; i < ITERATIONS; i++)
	{
		testCount++;
		int errorCount = 0;
		struct gameState TestState;
		int numPlayers = randomInt(2, 4);
		int currentPlayer = 0;
		int seed = 1000;

		int k[10] = 
		{ 
			adventurer, 
			gardens, 
			embargo, 
			village, 
			minion, 
			mine, 
			cutpurse, 
			sea_hag, 
			tribute, 
			smithy 
		};

		int cardsToDraw[13] =
		{
			adventurer, 
			gardens, 
			embargo, 
			village, 
			minion, 
			mine, 
			cutpurse, 
			sea_hag, 
			tribute, 
			smithy,
			copper,
			silver,
			gold 
		};

		int preHandCount = 0;
		int preDeckCount = 0;
		int preDiscardCount = 0;
		int preHandPlayedCount = 0;

		int postHandCount = 0;
		int postDeckCount = 0;
		int postDiscardCount = 0;
		int postHandPlayedCount = 0;

		

		// Initialize game 
		int a = initializeGame(numPlayers, k, seed, &TestState);
		if(a != 0)
		{
			initFailedCount++;
		}
		
		// Randomly select player and set deck and discard counts
		currentPlayer = randomInt(2,numPlayers)-1;
		// Player can have a had of 1 to max cards
	    preHandCount = TestState.handCount[currentPlayer] = randomInt(1,MAX_HAND);
	    // The discard wil be the deck count minus the hand
		preDiscardCount = TestState.discardCount[currentPlayer] = randomInt(0,MAX_DECK - preHandCount); 
		// The deck can be any number between the amount of cards in hand + discard and the full deck (this isn't realyy possible, but hey!)
		preDeckCount = TestState.deckCount[currentPlayer] = randomInt(0,MAX_DECK - (preHandCount + preDiscardCount)); 

		// Set the deck
		// Give the 
		TestState.hand[currentPlayer][0] = smithy;
		for(j = 1; j < preHandCount-1; j++)
		{
			TestState.hand[currentPlayer][j] = cardsToDraw[randomInt(0,12)];
		}

		for(l = 0; l < preDiscardCount-1; l++)
		{
			TestState.discard[currentPlayer][l] = cardsToDraw[randomInt(0,12)];
		}

		for(m = 0; m < preDeckCount-1; m++)
		{
			TestState.deck[currentPlayer][m] = cardsToDraw[randomInt(0,12)];
		}

		// Check played card count
		preHandPlayedCount = TestState.playedCardCount;


		// Set whose turn
		TestState.whoseTurn = currentPlayer;

		int b = cardEffect(smithy,0,0,0,&TestState,0,0);
		if(b != 0)
		{
			cardFailedCount++;
		}

		postDiscardCount = TestState.discardCount[currentPlayer];
		postDeckCount = TestState.deckCount[currentPlayer];
		postHandCount = TestState.handCount[currentPlayer];

		// Check played card
		postHandPlayedCount = TestState.playedCardCount;
	

		// Add 1 back to current player for output					           
		currentPlayer++;

		// Figure out how many cards would be in the deck if the discard was shuffled in
		int shuffled = preDeckCount + preDiscardCount;

		// If there are 3 or more cards in the deck, draw them.	           
		if(preDeckCount >= 3)
		{

			if(postDeckCount != preDeckCount - 3)
			{	printf("\nError: There were 3 or more cards in the deck, but exactly 3 cards were not removed from the deck!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
		}
		// If there are less than 3 cards in the deck, a shuffle will occur and we have 2 cases
		else 
		{
			// If there were more than 3 cards left, 3 should be drawn
			if(shuffled >= 3 && postDeckCount != shuffled - 3)
			{	printf("\nError: Shuffled deck had > 3 cards, but 3 were not removed!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}

			// If there were less than 3 cards left, they should be drawn
			else if(shuffled < 3 && postDeckCount != 0)
			{	printf("\nError: Shuffled deck had > 3 cards, but 3 were not removed!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
		}

		// If there were at least 3 cards to draw, final had should contain 3 more cards minus smithy	           
		if(preDeckCount >= 3)
		{

			if(postHandCount != preHandCount + 3 - 1)
			{	printf("\nError: There were 3 or more cards in the deck, but exactly 3 cards -1 (discard) were not added to hand!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
		}
		// If there not enough cards in the deck, draw!
		else if(preDeckCount < 3)
		{
			if(shuffled >= 3 && postHandCount != preHandCount + 3 - 1)
			{	printf("\nError: Shuffled deck had > 3 cards, but the final hand did not gain exactly 3 cards and lose 1!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
			else if(shuffled == 2 && postHandCount != preHandCount + 2 - 1)
			{	printf("\nError: Shuffled deck had 2 cards, but the final hand did not gain exactly 2 cards and lose 1!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
			else if(shuffled == 1 && postHandCount != preHandCount + 1 - 1)
			{	printf("\nError: Shuffled deck had 1 card, but the final hand did not gain exactly 1 card and lose 1!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
			else if(shuffled == 0 && postHandCount != preHandCount - 1)
			{	
				printf("\nError: Deck had no cards, but the final hand was not correct!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
				errorCount++;
			}
		}
		
		if(preHandPlayedCount != 0)
		{
			printf("\nError: Played cards was not empty at start of turn!\n");
			printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
			printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
			errorCount++;
		}

		if(postHandPlayedCount != 1 )
		{
			printf("\nError: Smithy was not added to the played pile (discarded)!\n");
			printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t InitFailed Count: %d\n", 
			currentPlayer, preDeckCount, preHandCount, preDiscardCount, initFailedCount);
			printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t  Card Failed Count: %d\n", 
			currentPlayer, postDeckCount, postHandCount, postDiscardCount, cardFailedCount);
			errorCount++;
		}


		if(errorCount > 0)
		{
			failCount++;
		}

/*
		printf("Players: %d PreDeckCount: %d PreHandCount: %d PreDiscardCount: %d DeckTreasure: %d HandTreasure: %d InitFailed Count: %d\n", 
			    numPlayers, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
		printf("Players: %d PostDeckCount: %d PostHandCount: %d PostDiscardCount: %d DeckTreasure: %d HandTreasure: %d Card Failed Count: %d\n", 
			    numPlayers, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
*/
	}
	printf("\n****************************************\nSmithy Random Test Summary\n****************************************\nTest Count = %d\nErrors = %d\n",
		   testCount,failCount);

	return 0;
} 