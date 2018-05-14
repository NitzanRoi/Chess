#include "Rook.h"
#include "cmath"

#define ROOK_UNICODE "\u265C"

using std::abs;

/**
 * @return its unicode
 */
string Rook::getItsUnicode() const
{
    return ROOK_UNICODE;
}

/**
 * check from index perspective if the step given is legal
 * @param posX current position on x axis
 * @param posY current position on y axis
 * @param destX destination on x axis
 * @param destY destination on y axis
 * @return true if we can reach from our position to the destination, false otherwise
 */
bool Rook::checkMove(int posX, int posY, int destX, int destY)
{
    return (abs(posX - destX) > 0) != (abs(posY - destY) > 0);
}

/**
 * increments turn counter
 */
void Rook::incrementTurn()
{
    ++_turn;
}

/**
 *
 * @return turn counter
 */
int Rook::getTurn() const
{
    return _turn;
}


