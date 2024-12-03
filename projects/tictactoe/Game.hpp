// Game.hpp
//
// File defines the interface for tic-tac-toe Game 
// Author: Joshua Lane
// ----------------------------------------------

#include<iostream>

class Game
{
private:
    bool m_gameDecided;


public:
    Game(/* args */);
    ~Game();
    void play();
    void selectdifficulty();
    void writeboard();
    void clearboard();
    void printboard();
};
