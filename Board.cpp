#include <tuple>
#include "Board.h"

#define BISHOP_UNICODE "\u265D"
#define KING_UNICODE "\u265A"
#define KNIGHT_UNICODE "\u265E"
#define PAWN_UNICODE "\u265F"
#define QUEEN_UNICODE "\u265B"
#define ROOK_UNICODE "\u265C"

// for castling
#define MINI_CAST_START_TREAT 4
#define MINI_CAST_END_TREAT 6
#define MINI_CAST_START_EMPTY 4
#define MINI_CAST_END_EMPTY 6
#define BIG_CAST_START_TREAT 2
#define BIG_CAST_END_TREAT 4
#define BIG_CAST_START_EMPTY 0
#define BIG_CAST_END_EMPTY 3
#define MINI_CAST_ROOK_DEST 5
#define MINI_CAST_KING_DEST 6
#define BIG_CAST_KING_DEST 3
#define BIG_CAST_ROOK_DEST 2

using std::cout;
using std::endl;
using std::cerr;
using std::abs;

/**
 * check for legality of a move
 * @param move move coordinates
 * @param playerColor player's color
 * @param board board
 * @return boolean value if the move is legal
 */
bool Board::checkLegal(int *move, string& playerColor, Board& board)
{
	if (!board(move[POS_X], move[POS_Y]).hasSoldier() ||
        board(move[POS_X], move[POS_Y]).getSoldierColor() != playerColor ||
        board(move[DEST_X], move[DEST_Y]).getSoldierColor() == playerColor)
	{
		cout << ILLEGAL_MOVE;
		return false;
	}
	if (board(move[POS_X], move[POS_Y]).getThisSoldier()->getItsUnicode() == PAWN_UNI)
	{
		if (!board.pawnIsOnTheBoard(move[POS_X], move[POS_Y], move[DEST_X], move[DEST_Y], playerColor))
		{
			cout << ILLEGAL_MOVE;
			return false;
		}
	}
	else if (!board(move[POS_X], move[POS_Y]).getThisSoldier()->
			 checkMove(move[POS_X], move[POS_Y], move[DEST_X], move[DEST_Y]))
	{
		cout << ILLEGAL_MOVE;
		return false;
	}
	if (!board(move[POS_X], move[POS_Y]).getThisSoldier()->getLeap())
	{
		if (!board.leapingCheck(move[POS_X], move[POS_Y], move[DEST_X], move[DEST_Y]))
		{
			cout << ILLEGAL_MOVE;
			return false;
		}
	}
	return true;
}

/**
 * overload the parenthesis operator
 * @param coorX the x coordinate of the place we want represent as char
 * @param coorY the y coordinate of ths place we want represent as int
 * @return the square we want to get
 */
Square& Board::operator()(int coorX, int coorY)
{
    return _board[coorX][coorY];
}

/**
 * check if the pawn move is legal
 * @param posX source x
 * @param posY source y
 * @param destX destination x
 * @param destY destination y
 * @param color its color
 * @return bool value as above mentioned
 */
bool Board::pawnIsOnTheBoard(int posX, int posY, int destX, int destY, const string& color) const
{
	if (color == WHITE)
	{
		if (abs(posX - destX) == MAX_PAWN_STEP && destY - posY == MAX_PAWN_STEP && _board[destX][destY].hasSoldier())
		{
			return true;
		}
		return _board[posX][posY].getThisSoldier()->checkMove(posX, posY, destX, destY) &&
               !_board[destX][destY].hasSoldier();
	}
	if (abs(posX - destX) == MAX_PAWN_STEP && posY - destY == MAX_PAWN_STEP && _board[destX][destY].hasSoldier())
	{
		return true;
	}
	return _board[posX][posY].getThisSoldier()->checkMove(posX, destY, destX, posY) &&
		   !_board[destX][destY].hasSoldier();
}

/**
* for the soldiers that can not leap, check if the board is "clean"
* in their way
* @param posX current position on axis x
* @param posY current position on axis y
* @param destX destination on axis x
* @param destY destination on axis y
* @return true if we can do the road without leap, false otherwise
*/
bool Board::leapingCheck(int posX, int posY, int destX, int destY) const
{
	int dirX = destX - posX;
	int dirY = destY - posY;
	int moveX = dirX > ON_THE_SPOT ? RIGHT : (dirX == ON_THE_SPOT ?  ON_THE_SPOT : LEFT);
	int moveY = dirY > ON_THE_SPOT ? UP : (dirY == ON_THE_SPOT ?  ON_THE_SPOT : DOWN);
    if(dirX == 1 || dirY == 1)// LOGIC, NOT MAGIC
    {
        return true;
    }
	if(abs(dirX) == abs(dirY))
	{
		for (int i = 1; i < abs(dirX) ; i++) // LOGIC, NOT MAGIC
		{
			if (_board[posX + moveX][posY + moveY].hasSoldier())
			{
				return false;
			}
			posX += moveX;
			posY += moveY;
		}
	}
	if (abs(dirX) > abs(dirY))
    {
		for (int i = 1 ; i < abs(dirX) ; i++)// LOGIC, NOT MAGIC
        {
			if (_board[posX + moveX][posY].hasSoldier())
            {
				return false;
			}
			posX += moveX;
		}
	}
	else if (abs(dirX) < abs(dirY))
    {
		for (int i = 1; i < abs(dirY) ; i++)// LOGIC, NOT MAGIC
        {
			if (_board[posX][posY + moveY].hasSoldier())
            {
				return false;
			}
			posY += moveY;
		}
	}
	return true;
}

/**
 * constructor, initialize the game board and the soldiers
 */
Board::Board() : _kingWhiteX(4), _kingWhiteY(0), _kingBlackX(4), _kingBlackY(7), _mate(false),
                 _end(false)
{
	_board = new Square*[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		_board[i] = new Square[SIZE];
	}
    _continue = true;
    _check = false;
	string tmpColor = GREEN;
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE ; j++)
		{
            _board[j][i].setSquareColor(tmpColor);
			tmpColor = tmpColor == BLUE ? GREEN : BLUE;
		}
        tmpColor = tmpColor == BLUE ? GREEN : BLUE;
	}
	for(int i = 0; i < SIZE ; i++)
	{
		Soldier* gringo = new Pawn;
		_board[i][WHITE_PAWNS].setSquareSoldier(gringo, WHITE);
        _board[i][WHITE_PAWNS].changeHasSoldier();
		Soldier* mualem = new Pawn;
		_board[i][BLACK_PAWNS].setSquareSoldier(mualem, BLACK);
        _board[i][BLACK_PAWNS].changeHasSoldier();
	}
	_initSoldiers(WHITE);
	_initSoldiers(BLACK);
}

/**
 * destructor, deletes all memory allocations
 */
Board::~Board()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (_end && _board[i][j].hasSoldier())
			{
				delete _board[i][j].getThisSoldier();
			}
		}
		delete[] _board[i];
	}
	delete[] _board;
}

/**
 * operator = overloading
 * @param other the board to copy from
 * @return board object
 */
Board& Board::operator=(const Board &other)
{
	if (this != &other)
	{
		for (int i = 0; i < SIZE; i++)
		{
			delete[] _board[i];
		}
		delete[] _board;

		_board = new Square*[SIZE];
		for (int i = 0 ; i < SIZE ; i++)
		{
			_board[i] = new Square[SIZE];
		}
		for (int i = 0; i < SIZE; ++i)
		{
			for (int j = 0; j < SIZE ; j++)
			{
				_board[j][i] = other._board[j][i];
			}
		}
	}
	return *this;
}

/**
 * copy constructor
 * @param other the board to copy
 */
Board::Board(const Board& other)
{
	_board = new Square*[SIZE];
	for (int i = 0 ; i < SIZE ; i++)
	{
		_board[i] = new Square[SIZE];
	}
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE ; j++)
		{
			_board[j][i] = other._board[j][i];
		}
	}
	_continue = other._continue;
	_check = other._check;
	_kingWhiteX = other._kingWhiteX;
	_kingWhiteY = other._kingWhiteY;
	_kingBlackX = other._kingBlackX;
	_kingBlackY = other._kingBlackY;
    _mate = other._mate;
    _end = other._end;
}

/**
 * help method for the construction process
 * @param color which color the soldier we want to add to _board
 */
void Board::_initSoldiers(string color)
{
	int line = color == WHITE ? WHITE_LINE : BLACK_LINE;
	Soldier* rook1 = new Rook;
    rook1->setLeap(false);
	Soldier* knight1 = new Knight;
	Soldier* bishop1 = new Bishop;
    bishop1->setLeap(false);
	_board[FIRST_ROOK][line].setSquareSoldier(rook1, color);
	_board[FIRST_KNIGHT][line].setSquareSoldier(knight1, color);
	_board[FIRST_BISHOP][line].setSquareSoldier(bishop1, color);
	Soldier* king = new King;
	Soldier* queen = new Queen;
    queen->setLeap(false);
	_board[QUEEN_SPOT][line].setSquareSoldier(queen, color);
	_board[KING_SPOT][line].setSquareSoldier(king, color);
	Soldier* rook2 = new Rook;
    rook2->setLeap(false);
	Soldier* knight2 = new Knight;
	Soldier* bishop2 = new Bishop;
    bishop2->setLeap(false);
	_board[SEC_BISHOP][line].setSquareSoldier(bishop2, color);
	_board[SEC_KNIGHT][line].setSquareSoldier(knight2, color);
	_board[SEC_ROOK][line].setSquareSoldier(rook2, color);
	for (int i = 0; i < SIZE; ++i)
	{
		_board[i][line].changeHasSoldier();
	}
}

/**
* prints the lines with the letters and spaces
* @param firstLine bool value corresponding to the line
*/
void Board::_printHelper(const bool firstLine) const
{
    string letters[] = {
                        HORIZONTAL_SPOT_ONE, HORIZONTAL_SPOT_TWO, HORIZONTAL_SPOT_THREE,
                        HORIZONTAL_SPOT_FOUR, HORIZONTAL_SPOT_FIVE, HORIZONTAL_SPOT_SIX,
                        HORIZONTAL_SPOT_SEVEN, HORIZONTAL_SPOT_EIGHT
                       };
    if (!firstLine)
    {
        cout << endl;
    }
    cout << SPACE << SPACE;
    for (const auto &letter : letters)
    {
        cout << letter;
    }
    cout << endl;
    cout << endl;
}

/**
 * friend overloading << operator (print the board)
 * @param os the stream
 * @param b the board
 * @return prints the board
 */
ostream& operator << (ostream& os, const Board& b)
{
    b._printHelper(true);
	for (int i = END_LINE; i >= START_LINE; --i)
	{
		os << (i + 1) << SPACE;
		for (int j = 0; j < SIZE; ++j)
		{
            os << b._board[j][i];
		}
		os << SPACE << (i + 1) << NEW_LINE;
	}
	b._printHelper(false);
	return os;
}

/**
 * @return bool value if the game should continue or ended
 */
bool Board::toContinue() const
{
    return _continue;
}

/**
 * @return if the current state is check
 */
bool Board::check() const
{
    return _check;
}

/** moves the soldiers
 * move[0-1] : src x and y; move[2-3]: dest x and y
 * @param move move coordinates
 * @return bool value if the move legal and done
 */
bool Board::moveSoldier(const int *move)
{
	Board tmpBoard(*this);
    string currentUserColor = _board[move[POS_X]][move[POS_Y]].getSoldierColor();
    string enemyColour = currentUserColor == WHITE ? BLACK : WHITE;
    int userKingX = currentUserColor == WHITE ? _kingWhiteX : _kingBlackX;
    int userKingY = currentUserColor == WHITE ? _kingWhiteY : _kingBlackY;
    if (_board[move[POS_X]][move[POS_Y]].getThisSoldier()->getItsUnicode() == KING_UNI)
    {
        if (_enemyThreat(move[DEST_X], move[DEST_Y], enemyColour))
        {
            return false;
        }
        _check = false;
    }
	swap(_board[move[DEST_X]][move[DEST_Y]], _board[move[POS_X]][move[POS_Y]]);
    if (_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == KING_UNI)
    {
        userKingX = move[DEST_X];
        userKingY = move[DEST_Y];
    }
    if (_enemyThreat(userKingX, userKingY, enemyColour)) // if the king being under a threat - we need to cancel the move
    {
        *this = tmpBoard;
        return false;
    }
	if ((_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == KING_UNI) ||
		(_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == ROOK_UNI) ||
		(_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == PAWN_UNI))
	{
		_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->incrementTurn();
	}
	bool pawn = _board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == PAWN_UNI;
	if (pawn && (move[DEST_Y] == START_LINE || move[DEST_Y] == END_LINE))
	{
		Square square = _board[move[DEST_X]][move[DEST_Y]];
		_pawnBecomeAQueen(square, _board[move[DEST_X]][move[DEST_Y]].getSoldierColor());
	}
	if (_board[move[DEST_X]][move[DEST_Y]].getThisSoldier()->getItsUnicode() == KING_UNI)
	{
		string color = _board[move[DEST_X]][move[DEST_Y]].getSoldierColor();
		_kingWhiteX = color == WHITE ? move[DEST_X] : _kingWhiteX;
		_kingWhiteY = color == WHITE ? move[DEST_Y] : _kingWhiteY;
		_kingBlackX = color == BLACK ? move[DEST_X] : _kingBlackX;
		_kingBlackY = color == BLACK ? move[DEST_Y] : _kingBlackY;
	}
    userKingX = currentUserColor == WHITE ? _kingBlackX : _kingWhiteX;
    userKingY = currentUserColor == WHITE ? _kingBlackY : _kingWhiteY;
    if (_enemyThreat(userKingX, userKingY, currentUserColor)) // detect check
    {
        _check = true;
    }
    return true;
}

/**
 * helper function
 * @param i coordinate i
 * @param j coordinate j
 * @param coorX coordinate x
 * @param coorY coordinate y
 * @return bool value
 */
bool Board::_threatHelper(int i, int j, int coorX, int coorY) const
{
    if (!_board[j][i].getThisSoldier()->getLeap())
    {
        if (leapingCheck(j, i, coorX, coorY))
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    return false;
}

/**
 * given a coordinate and color and return if this coordinate is under a threat
 * @param coorX coordinate x
 * @param coorY coordinate y
 * @param enemyColor the color to check if threaten
 * @return bool value if there is a threat, true - threat, false otherwise
 */
bool Board::_enemyThreat(int coorX, int coorY, const string& enemyColor) const
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            auto soldier = _board[j][i].getThisSoldier();
            if (!soldier)
            {
                continue;
            }
            if (_board[j][i].getSoldierColor() != enemyColor)
            {
                continue;
            }
            if (soldier->getItsUnicode() == PAWN_UNI)
            {
                if (pawnIsOnTheBoard(j, i, coorX, coorY, enemyColor))
                {
                    return true;
                }
            }
            else if (_board[j][i].getThisSoldier()->checkMove(j, i, coorX, coorY))
            {
                if (_threatHelper(i, j, coorX, coorY))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * assigen func for castling check
 * @param playerColor color of the player
 * @param enemy enemy color to be update
 * @param line line number to be update
 * @param rook rook place to be update
 * @param rookDest rook destination to be update
 * @param kingDest king destination to be update
 * @param emptyS our sign to decide
 */
void Board::_assignForCast(string &playerColor, string &enemy, int &line, int &rook, int &rookDest, int &kingDest,
						   int emptyS)
{
	if (playerColor == WHITE_PLAY)
	{
		line = WHITE_LINE;
		enemy = BLACK;
	}
	else // black player turn
	{
		enemy = WHITE;
		line = BLACK_LINE;
	}
	emptyS == FIRST_ROOK ? (rook = FIRST_ROOK, rookDest = BIG_CAST_ROOK_DEST, kingDest = BIG_CAST_KING_DEST) :
	(rook = SEC_ROOK, rookDest = MINI_CAST_ROOK_DEST, kingDest = MINI_CAST_KING_DEST);
}

/**
 * check if we can make the wanted castaling
 * @param playerColor color of the player who want to castling
 * @param treatS start of the place we want to check if treat
 * @param treatE end of the place we want to check if treat
 * @param emptyS start of the place we want to check if empty
 * @param emptyE end  of the place we want to check if empty
 * @return true if we can make the castling, false else
 */
bool Board::_castlingCheck(string& playerColor, int treatS, int treatE, int emptyS, int emptyE)
{
	string enemy;
	int line = 0;
	int rook = 0;
	int rookDestination = 0;
	int kingDestination = 0;
	_assignForCast(playerColor, enemy, line, rook, rookDestination, kingDestination, emptyS);

	if ((_board[KING_SPOT][line].getThisSoldier()->getItsUnicode() != KING_UNI) ||
		(_board[rook][line].getThisSoldier()->getItsUnicode() != ROOK_UNI))
	{
		return false;
	}
	if ((_board[KING_SPOT][line].getThisSoldier()->getTurn() != 0) ||
		(_board[rook][line].getThisSoldier()->getTurn() != 0))
	{
		return false;
	}
	if (!leapingCheck(emptyS, line, emptyE + 1, line))
	{
		return false;
	}
	for (int i = treatS; i <= treatE; i++)
	{
		if (_enemyThreat(i, line, enemy))
		{
			return false;
		}
	}
	int tmpMove1[] = {KING_SPOT, line, kingDestination, line};
	moveSoldier(tmpMove1);
	int tmpMove2[] = {rook, line, rookDestination, line};
	moveSoldier(tmpMove2);
	return true;
}

/**
 * check legal castling
 * @param type mini or big castling
 * @param playerColor player color
 * @return bool value if legal
 */
bool Board::_checkLegalCastling(string &type, string& playerColor)
{
	if (type == MINI_CASTL)
	{
		if (!_castlingCheck(playerColor, MINI_CAST_START_TREAT, MINI_CAST_END_TREAT,
			MINI_CAST_START_EMPTY, MINI_CAST_END_EMPTY))
		{
			return false;
		}
	}
	else // big castling
	{
		if (!_castlingCheck(playerColor, BIG_CAST_START_TREAT, BIG_CAST_END_TREAT,
			BIG_CAST_START_EMPTY, BIG_CAST_END_EMPTY))
		{
			return false;
		}
	}
	return true;
}

/**
 * function for doing castling
 * @param type big or mini castling
 * @param playerColor player color
 * @return boolean value if the castling done
 */
bool Board::castling(string &type, string& playerColor)
{
    return _checkLegalCastling(type, playerColor);
}

/**
 * makes promotion for the pawn
 * @param square its current square
 * @param color its color
 */
void Board::_pawnBecomeAQueen(Square &square, const string& color)
{
    delete(square.getThisSoldier());
    Queen* queen = new Queen;
    square.setSquareSoldier(queen, color);
}

/**
 * changes _end to true
 */
void Board::checkMate()
{
    _end = true;
}

/**
 * check for mate
 * @param x king x
 * @param y king y
 * @param enemyColour enemy color
 * @return true - no possibilities for the king = mate!
 */
bool Board::noPossibilities(int x, int y, string& enemyColour) const
{
    if (!_check)
    {
        return false;
    } // ALL THE NUMBERS ARE PART OF THE LOGIC
    int coors[][SIZE] = {
                            {x - 1, y}, {x, y + 1}, {x + 1, y + 1}, {x + 1, y}, {x - 1, y + 1},
                            {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1}
                        };
    int squaresCtr = 0;
    for (auto &coor : coors)
    {
        if (_legalSquare(coor[0], coor[1]))
        {
            if (!_board[coor[0]][coor[1]].hasSoldier())
            {
                if (_enemyThreat(coor[0], coor[1], enemyColour))
                {
                    ++squaresCtr;
                }
            }
            else
            {
                ++squaresCtr;
            }
        }
        else
        {
            ++squaresCtr;
        }
    }
    return squaresCtr == SIZE;
}

/**
 * check if coordinate is legal - in the board
 * @param x x coordinate
 * @param y y coordinate
 * @return true - if coordinate is in the board
 */
bool Board::_legalSquare(int x, int y) const
{
    return ((x >= WHITE_LINE && x <= BLACK_LINE) && (y >= WHITE_LINE && y <= BLACK_LINE));
}