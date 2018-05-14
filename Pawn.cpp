#include "Pawn.h"

#define PAWN_UNICODE "\u265F"
#define REGULAR_STEP 1
#define FIRST_STEP 2

/**
 * @return its unicode
 */
string Pawn::getItsUnicode() const
{
    return PAWN_UNICODE;
}

/**
 * check from index perspective if the step given is legal
 * @param posX current position on x axis
 * @param posY current position on y axis
 * @param destX destination on x axis
 * @param destY destination on y axis
 * @return true if we can reach from our position to the destination, false otherwise
 */
bool Pawn::checkMove(int posX, int posY, int destX, int destY)
{
    if(posX != destX)
    {
        return false;
    }
    if(!_turn)
    {
        return destY - posY == REGULAR_STEP || destY - posY == FIRST_STEP;
    }
    return destY - posY == REGULAR_STEP;
}

/**
 * increment turn counter
 */
void Pawn::incrementTurn()
{
    ++_turn;
}


