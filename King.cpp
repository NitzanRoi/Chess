#include "King.h"
#include "cmath"

#define KING_UNICODE "\u265A"
#define MAX_STEP 1

using std::abs;

/**
 * @return its unicode
 */
string King::getItsUnicode() const
{
    return KING_UNICODE;
}

/**
 * check from index perspective if the step given is legal
 * @param posX current position on x axis
 * @param posY current position on y axis
 * @param destX destination on x axis
 * @param destY destination on y axis
 * @return true if we can reach from our position to the destination, false otherwise
 */
bool King::checkMove(int posX, int posY, int destX, int destY)
{
    return ((abs(posX - destX) == MAX_STEP) || (abs(posY - destY) == MAX_STEP) ) &&
                                                      ((abs(posX - destX) <= MAX_STEP) &&
                                                      (abs(posY - destY) <= MAX_STEP));
}

/**
 * increment turn counter
 */
void King::incrementTurn()
{
    ++_turn;
}

/**
 * @return turn counter
 */
int King::getTurn() const
{
    return _turn;
}
