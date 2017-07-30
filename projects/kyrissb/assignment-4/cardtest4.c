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

	

	
	printf("\n------------ Card Test: Steward -----------\n");
	printf("\nTest 1: Play Steward With Draw 2 Cards Option\n\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);


	// Give player 1 and Steward
	G.hand[0][0] = steward;
	G.coins = G.coins - 1; // Reduce coins by 1 for taking out a copper

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

	printf("\nPlayer 1 total coins: %d\n",G.coins);

	// Play Steward (option 1: draw 2 cards)
	printf("\n...play steward...\n");
	int b = cardEffect(steward,1,0,0,&G,0,0);
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

	printf("\nPlayer 1 total coins: %d\n",G.coins);

	
	// Check final state
	// Discarded Stweard, gained 2 gold (1 replaces steward, other appeneded to end)
	if(G.hand[0][0] != gold ||
	   G.hand[0][1] != copper ||
	   G.hand[0][2] != estate ||
	   G.hand[0][3] != copper ||
	   G.hand[0][4] != copper ||
	   G.hand[0][5] != gold ||
	   G.handCount[0] != 6)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 1 FAILED: Incorrect Cards In Hand\n");
	}
	// Drew 2 cards, so total is now 5 - 2 =3 
	if(G.deck[0][0] != gold ||
	   G.deck[0][1] != gold ||
	   G.deck[0][2] != gold ||
	   G.deckCount[0] != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Cards In Deck\n");
	}
	//Discard steward, gain 2 gold
	if(G.handCount[0] != 6)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Hand Count\n");
	}
	// Drew 2, so deck = 5 - 3
	if(G.deckCount[0] != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Deck Count\n");
	}
	// No cards discarded
	if(G.discardCount[0] > 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Cards Added To Discard Pile\n");
	}
	// Steward was played, so 0 + 1
	if(G.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Too Many Cards Played\n");
	}
	// Played card should be steward
	if(G.playedCards[0] != steward)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect Card Played\n");
	}
	// No change in coins for option 1 and starting hand has 3 copper
	if(G.coins != 3)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 1 FAILED: Incorrect coin count\n");
	}


	if(testFailed == 0)
	{
		printf("\nTest 1 Passed!\n");
	}

	printf("\n------------------------------------------\n");
	printf("\nTest 2: Play Steward With Coins + 2 Option\n\n");

	testFailed = 0; // Reset tests failed for round 2

	// Initialize game 
	int c = initializeGame(numPlayers, k, seed, &G2);
	assert(c == 0);


	// Give player 1 and Steward
	G2.hand[0][0] = steward;
	G2.coins = G2.coins - 1; // Reduce coins by 1 for taking out a copper

	// Set P1 deck to contain 5 gold (easy to see what has been drawn)
	for(i = 0; i < G2.deckCount[0]; i++)
	{
		G2.deck[0][i] = gold;
	}


	printf("\nPlayer 1 initial hand:\n");
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

	printf("\nPlayer 1 total coins: %d\n",G2.coins);

	// Play Steward (option 1: draw 2 cards)
	printf("\n...play steward...\n");
	int d = cardEffect(steward,2,0,0,&G2,0,0);
	assert(d == 0);

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

	printf("\nPlayer 1 total coins: %d\n",G2.coins);

	
	// Check final state
	// Played steward, no new cards should be added
	if(G2.hand[0][0] != copper ||
	   G2.hand[0][1] != copper ||
	   G2.hand[0][2] != estate ||
	   G2.hand[0][3] != copper ||
	   G2.handCount[0] != 4)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 2 FAILED: Incorrect Cards In Hand\n");
	}
	// No draw, so deck should still be 5 gold
	if(G2.deck[0][0] != gold ||
	   G2.deck[0][1] != gold ||
	   G2.deck[0][2] != gold ||
	   G2.deck[0][3] != gold ||
	   G2.deck[0][4] != gold ||
	   G2.deckCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Cards In Deck\n");
	}
	// Played steward, should be 4 cards left
	if(G2.handCount[0] != 4)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Hand Count\n");
	}
	// No draw, should be 5 cards still
	if(G2.deckCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Deck Count\n");
	}
	// No cards discarded
	if(G2.discardCount[0] > 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Cards Added To Discard Pile\n");
	}
	// Steward was played, so 0 + 1
	if(G2.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Too Many Cards Played\n");
	}
	// Played card should be steward
	if(G2.playedCards[0] != steward)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect Card Played\n");
	}
	// Steward adds 2 coins to 3 existing = 5
	if(G2.coins != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 2 FAILED: Incorrect coin count\n");
	}


	if(testFailed == 0)
	{
		printf("\nTest 2 Passed!\n");
	}
	


	printf("\n---------------------------------------------\n");
	printf("\nTest 3: Play Steward With Trash 2 Cards Option\n\n");

	testFailed = 0; // Reset

	// Initialize game 
	int e = initializeGame(numPlayers, k, seed, &G3);
	assert(e == 0);


	// Give player 1 and Steward
	G3.hand[0][0] = steward;

	// Set cards 3 and 4 to unique cards to observe trashing
	G3.hand[0][3] = tribute;
	G3.hand[0][4] = cutpurse;

	G3.coins = G3.coins - 3; // Reduce coins by 3 for taking out 3 coppers


	// Set P1 deck to contain 5 gold (easy to see what has been drawn)
	for(i = 0; i < G3.deckCount[0]; i++)
	{
		G3.deck[0][i] = gold;
	}


	printf("\nPlayer 1 initial hand:\n");
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

	printf("\nPlayer 1 total coins: %d\n",G3.coins);

	// Play Steward (option 3: trash 2 cards) Trash tribute and cutpurse (zero-based pos 3 and 4)
	printf("\n...play steward...\n");
	int f = cardEffect(steward,3,3,4,&G3,0,0);
	assert(f == 0);

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

	printf("\nPlayer 1 total coins: %d\n",G3.coins);

	
	// Check final state
	// Discarded Steward, trashed tribute and cutpurse
	if(G3.hand[0][0] != estate ||
	   G3.hand[0][1] != copper ||
	   G3.handCount[0] != 2)
	{
		testFailed = 1;
		failCount ++;
		printf("\nTEST 3 FAILED: Incorrect Cards In Hand\n");
	}
	// Deck is untouched
	if(G3.deck[0][0] != gold ||
	   G3.deck[0][1] != gold ||
	   G3.deck[0][2] != gold ||
	   G3.deck[0][3] != gold ||
	   G3.deck[0][4] != gold ||
	   G3.deckCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Cards In Deck\n");
	}
	// Discarded Steward, trashed tribute and cutpurse, 2 cards left
	if(G3.handCount[0] != 2)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Hand Count\n");
	}
	// Deck size unchanged (no draw)
	if(G3.deckCount[0] != 5)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Deck Count\n");
	}
	// No cards discarded because cards were trashed and should not go back to deck
	if(G3.discardCount[0] > 0)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Cards Added To Discard Pile\n");
	}
	// Steward was played, so 0 + 1
	if(G3.playedCardCount != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Too Many Cards Played\n");
	}
	// Played card should be steward
	if(G3.playedCards[0] != steward)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect Card Played\n");
	}
	// No change in coins for option 3 and starting hand has 1 copper
	if(G3.coins != 1)
	{
		testFailed = 1;
		if(failCount < 1)
		{
			failCount ++;
		}
		printf("\nTEST 3 FAILED: Incorrect coin count\n");
	}


	if(testFailed == 0)
	{
		printf("\nTest 3 Passed!\n");
	}
	

	if(failCount == 0)
	{
		printf("\nAll Tests Passed!\n");
	}
	

	printf("\n------------ End Of Unit Test: Steward -----------\n"); 
	

	return 0;
} 