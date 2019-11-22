

#ifndef NCursesConnectN_BOARD_H
#define NCursesConnectN_BOARD_H
#include "move.h"



typedef struct Board_Struct{
    char** theBoard;
    int numRows;
    int numCols;
    char blankChar;
}Board;



Board makeBoard(int numRows, int numCols, char blankChar);
void printBoard(Board board);
void cleanUpBoard(Board* board);
void emptyboard(Board * board);
void printAllBoards(Board playboard, Board board, Board annBoard, FILE* fp, int pieces, TurnType playerTurn);
void fprintBoard(Board board, FILE * fp);

void placeMove(Move move, Board* board, Board* playboard, Board* annboard, CursorTrackedWindow* boardwin, CursorTrackedWindow* playwin, FILE* fp, TurnType playerTurn, int pieces);
#endif //NCursesConnectN_BOARD_H
