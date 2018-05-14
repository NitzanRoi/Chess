#include <cassert>
#include <tuple>
#include "Soldier.h"

#define EXIT_FAIL (-1)

using std::make_tuple;

/**
 * destructor
 */
Soldier::~Soldier() = default;

/**
 * @return leaping over boolean value
 */
bool Soldier::getLeap() const
{
    return _leapingOver;
}

/**
 * sets leaping over boolean value
 * @param isLeap the boolean to set to
 */
void Soldier::setLeap(bool isLeap)
{
    _leapingOver = isLeap;
}

/**
 * @return turn counter
 */
int Soldier::getTurn() const
{
    assert(false);
    return EXIT_FAIL;
}

/**
 * increments turn counter
 */
void Soldier::incrementTurn()
{
    assert(false);
}

/**
 * constructor
 */
Soldier::Soldier() = default;
