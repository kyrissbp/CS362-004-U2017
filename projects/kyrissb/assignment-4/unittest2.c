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

	// Instantiate an array loaded with all 27 supply cards
	int cards[27] =
	{
		curse,
		estate,
		duchy,
		province,
		copper,
		silver,
		gold,
		adventurer,
		council_room,
		feast,
		gardens,
		mine,
		remodel,
		smithy,
		village,
		baron,
		great_hall,
		minion,
		steward,
		tribute,
		ambassador,
		cutpurse,
		embargo,
		outpost,
		salvager,
		sea_hag,
		treasure_map
	};

	// Instantiate an array with 5 numbers that are beyond the maximum number of card types
	int fakeCards[5] =
	{
		30,
		31,
		32,
		33,
		34
	};

	// Instantiate an array with the values of each card in the supply. 
	// Cost values from http://wiki.dominionstrategy.com rather than dominion.c to test
	int values[] =
	{
		0, // curse
		2, // estate,
		5, // duchy
		8, // province
		0, // copper
		3, // silver
		6, // gold
		6, // adventurer
		5, // council room
		4, // feast
		4, // gardens
		5, // mine
		4, // remodel
		4, // smithy
		3, // village
		4, // baron
		3, // great hall
		5, // minion
		3, // steward
		5, // tribute
		3, // ambassador
		4, // cutpurse
		2, // embargo
		5, // outpost
		4, // salvager
		4, // sea hag
		4, // treasure map
	};
	
	printf("\n------------ Unit Test: getCost -----------\n");
	printf("\nTest 1: Get All Card Values\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);
	
	for (i = 0; i < 27; i++)
	{
		j = getCost(cards[i]);

		char name[MAX_STRING_LENGTH];
		cardNumToName(cards[i], name);
		if(i == 8 || i == 26)
		{
			printf("Card tested = %s    \tvalue returned = %d   \tvalue expected = %d\n", name,j,values[i]);
		}
		else
		{
			printf("Card tested = %s      \tvalue returned = %d   \tvalue expected = %d\n", name,j,values[i]);
		}
		assert(j == values[i]);
	}

	printf("\nTest 2: Try To Get Values For Nonexistant Cards\n");

	for (i = 0; i < 5; i++)
	{
		j = getCost(fakeCards[i]);
		printf("Fake card %d: function returned %d\n", fakeCards[i],j);
		assert(j < 0);
	}


	printf("\nAll Tests Passed!\n");

	printf("\n------------ End Of Unit Test: getCost -----------\n"); 
	

	return 0;
} 