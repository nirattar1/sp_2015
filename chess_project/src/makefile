all: chessprog 

CFLAGS=-std=c99 -pedantic-errors -Wall -g -lm 
XML_CFLAGS=`xml2-config --cflags` 
SDL_CFLAGS=`sdl-config --cflags`
LIBS=`xml2-config --libs` `sdl-config --libs` -lm

O_FILES=Game_Mgr.o Game.o ListNode.o Memory.o Minimax.o Console_ui.o Files.o Gui_framework.o Gui.o

clean:
	-rm chessprog $(O_FILES)

chessprog: $(O_FILES)
	gcc $(CFLAGS) -o $@ $^ $(LIBS)

Game_Mgr.o: Game_Mgr.h Game_Mgr.c
	gcc -c $(CFLAGS) $*.c $(SDL_CFLAGS)

Game.o: Game.h Game.c
	gcc -c $(CFLAGS) $*.c
	
ListNode.o: ListNode.h ListNode.c
	gcc -c $(CFLAGS) $*.c

Memory.o: Memory.h Memory.c
	gcc -c $(CFLAGS) $*.c
	
Minimax.o: Minimax.h Minimax.c
	gcc -c $(CFLAGS) $*.c
	
Console_ui.o: Console_ui.h Console_ui.c
	gcc -c $(CFLAGS) $*.c $(XML_CFLAGS)

Files.o: Files.h Files.c
	gcc -c $(CFLAGS) $*.c $(XML_CFLAGS)

Gui_framework.o: Gui_framework.h Gui_framework.c
	gcc -c $(CFLAGS) $*.c $(SDL_CFLAGS)

Gui.o: Gui.h Gui.c
	gcc -c $(CFLAGS) $*.c $(SDL_CFLAGS) $(XML_CFLAGS)

