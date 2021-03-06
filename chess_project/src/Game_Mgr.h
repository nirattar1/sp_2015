#ifndef DRAUGHTS_
#define DRAUGHTS_


//the "game manager" is responsible for managing a game.
//contains the program's "main" function.
//they are responsible for:
//1. launching console/graphic UI,
//2. determining settings, managing turns,
//3. and also serves as an interaction with the minimax. (contains scoring funcs.)
//

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
//#define TESTING


//includes
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"


//global settings + defaults
extern int			SETTINGS_GAME_MODE;
extern color_t 		SETTINGS_USER_COLOR;
extern	color_t		SETTINGS_NEXT_PLAYER;
extern int 		SETTINGS_MAX_DEPTH;
extern int 		_RunModeIsGui;

#define GAME_MODE_PLAYER_VS_PLAYER 	1
#define GAME_MODE_PLAYER_VS_CPU 	2
#define	 DEFAULT_GAME_MODE		GAME_MODE_PLAYER_VS_PLAYER
#define DEFAULT_USER_COLOR 		COLOR_WHITE
#define	 DEFAULT_NEXT_PLAYER 	COLOR_WHITE
#define DEFAULT_MAX_DEPTH 		1
#define MAX_DEPTH_MIN_VALUE 	1
#define MAX_DEPTH_MAX_VALUE 	4
#define MAX_DEPTH_BEST_VALUE 	5
#define MAX_COMMAND_LENGTH 		51
#define MAX_FILE_NAME_LENGTH	MAX_COMMAND_LENGTH

//texts
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define PIECE_NOT_OF_PLAYER "The specified position does not contain your piece\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"
#define WRONG_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE "Illegal move\n"
 
#define WRONG_ROOK_POSITION "Wrong position for a rook\n"
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"

#define TIE "The game ends in a tie\n"


//error codes for settings command
typedef enum
{
	SETTING_COMMAND_STATUS_OK,
	SETTING_COMMAND_STATUS_ILLEGAL_COMMAND,
	SETTING_COMMAND_STATUS_WRONG_MINIMAX_DEPTH,
	SETTING_COMMAND_STATUS_WRONG_GAME_MODE,
	SETTING_COMMAND_STATUS_WRONG_FILE_NAME,
	SETTING_COMMAND_STATUS_WRONG_POSITION,
	SETTING_COMMAND_STATUS_BAD_PIECE_SET,
	SETTING_COMMAND_STATUS_WRONG_BOARD_INITIALIZATION,
	SETTING_COMMAND_STATUS_PIECE_NOT_OF_PLAYER,
	SETTING_COMMAND_STATUS_ILLEGAL_MOVE_FOR_PLAYER

}
user_command_errorcode_t;


//function pointers for interaction with the user.
//there will be one such for GUI and one for console UI.
typedef struct {
	void 	(*DisplayUpdatedBoardFunc) 	(game_state_t * game);
	int 	(*SelectUserMoveFunc) 		(game_state_t * game, move_t * selected_move);
	void 	(*HandleCheck) 	(play_status_t play_status, color_t next_player);
	void 	(*HandleEnd) 	(game_state_t * game, play_status_t play_status, color_t next_player);


} game_mgr_handlers_t;


//functions

game_mgr_handlers_t GetGameMgrHandlers (int runModeIsGui);

//program's main.
//launches the game in console/graphic UI.
//parameter 0 - "gui" or "console"
//(default=console)
int main (int argc, char * argv[]);

//check whether a file exists.
int DoesFileExist(const char *filename);

//check if a file in location "filename", can be opened for writing.
//returns: 1 if yes (file can be opened for writing),
//0 if not.
int FileCanOpenForWriting (const char * filename);

#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));

//function to apply default settings
void Settings_ResetDefaults();

//getters and setters for all settings
int Settings_GameMode_Get();
void Settings_GameMode_Set(int mode);
color_t Settings_NextPlayer_Get();
void Settings_NextPlayer_Set(color_t player);
color_t Settings_UserColor_Get();
color_t Settings_CPUColor_Get();
void Settings_UserColor_Set(color_t color);
int Settings_MaxDepth_Get();
void Settings_MaxDepth_Set(int max_depth);


//will compute the best depth for minimax running.
//simple implementation, just returns a value based on the number of pieces.
int BestDepthCompute (game_state_t * game, color_t current_player);

//scoring function to use with minimax.
//based on player and game state.
int BasicScoringFunction (game_state_t * game, color_t player, color_t current_player);


//prints the board
void PrintBoard(game_state_t * game);


//one turn of the CPU.
void CPUTurn (game_state_t * game);

//one turn of the user.
int UserTurn (game_state_t * game);

//manages game
void DoGame(game_state_t * game);


//print a list of moves in good format
void MovesListPrint( LINK head);

//will print the move
void MovePrint (move_t * move);



#endif  
