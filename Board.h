#ifndef EX2_BOARD_H
#define EX2_BOARD_H

#include "Square.h"
#include <ostream>
#include <array>
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "cmath"

#define SIZE 8

// square's colors
#define BLUE "blue"
#define GREEN "green"

// line numbers on the board in which only pawns of the given color are
#define WHITE_PAWNS 1
#define BLACK_PAWNS 6

// spot variables for the construct step - ALL OF THEM USED IN INIT SOLDIERS
#define FIRST_ROOK 0
#define FIRST_KNIGHT 1
#define FIRST_BISHOP 2
#define QUEEN_SPOT 3
#define KING_SPOT 4
#define SEC_ROOK 7
#define SEC_KNIGHT 6
#define SEC_BISHOP 5
#define WHITE_LINE 0
#define BLACK_LINE 7

// some string constants
#define SPACE " "
#define NEW_LINE "\n"
#define KING_UNI "\u265A"
#define ROOK_UNI "\u265C"
#define PAWN_UNI "\u265F"
#define MINI_CASTL "o-o"
#define WHITE_PLAY "white"
#define ILLEGAL_MOVE "\33[37;41millegal move\33[0m\n"

// spot variables for move pointer.
#define POS_X 0
#define POS_Y 1
#define DEST_X 2
#define DEST_Y 3

// spot variables, using to check if pawn reach end of board
#define END_LINE 7
#define START_LINE 0
#define MAX_PAWN_STEP 1

// direction variables
#define RIGHT 1
#define LEFT (-1)
#define UP 1
#define DOWN (-1)
#define ON_THE_SPOT 0

#define HORIZONTAL_SPOT_ONE "A"
#define HORIZONTAL_SPOT_TWO "B"
#define HORIZONTAL_SPOT_THREE "C"
#define HORIZONTAL_SPOT_FOUR "D"
#define HORIZONTAL_SPOT_FIVE "E"
#define HORIZONTAL_SPOT_SIX "F"
#define HORIZONTAL_SPOT_SEVEN "G"
#define HORIZONTAL_SPOT_EIGHT "H"

using std::ostream;
using std::string;
using std::array;

/**
 * class board
 */
class Board
{
	public:
		/**
		 * constructor, initialize the game board and the soldiers
		 */
		Board();
		/**
		 * destructor, deletes all memory allocations
		 */
		~Board();
		/**
		 * operator = overloading
		 * @param other the board to copy from
		 * @return board object
		 */
		Board& operator=(const Board &other);
		/**
		 * copy constructor
		 * @param other the board to copy
		 */
		Board(const Board& other);
		/**
		 * overload the parenthesis operator
		 * @param coorX the x coordinate of the place we want represent as char
		 * @param coorY the y coordinate of ths place we want represent as int
		 * @return the square we want to get
		 */
		Square& operator()(int coorX, int coorY);
        /**
        * @return bool value if the game should continue or ended
        */
		bool toContinue() const;
        /**
         * changes _end to true
         */
        void checkMate();
        /**
         * friend overloading << operator (print the board)
         * @param os the stream
         * @param b the board
         * @return prints the board
         */
		friend ostream& operator << (ostream& os, const Board& b);
        /**
         * @return if the current state is check
         */
        bool check() const;
        /**
        * for the soldiers that can not leap, check if the board is "clean"
        * in their way
        * @param posX current position on axis x
        * @param posY current position on axis y
        * @param destX destination on axis x
        * @param destY destination on axis y
        * @return true if we can do the road without leap, false otherwise
        */
        bool leapingCheck(int posX, int posY, int destX, int destY) const;
        /**
         * check if the pawn move is legal
         * @param posX source x
         * @param posY source y
         * @param destX destination x
         * @param destY destination y
         * @param color its color
         * @param board the board
         * @return bool value as above mentioned
         */
		bool pawnIsOnTheBoard(int posX, int posY, int destX, int destY, const string& color) const;
        /** moves the soldiers
         * move[0-1] : src x and y; move[2-3]: dest x and y
         * @param move move coordinates
         * @return bool value if the move legal and done
         */
        bool moveSoldier(const int *move);
        /**
         * function for doing castling
         * @param type big or mini castling
         * @param playerColor player color
         * @return boolean value if the castling done
         */
        bool castling(string& type, string& playerColor);
        /**
         * check for legality of a move
         * @param move move coordinates
         * @param playerColor player's color
         * @param board board
         * @return boolean value if the move is legal
         */
		bool checkLegal(int *move, string& playerColor, Board& board);
        /**
         * check for mate
         * @param x king x
         * @param y king y
         * @param enemyColour enemy color
         * @return true - no possibilities for the king = mate!
         */
        bool noPossibilities(int x, int y, string& enemyColour) const;
        int _kingWhiteX, _kingWhiteY, _kingBlackX, _kingBlackY;

    private:
        Square **_board;
        bool _continue;
		bool _check;
        bool _mate;
        bool _end;

		/**
		 * help method for the construction process
		 * @param color which color the soldier we want to add to _board
		 */
		void _initSoldiers(string color);
        /**
        * prints the lines with the letters and spaces
        * @param firstLine bool value corresponding to the line
        */
		void _printHelper(bool firstLine) const;
        /**
         * check legal castling
         * @param type mini or big castling
         * @param playerColor player color
         * @return bool value if legal
         */
        bool _checkLegalCastling(string &type, string &playerColor);
        /**
         * given a coordinate and color and return if this coordinate is under a threat
         * @param coorX coordinate x
         * @param coorY coordinate y
         * @param enemyColor the color to check if threaten
         * @return bool value if there is a threat, true - threat, false otherwise
         */
        bool _enemyThreat(int coorX, int coorY, const string &enemyColor) const;
		/**
		 * check if we can make the wanted castling
		 * @param playerColor color of the player who want to castling
		 * @param treatS start of the place we want to check if treat
		 * @param treatE end of the place we want to check if treat
		 * @param emptyS start of the place we want to check if empty
		 * @param emptyE end  of the place we want to check if empty
		 * @return true if we can make the castling, false else
		 */
		bool _castlingCheck(string& playerColor, int treatS, int treatE, int emptyS, int emptyE);
        /**
         * makes promotion for the pawn
         * @param square its current square
         * @param color its color
         */
        void _pawnBecomeAQueen(Square &square, const string& color);
        /**
		 * assign func for castling check
		 * @param playerColor color of the player
		 * @param enemy enemy color to be update
		 * @param line line number to be update
		 * @param rook rook place to be update
		 * @param rookDest rook destination to be update
		 * @param kingDest king destination to be update
		 * @param emptyS our sign to decide
		 */
		void _assignForCast(string &playerColor, string &enemy, int &line, int &rook, int &rookDest, int &kingDest,
                            int emptyS);
        /**
         * check if coordinate is legal - in the board
         * @param x x coordinate
         * @param y y coordinate
         * @return true - if coordinate is in the board
         */
        bool _legalSquare(int x, int y) const;
        /**
         * helper function
         * @param i coordinate i
         * @param j coordinate j
         * @param coorX coordinate x
         * @param coorY coordinate y
         * @return bool value
         */
        bool _threatHelper(int i, int j, int coorX, int coorY) const;
};

#endif //EX2_BOARD_H
