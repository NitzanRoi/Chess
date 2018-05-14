#ifndef EX2_SQUARE_H
#define EX2_SQUARE_H

#include "iostream"
#include "Soldier.h"

#define BLACK "black"
#define WHITE "white"
#define NO_SOLDIER "no soldier"

using std::string;
using std::ostream;

/**
 * class square
 */
class Square
{
    public:
		/**
		 * constructor
		 */
        Square();
        /**
         * copy constructor
         * @param other the square to copy
         */
        Square(const Square &other);
        /**
         * destructor
         */
        ~Square();
        /**
         * friend swap function between 2 squares
         * @param dest the first
         * @param src the second
         */
        friend void swap(Square& dest, Square& src);
        /**
         * operator = overloading
         * @param other the square to copy from
         * @return square object
         */
        Square& operator=(const Square& other);
        /**
         * move = operator overloading
         * @param other rvalue of square
         * @return square object
         */
        Square& operator=(Square && other) noexcept;
        /**
         * set square color
         * @param color the wanted color
         */
	    void setSquareColor(const string& color);
        /**
         * set square soldier
         * @param soldier the soldier
         * @param color its color
         */
		void setSquareSoldier(Soldier* soldier, const string& color);
        /**
         * @return its soldier
         */
        Soldier* getThisSoldier() const;
        /**
         * @return if this square has a soldier
         */
        bool hasSoldier() const;
        /**
         * friend operator << overloading
         * @param os the stream
         * @param s the square to print
         * @return print the square
         */
		friend ostream& operator << (ostream& os, const Square& s);
		/**
		 * changes its has-soldier flag
		 */
        void changeHasSoldier();
		/**
		 * @return its soldier's color
		 */
        string getSoldierColor() const;
		/**
		 * @return its color
		 */
        string getSquareColor() const;

    private:
		string _soldierColor;
		bool _hasSoldier;
        string _squareColor;
        Soldier* _soldier;
};

#endif //EX2_SQUARE_H
