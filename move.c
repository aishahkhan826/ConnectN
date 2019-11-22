
#include <stdlib.h>
#include <stdio.h>
#include "move.h"
#include "board.h"
#include "InputValidation.h"
#include "CursorTrakedWindow.h"
#include <ncurses.h>

Move getValidMove(struct Board_Struct* board, struct Board_Struct* playboard, struct Board_Struct* annboard, TurnType playerTurn, CursorTrackedWindow* boardwin, CursorTrackedWindow* playwin, FILE* fp, int pieces) {
    Move move;
    while (true) {
        mvwaddch(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol, "XO"[playerTurn]);
        wrefresh(playwin->cursesWin);
        CursorTrackedWindowMove(playwin, 0, playwin->cursorCol);
        wrefresh(playwin->cursesWin);
        char input = wgetch(playwin->cursesWin);
        if (input == 'a' || input == 'j') {
            printAllBoards(*playboard, *board, *annboard, fp, pieces, playerTurn);
            mvwaddch(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol, ' ');
            emptyboard(playboard);
            playwin->cursorCol -= 1;

            if (playwin->cursorCol < 0) {
                playwin->cursorCol = getNumCols(boardwin)-1;
            }
            mvwaddch(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol, "XO"[playerTurn]);
            wrefresh(playwin->cursesWin);
            playboard->theBoard[0][playwin->cursorCol] = "XO"[playerTurn];
            wmove(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol);

        }
        else if (input == 's' || input == 'k') {
            printAllBoards(*playboard, *board, *annboard, fp, pieces, playerTurn);
            wrefresh(playwin->cursesWin);
            mvwaddch(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol, ' ');
            emptyboard(playboard);
            playwin->cursorCol += 1;
            if (playwin->cursorCol > getNumCols(boardwin)-1) {
                playwin->cursorCol = 0 ;
            }
            mvwaddch(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol, "XO"[playerTurn]);
            wrefresh(playwin->cursesWin);
            playboard->theBoard[0][playwin->cursorCol] = "XO"[playerTurn];
            wmove(playwin->cursesWin, playwin->cursorRow, playwin->cursorCol);
        }
        else if (input == ' ' || input == '\n') {
            printAllBoards(*playboard, *board, *annboard, fp, pieces, playerTurn);
            move.row = playwin->cursorRow;
            move.col = playwin->cursorCol;
            move.marker = "XO"[playerTurn];
            emptyboard(playboard);
            playboard->theBoard[0][playwin->cursorCol] = "XO"[playerTurn];
            return move;

        }
        else{
            printAllBoards(*playboard, *board, *annboard, fp, pieces, playerTurn);
        }
        wrefresh(boardwin->cursesWin);
        wrefresh(playwin->cursesWin);
    }
}

bool isValidMove(Move move, struct Board_Struct* board, int numArgsRead, int numArgsNeeded) {
    return isValidFormat(numArgsRead, numArgsNeeded) &&
           isInRange(move.row, 0, board->numRows - 1) &&
           isInRange(move.col, 0, board->numCols - 1) &&
           board->theBoard[move.row][move.col] == board->blankChar;
}

const char* PlayerToString(TurnType player) {
    static const char p1[] = "Player1";
    static const char p2[] = "Player2";
    if (player == Player1) {
        return p1;
    } else {
        return p2;
    }

}
