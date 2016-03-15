/******************************************************************************
Copyright (c) 2011, Pavel Novotny
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the organization nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Pavel Novotny BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/
/*
 * File:    Cell.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Contains class definition for the cellular automata cell
 *          having a binary _state.
 *          Matthew Meyer's ideas
 */

#ifndef __CELL_H
#define __CELL_H

#include <iostream>

// states of the cell
typedef unsigned short StateCount;
typedef unsigned short State;


/*!
  Cell of the cellular automaton
*/
class Cell
{

    // default values
    enum { DEFAULT_STATES = 2 }; // default states count for CommonCell
    enum { DEFAULT_STATE  = 0 }; // default state for CommonCell

public:
    //! Default constructor
    Cell() : states(DEFAULT_STATES), _state(DEFAULT_STATE) {}
    //! Constructor with states count parametr, state is default
    Cell(StateCount sc) : states(sc), _state(DEFAULT_STATE) {}
    //! Copy contructor
    Cell(const Cell& C) : states(C.states), _state(C._state) {}

    //! Operator = for Cell object
    Cell& operator=(const Cell& C)
    {
        if (this != &C)
            _state = C._state;
        return *this;
    }

    //! Operator = for direct state input
    Cell& operator=(const State& s)
    {
        if (s < states)_state = s;
        return *this;
    }

    void setStateCount(const StateCount& s) {
        states = s;
    }

    StateCount stateCount() const {
        return states;
    }

    State state() const {
        return _state;
    }

    void setState(const State& s) {
        if (s < states)_state = s;
    }

    //! Advance cell into next state
    void nextState() {
        if (++_state >= states) _state = 0;
    }

protected:
    StateCount states; // count of states

private:
    State      _state; // "state" of the cell

};

#endif // __CELL_H
