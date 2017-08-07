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

	// Supply Cards
	int cards[17] =
	{
		curse,
		estate,
		duchy,
		province,
		copper,
		silver,
		gold,
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

	// Instantiate an array with 5 numbers that are beyond the maximum number of card types
	int badCards[5] =
	{
		remodel,
		outpost,
		salvager,
		feast,
		baron
	};

	
	printf("\n------------ Unit Test: supplyCount -----------\n");
	printf("\nTest 1: Get Counts OF Existing Supply Cards\n\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);

	int cardCount = 0;
	for (i = 0; i < 17; i++)
	{
		cardCount = supplyCount(cards[i], &G);
		char name[MAX_STRING_LENGTH];
		cardNumToName(cards[i], name);

		// If the card is a victory card or garden, there should be 8
		if((i > 0 && i < 4) || i == 8)
		{
			assert(cardCount == 8);
		}
		// If the card is copper, there should be 60 - 7 dealt to each player
		else if(i == 4)
		{
			assert(cardCount = (60 - (numPlayers * 7)));
		}
		// There should be 40 silver
		else if(i == 5)
		{
			assert(cardCount == 40);
		}
		// There should be 30 gold
		else if(i == 6)
		{
			assert(cardCount == 30);
		}
		else
		{
			assert(cardCount == 10); 
		}

		// Format output so tabs align
		if(i == 7)
		{
			printf("Card tested = %s\tNumber in supply = %d\n", name,cardCount);
		}
		else
		{
			printf("Card tested = %s\t\tNumber in supply = %d\n", name,cardCount);
		}
	}

	printf("\nTest 2: Get Counts Cards That Are Not In The Game\n\n");

	for (i = 0; i < 5; i++)
	{
		cardCount = supplyCount(badCards[i], &G);
		char name[MAX_STRING_LENGTH];
		cardNumToName(badCards[i], name);
		assert(cardCount < 0);

		printf("Card tested = %s\t\tReturn value = %d\n", name,cardCount);
		
	}


	printf("\nAll Tests Passed!\n");

	printf("\n------------ End Of Unit Test: supplyCount -----------\n"); 
	

	return 0;
} 