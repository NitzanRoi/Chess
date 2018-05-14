#include "Bishop.h"
#include <cmath>

#define BISHOP_UNICODE "\u265D"

using std::abs;

/**
 * getter for unicode of bishop
 * @return the unicode of the bishop
 */
string Bishop::getItsUnicode() const
{
    return BISHOP_UNICODE;
}


/**
 * check from index perspective if the given step is legal
 * @param posX current position on x axis
 * @param posY current position on y axis
 * @param destX destination on x axis
 * @param destY destination on y axis
 * @return true if we can reach from our position to the destination, false otherwise
 */
bool Bishop::checkMove(int posX, int posY, int destX, int destY)
{
    return (abs(destX - posX)) == (abs(destY - posY));
}
