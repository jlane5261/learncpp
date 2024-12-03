// board.cpp
//
// File contains the definitions for a tic-tac-toe board 
// Author: Joshua Lane
// ---------------------------------------------------
#include<iostream>
#include "Board.hpp"

void Space::set_location(const int& location)
{
    m_location = BoardLocation(location);
}

void Space::update_state(const char& state)
{
    m_state = state;
}

char Space::get_state()
{
    return m_state;
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

void Board::update_space(const int& location, const char& state)
{
    switch (location)
    {
    case 1:
        m_topLeft.update_state(state);
    case 2:
        m_topCenter.update_state(state);
    case 3:
        m_topRight.update_state(state);
    case 4:
        m_middleLeft.update_state(state);
    case 5:
        m_middleCenter.update_state(state);
    case 6:
        m_middleRight.update_state(state);
    case 7:
        m_bottomLeft.update_state(state);
    case 8:
        m_bottomCenter.update_state(state);
    case 9:
        m_bottomRight.update_state(state);
    default:
        std::cout << "invalid location" << std::endl;
    }
}

bool Board::check_board()
{
    /*
    Space Locations
    _1_|_2_|_3_
    _4_|_5_|_6_
     7 | 8 | 9 
    */

    // Check Square 1 options
    if (m_topLeft.get_state() != ' ')
        // horizontal
        if(m_topLeft.get_state() == m_topCenter.get_state() && m_topLeft.get_state() == m_topRight.get_state())
        {
            return true;
        }
        // vertical
        else if (m_topLeft.get_state() == m_middleLeft.get_state() && m_topLeft.get_state() == m_bottomLeft.get_state())
        {
            return true;
        }
        // diagonal
        else if (m_topLeft.get_state() == m_middleCenter.get_state() && m_topLeft.get_state() == m_bottomRight.get_state());
        {
            return true;
        }

    // Check Square 5 options
    if (m_middleCenter.get_state() != ' ')
        // horizontal
        if(m_middleCenter.get_state() == m_middleLeft.get_state() && m_middleCenter.get_state() == m_middleRight.get_state())
        {
            return true;
        }
        // vertical
        else if (m_middleCenter.get_state() == m_topCenter.get_state() && m_middleCenter.get_state() == m_bottomCenter.get_state())
        {
            return true;
        }
        // diagonal
        else if (m_middleCenter.get_state() == m_topRight.get_state() && m_middleCenter.get_state() == m_bottomLeft.get_state())
        {
            return true;
        }
    
    // Check Square 9 options
    if (m_bottomRight.get_state() != ' ')
        // horizontal
        if (m_bottomRight.get_state() == m_bottomCenter.get_state() && m_bottomRight.get_state() == m_bottomLeft.get_state())
        {
            return true;
        }
        // vertical
        else if (m_bottomRight.get_state() == m_middleRight.get_state() && m_bottomRight.get_state() == m_topRight.get_state())
        {
            return true;
        }
    
    return false;
}

void Board::clear_board()
{
    m_topLeft.update_state(' ');
    m_topCenter.update_state(' ');
    m_topRight.update_state(' ');
    m_middleLeft.update_state(' ');
    m_middleCenter.update_state(' ');
    m_middleRight.update_state(' ');
    m_bottomLeft.update_state(' ');
    m_bottomCenter.update_state(' ');
    m_bottomRight.update_state(' ');
}