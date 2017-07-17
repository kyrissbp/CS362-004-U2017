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
	int testFailed = 0;
	int failCount = 0;
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

	

	
	printf("\n------------ Card Test: Smithy -----------\n");
	printf("\nTest 1: Play Smithy With Custom Starting Hand\n\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);


	// Give player 1 and Smithy
	G.hand[0][0] = smithy;

	// Set P1 deck to contain 5 gold (easy to see what has been drawn)
	for(i = 0; i < G.deckCount[0]; i++)
	{
		G.deck[0][i] = gold;
	}


	printf("\nPlayer 1 initial hand:\n");
	for(i = 0; i < G.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial deck:\n");
	for(i = 0; i < G.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial discard card pile:\n");
	for(i = 0; i < G.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial played card pile:\n");
	for(i = 0; i < G.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	// Play Smithy
	printf("\n...play smithy...\n");
	int b = cardEffect(smithy,0,0,0,&G,0,0);
	assert(b == 0);

	printf("\nPlayer 1 new hand:\n");
	for(i = 0; i < G.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new deck:\n");
	for(i = 0; i < G.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new discard card pile:\n");
	for(i = 0; i < G.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new played card pile:\n");
	for(i = 0; i < G.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	
	// Check final state
	if(G.hand[0][0] != gold ||
	   G.hand[0][1] != copper ||
	   G.hand[0][2] != estate ||
	   G.hand[0][3] != copper ||
	   G.hand[0][4] != copper ||
	   G.hand[0][5] != gold ||
	   G.hand[0][6] != gold ||
	   G.handCount[0] != 7)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 1 FAILED: Incorrect Cards In Hand\n");
	}
	if(G.deck[0][0] != gold ||
	   G.deck[0][1] != gold ||
	   G.deckCount[0] != 2)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Cards In Deck\n");
	}
	if(G.handCount[0] != 7)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Hand Count\n");
	}
	if(G.deckCount[0] != 2)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Deck Count\n");
	}
	if(G.discardCount[0] > 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Cards Added To Discard Pile\n");
	}
	if(G.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Too Many Cards Played\n");
	}
	if(G.playedCards[0] != smithy)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Card Played\n");
	}


	if(testFailed == 0)
	{
		printf("\nTest 1 Passed!\n");
	}
	

	if(failCount == 0)
	{
		printf("\nAll Tests Passed!\n");
	}
	

	printf("\n------------ End Of Unit Test: Smithy -----------\n"); 
	

	return 0;
} 