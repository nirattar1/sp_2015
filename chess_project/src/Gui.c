/*
 * Gui.c
 *
 *  Created on: Oct 11, 2015
 *      Author: nirattar
 */

#include "Game_Mgr.h"
#include "Gui.h"
#include "Gui_framework.h"
#include "Memory.h"


gui_window_t _NextWindow = GUI_WINDOW_MAIN_MENU; //start with main menu.
game_state_t * _CurrentGame = NULL; //a pointer to current game.
//TODO make enum
//0==none is selected.
//1==selected and display move.
//2==selected and illegal.
int _BoardPieceSelection = 0;
position_t _BoardPieceMoveSrc;

//TODO remove
void Handler_New()
{
	DEBUG_PRINT (("new\n"));
	_QuitCurrentWindow = 1;
	_NextWindow = GUI_WINDOW_PLAYER_SELECTION;
}

void Handler_Load()
{
	DEBUG_PRINT (("load\n"));
	_QuitCurrentWindow = 1;
	_NextWindow = GUI_WINDOW_SAVE_LOAD;

}

void Handler_Quit()
{
	DEBUG_PRINT (("quit\n"));
	_QuitCurrentWindow = 1;
	_QuitProgram = 1;

}

void Handler_PlayerVsCpu()
{
	DEBUG_PRINT (("player vs. cpu\n"));

	//configure game mode
	Settings_GameMode_Set(GAME_MODE_PLAYER_VS_CPU);

	_QuitCurrentWindow = 1;
	_NextWindow = GUI_WINDOW_GAME; //TODO pass in settings
}

void Handler_PlayerVsPlayer()
{
	DEBUG_PRINT (("player vs. player\n"));

	//configure game mode
	Settings_GameMode_Set(GAME_MODE_PLAYER_VS_PLAYER);

	//
	_QuitCurrentWindow = 1;
	_NextWindow = GUI_WINDOW_GAME; //TODO pass in settings
}

void Handler_Cancel()
{
	DEBUG_PRINT (("cancel\n"));
	_QuitCurrentWindow = 1;
	_NextWindow = GUI_WINDOW_MAIN_MENU;	//go back to main menu.

}

void Handler_SaveGame()
{
	//TODO implement
	DEBUG_PRINT (("save game\n"));
	//_QuitCurrentWindow = 1;
	//_NextWindow = GUI_WINDOW_MAIN_MENU;	//go back to main menu.

}

void Handler_BoardPieceClick(Control * control, SDL_Event * event)
{

	//avoid null ptr
	//TODO special check pos if have pointer
	if (!control)
	{
		DEBUG_PRINT(("Error: clicked a piece with no position\n"));
		return;
	}

	game_state_t * game = _CurrentGame;

	DEBUG_PRINT (("clicked position: <%c,%d>\n", control->pos.x, control->pos.y));

	//act based on previous selection
	if (_BoardPieceSelection==0)
	{
		//none is currently selected.

		//check if invalid piece

		//mark as selected
		_BoardPieceSelection = 1;
		_BoardPieceMoveSrc = control->pos;

		//get the moves of piece, highlight them.
		piece_t piece;
		piece.position = control->pos;
		piece.identity = GetPiece (control->pos, game);
		ListNode * moves = GetMovesForPiece(game, piece); //free later

		//TODO highlight moves

		ListFreeElements(moves, MoveFree);
	}

	else if (_BoardPieceSelection==1)
	{
		//a piece was previously selected.

		//construct a move, from previous selection to current selection.
		move_t selected_move;

		//TODO promotion window.
		char promotion_identity = 0;

		//get list of moves starting from source (previously selected).
		piece_t piece;
		piece.position = _BoardPieceMoveSrc;
		piece.identity = GetPiece (_BoardPieceMoveSrc, game);
		ListNode * moves = GetMovesForPiece(game, piece); //free later

		//find move inside moves list.
		//find move in allowed moves list, (if found, will update move in argument).
		int valid = FindMoveInList(moves, _BoardPieceMoveSrc, control->pos,
				promotion_identity, &selected_move);

		//free moves list
		ListFreeElements(moves, MoveFree);

		//return based on result.
		if (valid)
		{
			DEBUG_PRINT(("legal move\n"));
			//TODO do / return the move.

			//reset selection
			_BoardPieceSelection=0;
		}
		else
		{
			//move is not in list.
			DEBUG_PRINT(("illegal move\n"));
			_BoardPieceSelection=0;
		}




	}
	//_QuitCurrentWindow = 1;
	//_NextWindow = GUI_WINDOW_MAIN_MENU;	//go back to main menu.

}

//builds main menu
Control * Menu_MainMenu_Create()
{

	//window (has no rect).
	Control * w1 = WindowCreate("imgs/background.bmp", NULL);
	//handle error in creation of window.
	if (!w1)
	{
		return NULL;
	}

	//buttons under window
	//new game, load game, quit.

	//new game button
	SDL_Rect * button_NewGame_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_NewGame_rect->x = 310; button_NewGame_rect->y = 150;
	button_NewGame_rect->w = 20; button_NewGame_rect->h = 30;
	Control * button_NewGame = ButtonCreate("imgs/new_g.bmp", button_NewGame_rect, Handler_New);

	//load game button
	SDL_Rect * button_LoadGame_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_LoadGame_rect->x = 310; button_LoadGame_rect->y = 250;
	button_LoadGame_rect->w = 20; button_LoadGame_rect->h = 30;
	Control * button_LoadGame = ButtonCreate("imgs/load_g.bmp", button_LoadGame_rect, Handler_Load);

	//quit button
	SDL_Rect * button_Quit_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_Quit_rect->x = 310; button_Quit_rect->y = 350;
	button_Quit_rect->w = 20; button_Quit_rect->h = 30;
	Control * button_Quit = ButtonCreate("imgs/exit.bmp", button_Quit_rect, Handler_Quit);


	//link the objects to window
	ControlAddChild(w1, button_NewGame);
	ControlAddChild(w1, button_LoadGame);
	ControlAddChild(w1, button_Quit);

	return w1;
}

Control * Menu_PlayerSelection_Create()
{

	//window (has no rect).
	Control * window = WindowCreate("imgs/background.bmp", NULL);
	//handle error in creation of window.
	if (!window)
	{
		return NULL;
	}

	//buttons under window
	//player vs. cpu, player vs. player, cancel
	//TODO set board, next player.

	//player vs. cpu
	SDL_Rect * button_PlayerVsCpu_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_PlayerVsCpu_rect->x = 270; button_PlayerVsCpu_rect->y = 150;
	button_PlayerVsCpu_rect->w = 20; button_PlayerVsCpu_rect->h = 30;
	Control * button_PlayerVsCpu = ButtonCreate("imgs/Player_vs_Computer.bmp", button_PlayerVsCpu_rect, Handler_PlayerVsCpu);

	//player vs. player
	SDL_Rect * button_PlayerVsPlayer_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_PlayerVsPlayer_rect->x = 270; button_PlayerVsPlayer_rect->y = 250;
	button_PlayerVsPlayer_rect->w = 20; button_PlayerVsPlayer_rect->h = 30;
	Control * button_PlayerVsPlayer = ButtonCreate("imgs/player_vs_player.bmp", button_PlayerVsPlayer_rect, Handler_PlayerVsPlayer);

	//cancel
	SDL_Rect * button_Cancel_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_Cancel_rect->x = 20; button_Cancel_rect->y = 350;
	button_Cancel_rect->w = 20; button_Cancel_rect->h = 30;
	Control * button_Cancel = ButtonCreate("imgs/Cancel.bmp", button_Cancel_rect, Handler_Cancel);


	//link the objects to window
	ControlAddChild(window, button_PlayerVsCpu);
	ControlAddChild(window, button_PlayerVsPlayer);
	ControlAddChild(window, button_Cancel);

	return window;
}


//build picture filename based on identity and position
//updates filename by reference
static void BoardPieceFindPictureByIdentity(position_t pos, char identity, char * filename)
{

	//find color of square
	int i = pos.x - 'a';
	int j = pos.y;
	color_t square_color = ((i%2==0 && j%2==0)||(i%2!=0 &&j%2!=0)) ? COLOR_BLACK : COLOR_WHITE;
	char * strSquareColor = (square_color==COLOR_BLACK) ? "blck":"wht" ;

	if (identity==EMPTY)
	{
		char * format = "imgs/empty_%s.bmp";
		sprintf(filename, format, strSquareColor);
	}
	else
	{
		//color_identity_bgcolor
		char * format = "imgs/%s_%s_%s.bmp";

		//determine piece's color
		char * strPieceColor = (GetColor(identity)==COLOR_WHITE) ? "wht" : "blck";

		//determine piece identity
		char * strPieceIdentity = NULL;
		piece_t piece;
		piece.identity = identity;
		piece.position = pos;
		if (IsMan(piece))
		{
			strPieceIdentity = "pwn";
		}
		else if (IsBishop(piece))
		{
			strPieceIdentity = "bshp";
		}
		else if (IsKnight(piece))
		{
			strPieceIdentity = "nght";
		}
		else if (IsRook(piece))
		{
			strPieceIdentity = "rk";
		}
		else if (IsQueen(piece))
		{
			strPieceIdentity = "qn";
		}
		else if (IsKing(piece))
		{
			strPieceIdentity = "kng";
		}

		//build filename
		sprintf (filename, format, strPieceColor, strPieceIdentity, strSquareColor);

	}


}

//a function for drawing board piece.
void BoardPieceDraw (Control * button, SDL_Surface * screen)
{

	//get current game state, find identity inside position.
	game_state_t * game = _CurrentGame;
	//decide what is in the piece
	char identity = GetPiece (button->pos, game);

	//TODO pre-load images.
	//find the correct image based on the piece and position
	char filename[50];
	BoardPieceFindPictureByIdentity(button->pos, identity, filename);
	//TODO handle errors

	//load image
	//load the image (if exists) into ctl's surface
	bmp_load(filename, &(button->surface));


	//load image to
	//update clipping information.
	//draw button inside it's parent's boundaries.
	if (button->parent && button->parent->rect)
	{
		SDL_SetClipRect(screen, button->parent->rect);
	}

	/* Blit onto the screen surface */
	//note: width and height are ignored in dstrect!
	if(SDL_BlitSurface(button->surface, NULL, screen, button->rect) < 0)
	{
		fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());
	}
	//reset clip
	SDL_SetClipRect (screen, NULL);

	//SDL_UpdateRect(dest, 0, 0, src->w, src->h);
	//flip instead of update
	SDL_Flip(screen);

	/* Free the allocated BMP surface. */
	SDL_FreeSurface(button->surface);

	//the surface was freed, reset pointer.
	button->surface = NULL;
}



//builds board (each square is a control),
//and links it to panel .
static void BuildBoard(game_state_t * game, Control * panel_GameBoard)
{

	//build board.
	int x_off = 0;
	int y_off = 0;
	const int board_piece_width = 65;
	const int board_piece_height = 65;
	//create board squares, add them to board panel
	for (int j=BOARD_SIZE; j>0; j--)
	{

		//start from beginning of row
		x_off = 0;

		//iterate on columns
		for (int i=0; i<BOARD_SIZE; i++)
		{
			//create button with image
			SDL_Rect * button_BoardPiece_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
			button_BoardPiece_rect->x = x_off;
			button_BoardPiece_rect->y = y_off;

			//build position from loop
			position_t pos = Position ('a'+i, j);

			//real draw is later.
			color_t square_color = ((i%2==0 && j%2==0)||(i%2!=0 &&j%2!=0)) ? COLOR_BLACK : COLOR_WHITE;
			char * filename = (square_color==COLOR_BLACK) ? "imgs/empty_blck.bmp":"imgs/empty_wht.bmp" ;
			Control * button_BoardPiece = ButtonCreate( filename, button_BoardPiece_rect, Handler_Quit);

			//save position info on button.
			button_BoardPiece->pos = pos;

			//give draw and handle events handlers.
			button_BoardPiece->Draw = BoardPieceDraw;
			button_BoardPiece->HandleEvents = Handler_BoardPieceClick;

			//progress to next column
			x_off += board_piece_width;

			//link button to panel
			ControlAddChild(panel_GameBoard, button_BoardPiece);
		}

		//finished with row, progress to next row.
		y_off += board_piece_height;

	}
}


Control * Menu_GameWindow_Create()
{
	//2 panels:
	//* game options panel
	//* game board

	//window (has no rect).
	Control * window = WindowCreate("imgs/background.bmp", NULL);
	//handle error in creation of window.
	if (!window)
	{
		return NULL;
	}

	//game options panel
	SDL_Rect * panel_GameOptions_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	panel_GameOptions_rect->x = 600; panel_GameOptions_rect->y = 0;
	panel_GameOptions_rect->w = 0; panel_GameOptions_rect->h = 0;
	Control * panel_GameOptions = PanelCreate("imgs/background.bmp", panel_GameOptions_rect);

	//buttons inside game options.
	SDL_Rect * button_SaveGame_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	button_SaveGame_rect->x = 600; button_SaveGame_rect->y = 0;
	button_SaveGame_rect->w = 0; button_SaveGame_rect->h = 0;
	Control * button_SaveGame = ButtonCreate("imgs/Save_Game.bmp", button_SaveGame_rect, Handler_SaveGame);
	//TODO more buttons

	//game board panel
	SDL_Rect * panel_GameBoard_rect = (SDL_Rect *) mymalloc(sizeof(SDL_Rect));
	panel_GameBoard_rect->x = 0; panel_GameBoard_rect->y = 0;
	panel_GameBoard_rect->w = 0; panel_GameBoard_rect->h = 0;
	Control * panel_GameBoard = PanelCreate("imgs/background.bmp", panel_GameBoard_rect);

	//link panels to window
	ControlAddChild(window, panel_GameBoard);
	ControlAddChild(window, panel_GameOptions);
	//link buttons to game options panel
	ControlAddChild(panel_GameOptions, button_SaveGame);


	//get current game.
	game_state_t * game = _CurrentGame;
	if (!game)
	{
		DEBUG_PRINT(("Error: game window with no active."));
		return NULL;
	}

	//build a board based on game.
	BuildBoard(game, panel_GameBoard);
	return window;
}


Control * Gui_GetNextWindow(gui_window_t window)
{
	switch (window)
	{
		case GUI_WINDOW_MAIN_MENU:
			return Menu_MainMenu_Create();
			break;
		case GUI_WINDOW_PLAYER_SELECTION:
			return Menu_PlayerSelection_Create();
			break;
		case GUI_WINDOW_GAME:
			return Menu_GameWindow_Create();
			break;
	}

	//default
	return NULL;
}


void Gui_Main(game_state_t * game)
{

	if (!game)
	{
		exit(1);
	}
	//update global game
	_CurrentGame = game;

	//init SDL
	if (init_sdl() != 0)
	{
		exit (1);
	}


	//init screen
	//(screen is a global surface).
	//(will be freed by SDL_Quit).
	SDL_Surface * screen = init_screen(WINDOW_TITLE);

	//a loop that will switch between windows.
	//will maintain a reference to the active window.
	//upon window close, will load the next window.
	while (!_QuitProgram)
	{
		//create the upcoming window
		Control * window = Gui_GetNextWindow(_NextWindow);
		if (!window)
		{
			DEBUG_PRINT(("Error: program continues but no next window."));
		}

		//game window has different flow.
		if (_NextWindow==GUI_WINDOW_GAME)
		{
			Gui_Main_Game(game, window, screen);
		}
		else
		{
			//draw the objects to screen. (with DFS traverse)
			DFSTraverseDraw (window, screen);

			//handle events in loop, until exit.
			HandleEventsLoop(window);

			//loop was done (window exited).
			//clear it (will free all children objects)
			ControlFree((void *) window);
		}
	}

	//done with program, will go back to main.
}


//just a special main function for main
void Gui_Main_Game (game_state_t * game, Control * window, SDL_Surface * screen)
{
	//game window is ready.

	//TODO DoGame with adjustments.

	//update board based on game state.
	DFSTraverseDraw(window, screen);

	//handle events in loop, until exit.
	HandleEventsLoop(window);

	//loop was done (window exited).
	//clear it (will free all children objects)
	ControlFree((void *) window);
}


