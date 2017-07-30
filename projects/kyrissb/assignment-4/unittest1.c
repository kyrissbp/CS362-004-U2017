#include "dominion.h"
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

	
	
	printf("\n------------ Unit Test: isGameOver -----------\n");
	printf("\nTest 1: One Supply Pile Empty, Province Cards Not Empty\n");

	// Initialize game 
	int a = initializeGame(numPlayers, k, seed, &G);
	assert(a == 0);
	printf("adventurer supply count = %d, expected = 10\n", G.supplyCount[adventurer]);
	G.supplyCount[adventurer] = 0;
	printf("adventurer supply count = %d, expected = 0\n", G.supplyCount[adventurer]);
	int j = isGameOver(&G);
	assert(j == 0);
	printf("returned %d, not game over\n", j);

	printf("\nTest 2: Two Supply Piles Empty, Province Cards Not Empty\n");
	
	printf("smithy supply count = %d, expected = 10\n", G.supplyCount[smithy]);
	G.supplyCount[smithy] = 0;
	printf("smithy supply count = %d, expected = 0\n", G.supplyCount[smithy]);
	j = isGameOver(&G);
	assert(j == 0);
	printf("returned %d, not game over\n", j);

	printf("\nTest 3: Three Supply Piles Empty, Province Cards Not Empty\n");

	printf("mine supply count = %d, expected = 10\n", G.supplyCount[mine]);
	G.supplyCount[mine] = 0;
	printf("mine supply count = %d, expected = 0\n", G.supplyCount[mine]);
	j = isGameOver(&G);
	assert(j == 1);
	printf("returned %d, game over\n", j);

	printf("\nTest 4: Supply Piles Full, Empty Estate Pile\n");
	G.supplyCount[adventurer] = 10;
	G.supplyCount[smithy] = 10;
	G.supplyCount[mine] = 10;
	G.supplyCount[estate] = 0;
	printf("adventurer, smithy, and mine supply count reset = %d, %d, %d\n", 
		   G.supplyCount[adventurer],
		   G.supplyCount[smithy],
		   G.supplyCount[mine]);
	printf("estate supply count = %d, expected = 0\n", G.supplyCount[estate]);
	j = isGameOver(&G);
	assert(j == 0);
	printf("returned %d, not game over\n", j);

	printf("\nTest 5: Supply Piles Full, Empty Duchy Pile\n");
	G.supplyCount[estate] = 10;
	G.supplyCount[duchy] = 0;
	printf("estate supply count reset = %d\n", 
		   G.supplyCount[estate]);
	printf("duchy supply count = %d, expected = 0\n", G.supplyCount[duchy]);
	j = isGameOver(&G);
	assert(j == 0);
	printf("returned %d, not game over\n", j);

	printf("\nTest 6: Supply Piles Full, Empty Province Pile\n");
	G.supplyCount[duchy] = 10;
	G.supplyCount[province] = 0;
	printf("duchy supply count reset = %d\n", 
		   G.supplyCount[duchy]);
	printf("province supply count = %d, expected = 0\n", G.supplyCount[province]);
	j = isGameOver(&G);
	assert(j == 1);
	printf("returned %d, game over\n", j);


	printf("\nAll Tests Passed!\n");

	printf("\n------------ End Of Unit Test: isGameOver -----------\n"); 
	

	return 0;
} 