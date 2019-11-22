

#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "CursorTrakedWindow.h"
#include "win.h"
Board makeBoard(int numRows, int numCols, char blankChar) {
    Board board;

    board.theBoard = (char**)malloc(numRows * sizeof(char*));
    for (int i = 0; i < numRows; ++i) {
        board.theBoard[i] = (char*)malloc(numCols * sizeof(char));
        for (int j = 0; j < numCols; ++j) {
            board.theBoard[i][j] = blankChar;
        }
    }

    board.numRows = numRows;
    board.numCols = numCols;
    board.blankChar = blankChar;
    return board;
}

void printBoard(Board board) {

    printf("  ");
    for (int i = 0; i < board.numCols; ++i) {
        printf("%d ", i);
    }
    printf("\n");

    for (int row = 0; row < board.numRows; ++row) {
        printf("%d ", row); //print row header
        for (int col = 0; col < board.numCols; ++col) {
            printf("%c ", board.theBoard[row][col]);
        }
        printf("\n");
    }
}

void fprintBoard(Board board, FILE * fp){

    for (int row = 0; row < board.numRows; ++row) {
        for (int col = 0; col < board.numCols; ++col) {
            fprintf(fp, "%c ", board.theBoard[row][col]);
        }
        fprintf(fp, "\n");
    }

}
void printAllBoards(Board playboard, Board board, Board annBoard, FILE* fp, int pieces, TurnType playerTurn){
    if (!isGameOver(board, pieces, playerTurn)) {
        fprintBoard(playboard, fp);
        fprintBoard(board, fp);
        fprintBoard(annBoard, fp);
    }
    else if (isGameOver(board, pieces, playerTurn)){
        fprintBoard(playboard, fp);
        fprintBoard(board, fp);
        declareWinner(board, pieces, playerTurn, fp);\
    }
}

void cleanUpBoard(Board* board) {

    for (int row = 0; row < board->numRows; ++row) {
        free(board->theBoard[row]);
    }
    free(board->theBoard);
    board->theBoard = NULL;
    board->numRows = 0;
    board->numCols = 0;
}
void emptyboard(Board * board){
    for (int row = 0; row < board->numRows; ++row) {
        for (int col = 0; col < board->numCols; ++col) {
            board->theBoard[row][col] = ' ';
        }
    }
}

void placeMove(Move move, Board* board, Board* playboard, Board* annboard, CursorTrackedWindow* boardwin, CursorTrackedWindow* playwin, FILE* fp, TurnType playerTurn, int pieces) {
    for (int i = board->numRows-1; i >= 0; --i) {
        if (board->theBoard[i][move.col] == '*') {
            board->theBoard[i][move.col] = move.marker;
            emptyboard(playboard);
            playerTurn = playerTurn == Player1 ? Player2 : Player1;
            playboard->theBoard[0][playwin->cursorCol] = "XO"[playerTurn];
            mvwaddch(boardwin->cursesWin, i, move.col, move.marker);
            wrefresh(boardwin->cursesWin);
            wrefresh(playwin->cursesWin);
            break;
        }
    }
}
