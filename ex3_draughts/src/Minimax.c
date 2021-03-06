/*
 * Minimax.c
 *
 *  Created on: Jun 14, 2015
 *      Author: nirattar
 */
#include "Minimax.h"
#include <stdio.h>
#include "Memory.h"
#include "Draughts.h"

//initialize global
int _NUM_LEAVES = 0;



//for testing. remove this function
//test function , updates child based on depth and child index.
//void TestUpdateState(int * state, int depth, int iChild)
//{
//	*state = *state + (depth * 10) + (iChild+1) ;
//}


void MinimaxChoose (STATE_TYPE * state, color_t player,
		ListNode * RootChildren,
		int current_depth, int max_depth,
		int (*ScoringFunction)(STATE_TYPE *, color_t),
		ListNode * (*ChildGenerateFunction)(STATE_TYPE *, color_t),
		int * chosenSon, int * chosenValue) //by reference, will update these for caller.
{


	//debug (only for ints)
	//DEBUG_PRINT(("current state: %d\n", *((int *) state)));

	//halt condition (leaf node)
	//update based on scoring function and return.
	if (current_depth==max_depth)
	{
		//compute this node's value and return it.
		*chosenSon = 0;
		//call scoring function to compute based on state.
		*chosenValue = (ScoringFunction(state, player));

		//debug
		DEBUG_PRINT(("scoring function value: %d\n", *chosenValue));

		//increment global leaves counter. (for debug)
		_NUM_LEAVES ++ ;
		DEBUG_PRINT(("number of leaves: %d\n", _NUM_LEAVES));
		return;
	}

	//get children.
	//(on first level - from argument, otherwise generate from state.)
	ListNode * Children;
	if (current_depth==0)
	{
		Children = RootChildren;
	}
	else
	{
		Children = ChildGenerateFunction (state, player);
	}


	//for each child (move):
	int numChildren = ListCount(Children);
	int iChild = 0;
	int * Scores = (int *) mymalloc (numChildren * (sizeof (int)) );
	ListNode * pChildren = NULL;
	for (pChildren = Children; pChildren !=NULL; pChildren = pChildren->next )
	{

		//create static copy of state.
		STATE_TYPE newState;
		char newBoard [BOARD_SIZE][BOARD_SIZE];
		newState.pieces = (board_column *) newBoard;
		CopyGameState(&newState, state);
		//memcpy (&newState, state, sizeof (STATE_TYPE));

		//update state based on child (play move)
		//TestUpdateState (&newState, current_depth, iChild);
		DoMove( (move_t *) pChildren->data , &newState);

		//debug
		DEBUG_PRINT(("if i play move %d board will look like:\n ", iChild));
		if (IS_DEBUG)
		{
			PrintBoard(&newState);
		}

		//call recursively to determine the score from this child.

		int childIndex;	//not really used.
		int childScore;
		MinimaxChoose(&newState, player, NULL, current_depth+1, max_depth,
				ScoringFunction, ChildGenerateFunction, &childIndex, &childScore);

		DEBUG_PRINT( ("current depth : %d. score from child %d: %d\n", current_depth, iChild, childScore));
		Scores [iChild] = childScore;
		iChild++;
	}

	//choose the child with the max / min level.
	//even depth (maximizer)- choose max.
	if (current_depth%2 == 0)
	{
		ArrFindMaxOrMin(Scores, numChildren, 1, chosenValue, chosenSon);
	}
	//odd depth (minimizer) - choose min.
	else
	{
		ArrFindMaxOrMin(Scores, numChildren, 0, chosenValue, chosenSon);
	}

	//free all children (got what we need from them).
	//(only on depth > 0), because caller needs children in level 0
	if (current_depth!=0)
	{
		ListFreeElements(Children, MoveFree);
	}
	//free scores of children.
	myfree(Scores);

	return;
}

//find max or min value in array
//if find_max = 1 -> will find max.
//if find_max = 0 -> will find min.
//will update : chosenValue with the value.
// chosenIndex with the index.
//if array is of length 0 , will return -1.
int ArrFindMaxOrMin (int * array, int arr_size,
		int find_max, int * chosenValue, int * chosenIndex)
{
	if (!array || arr_size==0)
	{
		return -1;
	}

	//initialize values
	int extremeValue = array[0];
	int extremeIndex = 0;

	//loop through array and find the extreme value.
	for (int i=0; i<arr_size; i++)
	{
		//if found a value that exceeds the extreme, change indication.
		if (((find_max==1) && array[i] > extremeValue)
			|| ((find_max==0) && array[i] < extremeValue))
		{
			extremeValue = array[i];
			extremeIndex = i;
		}
	}

	//update return arguments.
	*chosenValue = extremeValue;
	*chosenIndex = extremeIndex;
	return 1;
}

