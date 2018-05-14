#ifndef EX2_QUEEN_H
#define EX2_QUEEN_H

#include "Soldier.h"

/**
 * class queen
 */
class Queen : public Soldier
{
	public:
        /**
         * @return its unicode
         */
		string getItsUnicode() const override;

		/**
		* check from index perspective if the step given is legal
		* @param posX current position on x axis
		* @param posY current position on y axis
		* @param destX destination on x axis
		* @param destY destination on y axis
		* @return true if we can reach from our position to the destination, false otherwise
		*/
		bool checkMove(int posX, int posY, int destX, int destY) override;
};

#endif //EX2_QUEEN_H
