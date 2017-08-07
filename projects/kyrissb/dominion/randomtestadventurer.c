/* 
Author: Brandon P. Kyriss
Title: randomtestcard1.c
This is a random tester for the Dominion
adventurer card for CS 362_400.
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

	printf("\n****************************************\nBeginning Adventurer Random Test\n****************************************\n");

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
		int preDeckTreasureCount = 0;
		int preHandTreasureCount = 0;
		int preHandPlayedCount = 0;

		int postHandCount = 0;
		int postDeckCount = 0;
		int postDiscardCount = 0;
		int postDeckTreasureCount = 0;
		int postHandTreasureCount = 0;
		int postHandPlayedCount = 0;

		

		// Initialize game 
		int a = initializeGame(numPlayers, k, seed, &TestState);
		if(a != 0)
		{
			initFailedCount++;
			//printf("Players: %d InitFailed Count: %d\n", 
			//    numPlayers, initFailedCount);
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
		TestState.hand[currentPlayer][0] = adventurer;
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


		for(j = 0; j < preHandCount; j++)
		{
			if(TestState.hand[currentPlayer][j] == copper ||
			   TestState.hand[currentPlayer][j] == silver ||
			   TestState.hand[currentPlayer][j] == gold)
			{
				preHandTreasureCount++;
			}
		}
		// Since full deck treasure count counts the hand as well, subtract out treasures in the hand
		preDeckTreasureCount = fullDeckCount(currentPlayer,copper,&TestState) +
							   fullDeckCount(currentPlayer,silver,&TestState) +
							   fullDeckCount(currentPlayer,gold,&TestState)
							   - preHandTreasureCount;

		// Check played card count
		preHandPlayedCount = TestState.playedCardCount;


		//int abc;
		//for(abc = 0; abc < preHandCount; abc++)
		//	printf("HandCard %d = %d", abc+1, TestState.hand[currentPlayer][abc]);

		// Set whose turn
		TestState.whoseTurn = currentPlayer;
		int b = cardEffect(adventurer,0,0,0,&TestState,0,0);
		if(b != 0)
		{
			cardFailedCount++;
		}

		postDiscardCount = TestState.discardCount[currentPlayer];
		postDeckCount = TestState.deckCount[currentPlayer];
		postHandCount = TestState.handCount[currentPlayer];

		for(j = 0; j < postHandCount; j++)
		{
			if(TestState.hand[currentPlayer][j] == copper ||
			   TestState.hand[currentPlayer][j] == silver ||
			   TestState.hand[currentPlayer][j] == gold)
			{
				postHandTreasureCount++;
			}
		}

		postDeckTreasureCount = fullDeckCount(currentPlayer,copper,&TestState) +
					   		   fullDeckCount(currentPlayer,silver,&TestState) +
					           fullDeckCount(currentPlayer,gold,&TestState)
					           - postHandTreasureCount;

		// Check played card
		postHandPlayedCount = TestState.playedCardCount;
	

		// Add 1 back to current player fo output					           
		currentPlayer++;

		// If there is more than one treasure in the deck, deck treasure count should be reduced by 2	           
		if(preDeckTreasureCount > 1)
		{

			if(preDeckTreasureCount != postDeckTreasureCount + 2)
			{	printf("\nError: Deck began with > 2 treasures, but did not lose exactly 2!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
				errorCount++;
			}
		}
		// If we started with only one treasure in the deck, deck treasure count should be reduced by 1
		else if(preDeckTreasureCount == 1)
		{
			if(isTesting)
				printf("\nRARE CASE: Only 1 treasure in deck\n");
			if(preDeckTreasureCount != postDeckTreasureCount + 1)
			{	printf("\nError: Deck began with only 1 treasure, but did not lose exactly 1!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);	
				errorCount++;
			}
		}
		// If we started with no treasures in the deck, dech treasure count should remain the same
		else
		{
			if(isTesting)
				printf("\nRARE CASE: No treasures to draw\n");
			if(preDeckTreasureCount != postDeckTreasureCount)
			{	printf("\nError: There were no treasures in the starting deck, but the deck treasure count changed!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
				errorCount++;
			}
		}

		// If there is more than one treasure in the deck, two treasures should be added to hand	           
		if(preDeckTreasureCount > 1)
		{

			if(postHandTreasureCount != preHandTreasureCount + 2)
			{	printf("\nError: Deck began with > 2 treasures, hand did not gain exactly 2!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
				errorCount++;
			}
		}
		// If there is only one treasure in the deck, it should now be in the hand
		else if(preDeckTreasureCount == 1)
		{
			if(postHandTreasureCount != preHandTreasureCount + 1)
			{	printf("\nError: Deck began with only 1 treasure, but hand did not gain exactly 1!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
				errorCount++;
			}
		}
		// If there were no treasures in the deck, hand stays the same
		else
		{
			if(postHandTreasureCount != preHandTreasureCount)
			{	
				printf("\nError: There were no treasures in the starting deck, but hand treasure count changed!\n");
				printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t InitFailed Count: %d\n", 
			    currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, initFailedCount);
				printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t Card Failed Count: %d\n", 
			    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, cardFailedCount);
				errorCount++;
			}
		}

		if(preHandPlayedCount != 0)
		{
			printf("\nError: Played cards was not empty at start of turn!\n");
			printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t PlayedCards: %d\t InitFailed Count: %d\n", 
			currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, preHandPlayedCount, initFailedCount);
			printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t PlayedCards: %d\t Card Failed Count: %d\n", 
		    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, postHandPlayedCount, cardFailedCount);
			errorCount++;
		}

		if(postHandPlayedCount != 1 )
		{
			printf("\nError: Adventurer was not added to the played pile (discarded)!\n");
			printf("Player: %d\t PreDeckCount: %d\t PreHandCount: %d\t PreDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t PlayedCards: %d\t InitFailed Count: %d\n", 
			currentPlayer, preDeckCount, preHandCount, preDiscardCount, preDeckTreasureCount, preHandTreasureCount, preHandPlayedCount, initFailedCount);
			printf("Player: %d\t PostDeckCount: %d\t PostHandCount: %d\t PostDiscardCount: %d\t DeckTreasure: %d\t HandTreasure: %d\t PlayedCards: %d\t Card Failed Count: %d\n", 
		    currentPlayer, postDeckCount, postHandCount, postDiscardCount, postDeckTreasureCount, postHandTreasureCount, postHandPlayedCount, cardFailedCount);
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
	printf("\n****************************************\nAdventurer Random Test Summary\n****************************************\nTest Count = %d\nErrors = %d\n",
		   testCount,failCount);

	return 0;
} 