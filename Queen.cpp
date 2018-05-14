#include "Queen.h"
#include "cmath"

#define QUEEN_UNICODE "\u265B"

using std::abs;

/**
 * @return its unicode
 */
string Queen::getItsUnicode() const
{
    return QUEEN_UNICODE;
}

/**
 * check from index perspective if the step given is legal
 * @param posX current position on x axis
 * @param posY current position on y axis
 * @param destX destination on x axis
 * @param destY destination on y axis
 * @return true if we can reach from our position to the destination, false otherwise
 */
bool Queen::checkMove(int posX, int posY, int destX, int destY)
{
    return (abs(destX - posX) == abs(destY - posY)) ||
           (abs(posX - destX) > 0) != (abs(posY - destY) > 0);

}
