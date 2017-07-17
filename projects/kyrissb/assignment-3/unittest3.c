#include "dominion.h"
#include "interface.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char** argv)
{
	struct gameState G;
	int numPlayers = 2;
	int seed = 1000;
	int i;
	int j;
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


	printf("\n------------ Unit Test: fullDeckCount -----------\n");
	printf("\nTest 1: Check Initial Deck\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);

	int deckCount = 0;

	for(i = 0; i < numPlayers; i++)
	{
		printf("\nPlayer %d deck count:\n", i+1);
		printf("Deck contains %d cards\n", G.deckCount[i]);
		printf("Hand contains %d cards\n", G.handCount[i]);
		deckCount = fullDeckCount(i,copper,&G);
		assert(deckCount == 7);

		printf("Copper = %d   \tExpected = 7\n", deckCount);
		deckCount = fullDeckCount(i,estate,&G);
		assert(deckCount == 3);

		printf("Estate = %d   \tExpected = 3\n", deckCount);
	}

	printf("\nTest 2: Set All P1 Cards To Adventurer And P2 Cards To Smithy\n");

	// Set all cards in P1 and P2's hand and deck to adventurers
	for(i = 0; i < numPlayers; i++)
	{
		for(j = 0; j < G.deckCount[i]; j++)
		{
			if(i == 0)
			{
				G.deck[i][j] = adventurer;
				G.hand[i][j] = adventurer;
			}
			else
			{
				G.deck[i][j] = smithy;
				G.hand[i][j] = smithy;
			}
		}
	}

	for(i = 0; i < numPlayers; i++)
	{
		printf("\nPlayer %d deck count:\n", i+1);
		printf("Deck contains %d cards\n", G.deckCount[i]);
		printf("Hand contains %d cards\n", G.handCount[i]);

		deckCount = fullDeckCount(i,copper,&G);
		assert(deckCount == 0);
		printf("Copper = %d\tExpected = 0\n", deckCount);

		deckCount = fullDeckCount(i,estate,&G);
		assert(deckCount == 0);
		printf("Estate = %d\tExpected = 0\n", deckCount);

		deckCount = fullDeckCount(i,adventurer,&G);
		if(i == 0)
		{
			assert(deckCount == 10);
			printf("Adventurer = %d\tExpected = 10\n", deckCount);
		}
		else
		{
			assert(deckCount == 0);
			printf("Adventurer = %d\tExpected = 0\n", deckCount);
		}

		deckCount = fullDeckCount(i,smithy,&G);
		if(i == 0)
		{
			//assert(deckCount == 0);
			printf("Smithy = %d   \tExpected = 0\n", deckCount);
		}
		else
		{
			//assert(deckCount == 10);
			printf("Smithy = %d   \tExpected = 10\n", deckCount);
		}

	}

	printf("\nTest 3: Add a mine to P1 discard pile and count mines\n");
	deckCount = fullDeckCount(0,mine,&G);
	assert(deckCount == 0);
	printf("\nBefore Mine Added:\n", deckCount);
	printf("\nMine = %d   \tExpected = 0\n", deckCount);


	// Add a mine to P1 discard
	printf("\n...adding a mine P1 discard...\n");
	G.discard[0][0] = mine;
	G.discardCount[0] ++; // Must increment discardCount for P1 for loop to pick this up.
	deckCount = fullDeckCount(0,mine,&G);
	assert(deckCount == 1);
	printf("\nAfter Mine Added:\n", deckCount);
	printf("\nMine = %d   \tExpected = 0\n", deckCount);


	printf("\nAll Tests Passed!\n");

	printf("\n------------ End Of Unit Test: fullDeckCount -----------\n"); 
	
	return 0;
} 