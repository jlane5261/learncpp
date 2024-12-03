// board.cpp
//
// File contains the definitions for a tic-tac-toe board 
// Author: Joshua Lane
// ---------------------------------------------------
#include "Board.hpp"

void Space::set_location(const int& location)
{
    m_location = BoardLocation(location);
}

void Space::update_state(char& state)
{
    m_state = state;
}

Board::Board()
{
    m_topLeft.set_location(BoardLocation::topLeft);
    m_topCenter.set_location(BoardLocation::topCenter);
    m_topRight.set_location(BoardLocation::topRight);
    m_middleLeft.set_location(BoardLocation::middleLeft);
    m_middleCenter.set_location(BoardLocation::middleCenter);
    m_middleRight.set_location(BoardLocation::middleRight);
    m_bottomLeft.set_location(BoardLocation::bottomLeft);
    m_bottomRight.set_location(BoardLocation::bottomRight);
}