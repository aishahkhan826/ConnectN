#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "move.h"
#include "win.h"
#include "CursorTrakedWindow.h"
#include <stdlib.h>

int main(int argc, char*argv[]) {
    if(argc < 4){
        printf("Not enough arguments\n");
        return 0;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int pieces = atoi(argv[3]);
    FILE* fp = fopen(argv[4],"w");
    initscr();
    noecho();
    cbreak();
    refresh();
    CursorTrackedWindow playWindow = newCursorTrackedWindow(1, cols, 0,0);
    CursorTrackedWindow boardWindow = newCursorTrackedWindow(rows, cols, 1, 0);
    CursorTrackedWindow announcementWindow = newCursorTrackedWindow(1, 13, rows+1, 0);

    fillWindow(&boardWindow, '*');

    keypad(playWindow.cursesWin, true);
    wrefresh(announcementWindow.cursesWin);
    wrefresh(boardWindow.cursesWin);
    wrefresh(playWindow.cursesWin);


    Board playboard = makeBoard(1, cols, ' ');
    Board board = makeBoard(rows,cols,'*');
    Board annoucement = makeBoard(1, 14, ' ');
    TurnType playerTurn = Player2;

    playboard.theBoard[0][0] = 'X';

    while(!isGameOver(board, pieces, playerTurn)){
        //get a move from the user
        playerTurn = playerTurn == Player1 ? Player2 : Player1;

        Move move = getValidMove(&board, &playboard, &annoucement, playerTurn, &boardWindow, &playWindow, fp, pieces);
        //place their move on the board

        placeMove(move, &board, &playboard, &annoucement, &boardWindow, &playWindow, fp, playerTurn, pieces);
        wrefresh(playWindow.cursesWin);

    }


    playboard.theBoard[0][playWindow.cursorCol] = "XO"[playerTurn];
    fprintBoard(playboard, fp);
    fprintBoard(board, fp);
    declareWinner(board, pieces, playerTurn, fp);
    delwin(boardWindow.cursesWin);
    delwin(playWindow.cursesWin);
    delwin(announcementWindow.cursesWin);
    endwin();
    printBoard(board);


    cleanUpBoard(&board);
    cleanUpBoard(&playboard);
    cleanUpBoard(&annoucement);
    fclose(fp);
    return 0;

}
