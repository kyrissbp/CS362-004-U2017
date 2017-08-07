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

	

	
	printf("\n------------ Card Test: Village -----------\n");
	printf("\nTest 1: Play Village With Custom Starting Hand\n\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);


	// Give player 1 and Village
	G.hand[0][0] = village;

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

	printf("\nPlayer 1 total actions this turn: %d\n",G.numActions);

	// Play Village (draw one card, + 2 actions)
	printf("\n...play village...\n");
	int b = cardEffect(village,0,0,0,&G,0,0);
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

	printf("\nPlayer 1 total actions this turn: %d\n",G.numActions);

	
	// Check final state
	if(G.hand[0][0] != gold ||
	   G.hand[0][1] != copper ||
	   G.hand[0][2] != estate ||
	   G.hand[0][3] != copper ||
	   G.hand[0][4] != copper ||
	   G.handCount[0] != 5)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 1 FAILED: Incorrect Cards In Hand\n");
	}
	if(G.deck[0][0] != gold ||
	   G.deck[0][1] != gold ||
	   G.deck[0][2] != gold ||
	   G.deck[0][3] != gold ||
	   G.deckCount[0] != 4)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Cards In Deck\n");
	}
	if(G.handCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Hand Count\n");
	}
	if(G.deckCount[0] != 4)
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
		printf("\nTEST 1 FAILED: Wrong Number Of Cards Played\n");
	}
	if(G.playedCards[0] != village)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Card Played\n");
	}
	if(G.numActions != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect action count update\n");
	}


	if(testFailed == 0)
	{
		printf("\nTest 1 Passed!\n");
	}
	

	if(failCount == 0)
	{
		printf("\nAll Tests Passed!\n");
	}
	

	printf("\n------------ End Of Unit Test: Village -----------\n"); 
	

	return 0;
} 