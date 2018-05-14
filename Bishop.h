#ifndef EX2_BISHOP_H
#define EX2_BISHOP_H

#include "Soldier.h"

/**
 * 	class represent bishop on chess board
 */
class Bishop : public Soldier
{
	public:
		/**
		 * getter for unicode of bishop
		 * @return the unicode of the bishop
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

#endif //EX2_BISHOP_H
