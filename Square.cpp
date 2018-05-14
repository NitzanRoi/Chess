#include "Square.h"

// square's colors
#define BLUE "blue"
#define GREEN "green"

#define BLUE_UNICODE "46m"
#define GREEN_UNICODE "42m"
#define WHITE_UNICODE "37;"
#define BLACK_UNICODE "30;"
#define START_UNICODE "\33["
#define END_UNICODE "\33[0m"
#define SPACE_UNICODE " "
#define NO_SOLDIER_UNICODE "0;"

#define BISHOP_UNICODE "\u265D"
#define KING_UNICODE "\u265A"
#define KNIGHT_UNICODE "\u265E"
#define PAWN_UNICODE "\u265F"
#define QUEEN_UNICODE "\u265B"
#define ROOK_UNICODE "\u265C"

using std::swap;

/**
 * constructor
 */
Square::Square() : _soldierColor(NO_SOLDIER), _hasSoldier(false), _soldier(nullptr)
{
}

/**
 * copy constructor
 * @param other the square to copy
 */
Square::Square(const Square& other)
{
	_soldierColor = other._soldierColor;
	_hasSoldier = other._hasSoldier;
	_squareColor = other._squareColor;
    _soldier = other._soldier;
}

/**
 * destructor
 */
Square::~Square() = default;

/**
 * friend swap function between 2 squares
 * @param dest the first
 * @param src the second
 */
void swap(Square &dest, Square &src)
{
    swap(dest._soldierColor, src._soldierColor);
    if (dest.hasSoldier())
    {
        delete dest._soldier;
        dest._soldier = nullptr;
    }
    if (src.hasSoldier())
    {
        dest._hasSoldier = true;
        src._hasSoldier = false;
        dest._soldier = src._soldier;
		src._soldier = nullptr;
    }
}

/**
 * operator = overloading
 * @param other the square to copy from
 * @return square object
 */
Square& Square::operator=(const Square &other)
{
    if (this != &other)
	{
		_soldierColor = other._soldierColor;
		_hasSoldier = other._hasSoldier;
		_squareColor = other._squareColor;
		_soldier = other._soldier;
	}
    return *this;
}

/**
 * move = operator overloading
 * @param other rvalue of square
 * @return square object
 */
Square& Square::operator=(Square && other) noexcept
{
    if (this != &other)
    {
        delete _soldier;
        swap(*this, other);
    }
    return *this;
}

/**
 * set square color
 * @param color the wanted color
 */
void Square::setSquareColor(const string& color)
{
    _squareColor = color;
}

/**
 * @return if this square has a soldier
 */
bool Square::hasSoldier() const
{
    return _hasSoldier;
}

/**
 * @return its soldier's color
 */
string Square::getSoldierColor() const
{
    return _soldierColor;
}

/**
 * @return its soldier
 */
Soldier* Square::getThisSoldier() const
{
    return _soldier;
}

/**
 * friend operator << overloading
 * @param os the stream
 * @param s the square to print
 * @return print the square
 */
ostream& operator << (ostream& os, const Square& s)
{
    string printStr = START_UNICODE;
    string soldierStr;
    if (s.hasSoldier())
    {
        if (s._soldierColor == BLACK)
        {
            printStr += BLACK_UNICODE;
        }
        else
        {
            printStr += WHITE_UNICODE;
        }
        soldierStr = s.getThisSoldier()->getItsUnicode();
	}
    else
    {
        printStr += NO_SOLDIER_UNICODE;
        soldierStr = SPACE_UNICODE;
    }
    if (s._squareColor == GREEN)
    {
        printStr += GREEN_UNICODE;
    }
    else
    {
        printStr += BLUE_UNICODE;
    }
    printStr += soldierStr + END_UNICODE;
    os << printStr;
    return os;
}

/**
 * set square soldier
 * @param soldier the soldier
 * @param color its color
 */
void Square::setSquareSoldier(Soldier *soldier, const string& color)
{
    _soldier = soldier;
    _soldierColor = color;
}

/**
 * changes its has-soldier flag
 */
void Square::changeHasSoldier()
{
    _hasSoldier = !_hasSoldier;
}

/**
 * @return its color
 */
string Square::getSquareColor() const
{
    return _squareColor;
}
