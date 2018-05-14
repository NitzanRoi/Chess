#include "Knight.h"
#include "cmath"

#define KNIGHT_UNICODE "\u265E"

#define LONG_STEP 2
#define SHORT_STEP 1

using std::abs;

/**
 * @return its unicode
 */
string Knight::getItsUnicode() const
{
    return KNIGHT_UNICODE;
}

/**
* check from index perspective if the step given is legal
* @param posX current position on x axis
* @param posY current position on y axis
* @param destX destination on x axis
* @param destY destination on y axis
* @return true if we can reach from our position to the destination, false otherwise
*/
bool Knight::checkMove(int posX, int posY, int destX, int destY)
{
    return ((abs(posX - destX) == LONG_STEP) && (abs(posY - destY) == SHORT_STEP)) ||
           ((abs(posX - destX) == SHORT_STEP) && (abs(posY - destY) == LONG_STEP));
}
