/*
 * Gui.h
 *
 *  Created on: Oct 11, 2015
 *      Author: nirattar
 */

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include "Gui_framework.h"

//this class is responsible for all the GUI windows in program.

#define WINDOW_TITLE "Chess"

//an enum that for all the windows in the program
typedef enum
{
	GUI_WINDOW_MAIN_MENU,
	GUI_WINDOW_PLAYER_SELECTION,
	GUI_WINDOW_SAVE,
	GUI_WINDOW_LOAD,
	GUI_WINDOW_SET_BOARD,
	GUI_WINDOW_AI_SETTINGS,
	GUI_WINDOW_GAME
} gui_window_t;

//gui globals
extern gui_window_t 	_NextWindow; //start with main menu.
extern Control * 		_CurrentWindow;

//responsible for creating menus, and handling events.
void Gui_Main ();

void Gui_Main_Game (game_state_t * game, Control * window, SDL_Surface * screen);

void Gui_UpdateBoard(game_state_t * game);

int Gui_SelectUserMove(game_state_t * game, move_t * selected_move);

void Gui_HandleCheck (play_status_t play_status, color_t next_player);

void Gui_HandleEnd
	(game_state_t * game, play_status_t play_status, color_t next_player);

//will get the appropriate window object, based on requested window.
Control * Gui_GetNextWindow(gui_window_t window);

//"constructing" functions for all windows
Control * Menu_MainMenu_Create();
Control * Menu_PlayerSelection_Create();

//special "draw" functions
void Draw_PieceBoard (Control * button, SDL_Surface * screen);
void Draw_NextPlayerButton (Control * button, SDL_Surface * screen);
void Draw_UserColorButton (Control * button, SDL_Surface * screen);
void Draw_DepthButton (Control * button, SDL_Surface * screen);

#endif /* SRC_GUI_H_ */
