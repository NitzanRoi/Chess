#include <iostream>
#include "Board.h"

#define WHITE_PLAYER_NAME "Enter white player name:\n"
#define BLACK_PLAYER_NAME "Enter black player name:\n"
#define END_GAME " won!\n"
#define CHECK "\33[37;41mCheck!\33[0m\n"
#define ILLEGAL_MOVE "\33[37;41millegal move\33[0m\n"
#define WHITE_PLAYER "white"
#define BLACK_PLAYER "black"
#define ENTER_MOVE ": Please enter your move:\n"
#define MINI_CASTLING "o-o"
#define BIG_CASTLING "o-o-o"
#define KING_UNI "\u265A"

// convert ascii code of char to number
#define ASCII_CONVERT_NUMBER 48

// convert ascii code of capital latter to number
#define ASCII_CONVERT_CAPITAL_LETTER 65
#define CASTLING (-1)
#define MOVE_SIZE 4
#define GOOD_RETURN_VALUE 0

using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using std::cerr;

/**
 * saves player's names
 * @param whitePlayer white player
 * @param blackPlayer black player
 */
void getPlayersNames(string &whitePlayer, string &blackPlayer)
{
    cout << WHITE_PLAYER_NAME;
    getline(cin, whitePlayer);
    if(cin.bad())
    {
        return;
    }
    cout << BLACK_PLAYER_NAME;
    getline(cin, blackPlayer);
    if(cin.bad())
    {
        return;
    }
}

/**
 * saves player wanted coordinates to move
 * @param playerName his name
 * @param playerColor his color
 * @param move his coordinates to move
 * @param board the board
 * @param check bool value if the current state is check
 * @return bool value - legality of a move
 */
bool getUserCoordinate(string& playerName, string& playerColor, int *move, Board& board, bool check)
{
	string str;
	cout << playerName << ENTER_MOVE;
    getline(cin, str);
    if (cin.bad())
    {
        return false;
    }
    if ((str == MINI_CASTLING) || (str == BIG_CASTLING))
    {
        if (!board.castling(str, playerColor))
        {
            cout << ILLEGAL_MOVE;
            return false;
        }
		move[POS_X] = CASTLING;
        return true;
    }
    else
    {
		move[POS_X] = str[POS_X] - ASCII_CONVERT_CAPITAL_LETTER;
		move[POS_Y] = str[POS_Y] - ASCII_CONVERT_NUMBER - 1;
		move[DEST_X] = str[DEST_X] - ASCII_CONVERT_CAPITAL_LETTER;
		move[DEST_Y] = str[DEST_Y] - ASCII_CONVERT_NUMBER - 1;
    }
    for (int i = 0; i < MOVE_SIZE ; i++)
    {
        if (move[i] > BLACK_LINE || move[i] < WHITE_LINE)
        {
            cout << ILLEGAL_MOVE;
            return false;
        }
    }
    if(!board(move[POS_X], move[POS_Y]).hasSoldier())
    {
        cout << ILLEGAL_MOVE;
        return false;
    }
    if (check)
    {
        if (board(move[POS_X], move[POS_Y]).getThisSoldier()->getItsUnicode() != KING_UNI)
        {
            cout << ILLEGAL_MOVE;
            cout << CHECK;
            return false;
        }
    }
    return board.checkLegal(move, playerColor, board);
}

/**
 * prints the board
 * @param board the board
 */
void printBoard(Board& board)
{
    cout << board;
}

/**
 * runs the game
 * @param whitePlayer the white player name
 * @param blackPlayer the black player name
 */
void play(string& whitePlayer, string& blackPlayer)
{
    Board board;
    string playerColor = WHITE_PLAYER;
    int move[MOVE_SIZE];
    bool validMove;
    while (board.toContinue())
    {
        string enemyColour = playerColor == WHITE ? BLACK : WHITE;
        int userKingX = playerColor == WHITE ? board._kingWhiteX : board._kingBlackX;
        int userKingY = playerColor == WHITE ? board._kingWhiteY : board._kingBlackY;
        if (board.noPossibilities(userKingX, userKingY, enemyColour))
        {
            break;
        }
        printBoard(board);
        if (board.check())
        {
            cout << CHECK;
        }
        string tmpPlayer = playerColor == WHITE_PLAYER ? whitePlayer : blackPlayer;
        validMove = getUserCoordinate(tmpPlayer, playerColor, move, board, board.check());
        while (!validMove)
        {
            printBoard(board);
            validMove = getUserCoordinate(tmpPlayer, playerColor, move, board, board.check());
        }
		if (move[POS_X] != CASTLING)
		{
			if (!board.moveSoldier(move)) // check if the move reveals the king
			{
				cout << ILLEGAL_MOVE;
				continue;
			}
		}
        playerColor = playerColor == WHITE_PLAYER ? BLACK_PLAYER : WHITE_PLAYER;
    }
    printBoard(board);
    string winner = playerColor == WHITE_PLAYER ? blackPlayer : whitePlayer;
    cout << winner << END_GAME;
    board.checkMate();
}

/**
 * the main function
 * @return 0 if everything finished successfully
 */
int main()
{
    string whitePlayer, blackPlayer;
    getPlayersNames(whitePlayer, blackPlayer);
    play(whitePlayer, blackPlayer);
    return GOOD_RETURN_VALUE;
}
