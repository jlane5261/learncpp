// board.hpp
//
// File contains the interface for a tic-tac-toe board 
// Author: Joshua Lane
// ---------------------------------------------------

class Space
//A space can have a state of ' ', 'O', or 'X'
{
private:
    char m_state = ' ';
    int m_location;
public:
    void set_location(const int& location);
    void update_state(const char& state);
    char get_state();
};

enum BoardLocation{

/*
Space Locations
_1_|_2_|_3_
_4_|_5_|_6_
 7 | 8 | 9 
*/

    topLeft =       1,
    topCenter =     2,
    topRight =      3,
    middleLeft =    4,
    middleCenter =  5,
    middleRight =   6,
    bottomLeft =    7,
    bottomCenter =  8,
    bottomRight =   9
};

class Board
{
private:
    Space m_topLeft;
    Space m_topCenter;
    Space m_topRight;
    Space m_middleLeft;
    Space m_middleCenter;
    Space m_middleRight;
    Space m_bottomLeft;
    Space m_bottomCenter;
    Space m_bottomRight;

public:
    Board();
    //~Board();
    void update_space(const int& location, const char& state);
    bool check_board();
    void clear_board();
};