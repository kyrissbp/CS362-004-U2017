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
	struct gameState G2;
	struct gameState G3;
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

	

	
	printf("\n------------ Card Test: Adventurer -----------\n");
	printf("\nTest 1: Play Adventurer With Starting Hand\n\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);


	// Give player 1 and Adventurer
	G.hand[0][0] = adventurer;


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

	printf("\nPlayer 1 initial played card pile:\n");
	for(i = 0; i < G.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	// Play Adventurer
	printf("\n...play adventurer...\n");
	int b = cardEffect(adventurer,0,0,0,&G,0,0);
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

	printf("\nPlayer 1 new played card pile:\n");
	for(i = 0; i < G.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G.playedCards[i], name);

		printf("Card: %s \n", name);
	}


	// Check final state
	if(G.hand[0][0] != copper ||
	   G.hand[0][1] != copper ||
	   G.hand[0][2] != estate ||
	   G.hand[0][3] != copper ||
	   G.hand[0][4] != copper ||
	   G.hand[0][5] != copper ||
	   G.handCount[0] != 6)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 1 FAILED: Incorrect Cards In Hand\n");
	}
	if(G.deck[0][0] != estate ||
	   G.deck[0][1] != estate ||
	   G.deck[0][2] != copper ||
	   G.deckCount[0] != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Cards In Deck\n");
	}
	if(G.handCount[0] != 6)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Hand Count\n");
	}
	if(G.deckCount[0] != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Deck Count\n");
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
	if(G.playedCards[0] != adventurer)
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
	
	printf("\n-----------------------------------------------\n");
	printf("\nTest 2: Play Adventurer With Reshuffle Required!\n");

	a = initializeGame(numPlayers, k, seed, &G2); // re-initialize game

	// Set the 1st card in player's hand to adventurer
	G2.hand[0][0] = adventurer;

	// Set P1 deck to contain 4 estates and one gold
	for(i = 0; i < G2.deckCount[0] - 1; i++)
	{
		G2.deck[0][i] = estate;
	}
	G2.deck[0][G2.deckCount[0]-1] = gold;

	// Add a silver to P1 discard pile
	G2.discard[0][G2.discardCount[0]++] = silver;


	printf("Player 1 initial hand:\n");
	for(i = 0; i < G2.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial deck:\n");
	for(i = 0; i < G2.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	
	printf("\nPlayer 1 initial discard card pile:\n");
	for(i = 0; i < G2.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial played card pile:\n");
	for(i = 0; i < G2.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	
	// Play Adventurer
	// Adventurer searches the current deck until the gold is found, then must reshuffle to retrieve
	// the silver in the discard pile as the 2nd treasure.
	printf("\n...play adventurer...\n");
	int c = cardEffect(adventurer,0,0,0,&G2,0,0);
	assert(c == 0);


	printf("\nPlayer 1 new hand:\n");
	for(i = 0; i < G2.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new deck:\n");
	for(i = 0; i < G2.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new discard card pile:\n");
	for(i = 0; i < G2.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new played card pile:\n");
	for(i = 0; i < G2.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G2.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	// Check final state
	testFailed = 0; // Reset test failed

	if(G2.hand[0][0] != silver ||
	   G2.hand[0][1] != copper ||
	   G2.hand[0][2] != estate ||
	   G2.hand[0][3] != copper ||
	   G2.hand[0][4] != copper ||
	   G2.hand[0][5] != gold ||
	   G2.handCount[0] != 6)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 2 FAILED: Incorrect Cards In Hand\n");
	}
	if(G2.discard[0][0] != estate ||
	   G2.discard[0][1] != estate ||
	   G2.discard[0][2] != estate ||
	   G2.discard[0][3] != estate ||
	   G2.discardCount[0] != 4)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 2 FAILED: Incorrect Cards In Discard\n");
	}
	if(G2.handCount[0] != 6)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Hand Count\n");
	}
	if(G2.deckCount[0] != 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Deck Count\n");
	}
	if(G2.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Too Many Cards Played\n");
	}
	if(G2.playedCards[0] != adventurer)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Card Played\n");
	}
	if(testFailed == 0)
	{
		printf("\nTest 2 Passed!\n");
	}


printf("\n-----------------------------------------------\n");
	printf("\nTest 3: Play Adventurer With Only One Treasure Left in Deck\n");

	a = initializeGame(numPlayers, k, seed, &G3); // re-initialize game

	// Set the 1st card in player's hand to adventurer
	G3.hand[0][0] = adventurer;

	// Set P1 deck to contain 4 estates and one gold
	for(i = 0; i < G3.deckCount[0] - 1; i++)
	{
		G3.deck[0][i] = estate;
	}
	G3.deck[0][G3.deckCount[0]-1] = gold;

	// Add a mine to P1 discard pile ratehr than a silver
	G3.discard[0][G3.discardCount[0]++] = mine;


	printf("Player 1 initial hand:\n");
	for(i = 0; i < G3.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial deck:\n");
	for(i = 0; i < G3.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	
	printf("\nPlayer 1 initial discard card pile:\n");
	for(i = 0; i < G3.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 initial played card pile:\n");
	for(i = 0; i < G3.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	
	// Play Adventurer
	// Adventurer searches the current deck until the gold is found, then must reshuffle, but only one treasure
	// is found...
	printf("\n...play adventurer...\n");
	int x = cardEffect(adventurer,0,0,0,&G3,0,0);
	assert(x == 0);


	printf("\nPlayer 1 new hand:\n");
	for(i = 0; i < G3.handCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.hand[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new deck:\n");
	for(i = 0; i < G3.deckCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.deck[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new discard card pile:\n");
	for(i = 0; i < G3.discardCount[0]; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.discard[0][i], name);

		printf("Card: %s \n", name);
	}

	printf("\nPlayer 1 new played card pile:\n");
	for(i = 0; i < G3.playedCardCount; i++)
	{
		char name[MAX_STRING_LENGTH];
		cardNumToName(G3.playedCards[i], name);

		printf("Card: %s \n", name);
	}

	// Check final state
	testFailed = 0; // Reset test failed

	if(G3.hand[0][0] != gold ||
	   G3.hand[0][1] != copper ||
	   G3.hand[0][2] != estate ||
	   G3.hand[0][3] != copper ||
	   G3.hand[0][4] != copper ||
	   G3.handCount[0] != 5)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 3 FAILED: Incorrect Cards In Hand\n");
	}
	if(G3.discard[0][0] != mine ||
	   G3.discard[0][1] != estate ||
	   G3.discard[0][2] != estate ||
	   G3.discard[0][3] != estate ||
	   G3.discard[0][4] != estate ||
	   G3.discardCount[0] != 5)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 3 FAILED: Incorrect Cards In Discard\n");
	}
	if(G3.handCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Hand Count\n");
	}
	if(G3.deckCount[0] != 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Deck Count\n");
	}
	if(G3.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Too Many Cards Played\n");
	}
	if(G3.playedCards[0] != adventurer)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Card Played\n");
	}
	if(testFailed == 0)
	{
		printf("\nTest 3 Passed!\n");
	}

	if(failCount == 0)
	{
		printf("\nAll Tests Passed!\n");
	}

	printf("\n------------ End Of Unit Test: getCost -----------\n"); 
	

	return 0;
} 