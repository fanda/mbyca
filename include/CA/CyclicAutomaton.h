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
 * File:    CyclicAutomaton.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Generic automaton for cyclic totalistic family
 */

#ifndef __CYCLICAUTOMATON_H
#define __CYCLICAUTOMATON_H

#include "CellularAutomaton2D.h"

typedef int Threshold; // threshold as parameter of automaton

/*!
  Cyclic cellular automaton specification
    -> C states of cell
    -> extended Moore (or extended von Neumann) neighborhood
    -> minimal count of the next color cells in neighborhood for next color
*/
class CyclicAutomaton : public CellularAutomaton2D
{
    Q_OBJECT

    Threshold threshold;

    bool extended, mooreNeighborhood;

public:
    //! Rule definition of cyclic cellular automaton
    /*!
      Generic rule (parameters can be changed) of cyclic automaton.
      Counts neighbors of state which is next state of current cell and
      if its count is greater or equal than threshold, then advances cell
      into next state.
    */
    virtual void rule()
    {
      Dimension y, x; // lattice index counters
      Dimension xE, xE2, xW, xW2, yN, yN2, yS, yS2; // directional offsets
      
      swap(); // swaps current and previous lattices

      for (y = 0; y < rows(); y++) {

        yN = y-1; yN2 = y-2;
        yS = y+1; yS2 = y+2;

        if      (y == 0) { yN  += rows();  yN2 += rows(); }
        else if (y == 1) { yN2 += rows();  }
        else if (y == rows()-1) { yS  = 0; yS2 = 1;       }
        else if (y == rows()-2) { yS2 = 0; }

        for (x = 0; x < columns(); x++) {

            xW = x-1; xW2 = x-2;
            xE = x+1; xE2 = x+2;

            if      (x == 0) { xW  += columns();  xW2 += columns(); }
            else if (x == 1) { xW2 += columns();  }
            else if (x == columns()-1) { xE  = 0; xE2 = 1;          }
            else if (x == columns()-2) { xE2 = 0; }


            int livingNeighbors = 0;
            // update state if there is threshold count of next state
            State state, color = lattice[prev](x, y).state();

            state = color++;
            if (color == lattice[prev].cellStates()) color = 0;

            // von neumann's neighborhood
            if (lattice[prev](x,  yN).state() == color) livingNeighbors++;
            if (lattice[prev](xW, y ).state() == color) livingNeighbors++;
            if (lattice[prev](xE, y ).state() == color) livingNeighbors++;
            if (lattice[prev](x,  yS).state() == color) livingNeighbors++;

            // range of neighborhood > 1
            if (extended) {
                if (lattice[prev](x,   yN2).state() == color) livingNeighbors++;
                if (lattice[prev](xW2, y  ).state() == color) livingNeighbors++;
                if (lattice[prev](xE2, y  ).state() == color) livingNeighbors++;
                if (lattice[prev](x,   yS2).state() == color) livingNeighbors++;
            }
            // moore's neighborhood
            if (mooreNeighborhood)
            {
                if (lattice[prev](xW, yN).state() == color) livingNeighbors++;
                if (lattice[prev](xE, yN).state() == color) livingNeighbors++;
                if (lattice[prev](xW, yS).state() == color) livingNeighbors++;
                if (lattice[prev](xE, yS).state() == color) livingNeighbors++;

                if (extended) {
                    if (lattice[prev](xW2, yN2).state() == color) livingNeighbors++;
                    if (lattice[prev](xW,  yN2).state() == color) livingNeighbors++;
                    if (lattice[prev](xE,  yN2).state() == color) livingNeighbors++;
                    if (lattice[prev](xE2, yN2).state() == color) livingNeighbors++;
                    if (lattice[prev](xW2, yN ).state() == color) livingNeighbors++;
                    if (lattice[prev](xE2, yN ).state() == color) livingNeighbors++;
                    if (lattice[prev](xW2, yS ).state() == color) livingNeighbors++;
                    if (lattice[prev](xE2, yS ).state() == color) livingNeighbors++;
                    if (lattice[prev](xW2, yS2).state() == color) livingNeighbors++;
                    if (lattice[prev](xW,  yS2).state() == color) livingNeighbors++;
                    if (lattice[prev](xE,  yS2).state() == color) livingNeighbors++;
                    if (lattice[prev](xE2, yS2).state() == color) livingNeighbors++;
                }
            }
            // check for cell state change
            if ( livingNeighbors >= threshold )
              lattice[curr](x, y).nextState();
            else
              lattice[curr](x, y).setState(state);

        }
      }      
    }

    //! Constructor
    CyclicAutomaton(const Dimension& c, const Dimension& r,
                    StateCount sc=3, Threshold tr=1, bool nr=false, bool mn=true)
        : CellularAutomaton2D(r, c), threshold(tr), extended(nr), mooreNeighborhood(mn) {
        setStatesCount(sc);
    }

    //! Copy constructor
    CyclicAutomaton(const CyclicAutomaton& C) 
        : CellularAutomaton2D(C), threshold(C.getThreshold()) {
        setStatesCount(C.statesCount());
    }

    //! Destructor
    ~CyclicAutomaton() {}

    //! Changes rule of cyclic automaton
    void changeRule(StateCount sc, Threshold tr, bool nr=false, bool mn=false)
    {
        setStatesCount(sc);
        threshold = tr;
        extended = nr;
        mooreNeighborhood = mn;
    }

    Threshold getThreshold()    const {
        return threshold;
    }

    bool isExtendedNeighborhood()  const {
        return extended;
    }

    bool isMooreNeighborhood()  const {
        return mooreNeighborhood;
    }


public slots:
    //! Randomize implementation with probability parameter
    virtual void randomize(int p = 0)
    {
        Dimension i, j; // row, col index counters
        StateCount states = statesCount();

        // randomly assign life to each of the cells
        // based upon the probability defined by invP.
        for (i=0; i< rows(); i++)
          for (j=0; j< columns(); j++)
            lattice[curr](i, j).setState(random()%states);
        emit firstBang(&lattice[curr]);
    }

};

#endif // __CYCLICAUTOMATON_H
