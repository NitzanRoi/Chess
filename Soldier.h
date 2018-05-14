#ifndef EX2_SOLDIER_H
#define EX2_SOLDIER_H
#define BLACK "black"
#define WHITE "white"
#define NO_SOLDIER "no soldier"

#include "iostream"

using std::string;
using std::tuple;

/**
 * class soldier
 */
class Soldier
{
    public:
        /**
         * constructor
         */
        Soldier();
        /**
         * destructor
         */
        virtual ~Soldier();
        /**
         * @return its unicode
         */
        virtual string getItsUnicode() const = 0;
        /**
        * check from index perspective if the step given is legal
        * @param posX current position on x axis
        * @param posY current position on y axis
        * @param destX destination on x axis
        * @param destY destination on y axis
        * @return true if we can reach from our position to the destination, false otherwise
        */
        virtual bool checkMove(int posX, int posY, int destX, int destY) = 0;
        /**
         * @return turn counter
         */
        virtual int getTurn() const;
        /**
         * increments turn counter
         */
        virtual void incrementTurn();
        /**
         * @return leaping over boolean value
         */
        bool getLeap() const;
        /**
         * sets leaping over boolean value
         * @param isLeap the boolean to set to
         */
        void setLeap(bool isLeap);

    private:
        bool _leapingOver = true;
        int _curX;
        int _curY;
};

#endif //EX2_SOLDIER_H
