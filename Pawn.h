#ifndef EX2_PAWN_H
#define EX2_PAWN_H

#include "Soldier.h"

/**
 * class pawn
 */
class Pawn : public Soldier
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
		bool checkMove(int posX, int posY, int destX, int destY) override ;
		/**
		 * increment turn counter
		 */
        void incrementTurn() override;

	private:
		int _turn = 0;

};

#endif //EX2_PAWN_H
