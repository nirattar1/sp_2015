#ifndef DRAUGHTS_
#define DRAUGHTS_

//debug
//#define DEBUG

#ifdef DEBUG
	#define IS_DEBUG 1
#else
	#define IS_DEBUG 0
#endif

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif


//for unit testing,
//if defined will run tests main instead of main.
#define TESTING



#include <stdlib.h>
#include <stdio.h>
#include "Game.h"


//main class.
//will also include the settings.



//settings + defaults
extern color_t SETTINGS_USER_COLOR;
extern int SETTINGS_MAX_DEPTH;

#define DEFAULT_USER_COLOR COLOR_WHITE
#define DEFAULT_MAX_DEPTH 1

//

#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
 
#define WRONG_ROOK_POSITION "Wrong position for a rook\n"
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"

#define TIE "The game ends in a tie\n"

#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));


//get color of user/CPU.
color_t Settings_UserColor_Get();
color_t Settings_CPUColor_Get();
//set color of user
void Settings_UserColor_Set(color_t color);

//get/set max depth for minimax.
int Settings_MaxDepth_Get();
void Settings_MaxDepth_Set(int max_depth);

//prints the board
void PrintBoard(game_state_t * game);

//one turn of the CPU.
void CPUTurn (game_state_t * game);

//one turn of the user.
void UserTurn (game_state_t * game);

//manages game
void DoGame(game_state_t * game);

//print a list of moves in good format
void MovesListPrint( LINK head);


#endif  