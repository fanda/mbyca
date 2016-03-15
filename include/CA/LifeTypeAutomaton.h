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
 *  File:    LifeTypeAutomaton.h
 *  Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 *  Project: Music Creation Using Cellular Automata
 *  About:   Generic automaton for Life rules family
 */

#ifndef __LIFETYPEAUTOMATON_H
#define __LIFETYPEAUTOMATON_H

#include <QSet>

#include "CellularAutomaton2D.h"

/*!
  Life type specification
    -> Binary state cells
    -> Moore neighborhood
    -> some alive neighbors necessary for a cell to survive
    -> some alive neighbors necessary for a cell to be born
*/
class LifeTypeAutomaton : public CellularAutomaton2D
{
    Q_OBJECT

    typedef QSet<int> LifeTypeRuleSpec;

    enum State { DEAD, ALIVE };

    LifeTypeRuleSpec toSurvive;
    LifeTypeRuleSpec toBeBorn;

public:
    //! Rule definition of the game of Life
    /*!
      Generic rule (parameters can be changed) of Life game automaton.
      Counts living neighbors and according to parameters "toBeBorn" and
      "toSurvive" sets the state of the cell to alive or dead.
    */
    virtual void rule()
    {
      Dimension y, x; // lattice index counters
      Dimension ySouth, yNorth, xEast, xWest; // directional offsets
      
      swap(); // swaps current and previous lattices
      for (y = 0; y < rows(); y++) {

        yNorth = y==0        ? rows()-1 : y-1;
        ySouth = y==rows()-1 ? 0        : y+1;

        for (x = 0; x < columns(); x++) {

            xWest = x==0           ? columns()-1 : x-1;
            xEast = x==columns()-1 ? 0           : x+1;

            // neighbors counting
            int livingNeighbors = 0;
            if (lattice[prev](xWest, yNorth).state()) livingNeighbors++;
            if (lattice[prev](x,     yNorth).state()) livingNeighbors++;
            if (lattice[prev](xEast, yNorth).state()) livingNeighbors++;
            if (lattice[prev](xWest, y     ).state()) livingNeighbors++;
            if (lattice[prev](xEast, y     ).state()) livingNeighbors++;
            if (lattice[prev](xWest, ySouth).state()) livingNeighbors++;
            if (lattice[prev](x,     ySouth).state()) livingNeighbors++;
            if (lattice[prev](xEast, ySouth).state()) livingNeighbors++;

            switch(lattice[prev](x, y).state()) {
                case DEAD:
                            if (toBeBorn.contains(livingNeighbors)) {
                                lattice[curr](x, y).setState(ALIVE);
                            } else {
                                lattice[curr](x, y).setState(DEAD);
                            }
                            break;

                case ALIVE:
                            if (toSurvive.contains(livingNeighbors)) {
                                lattice[curr](x, y).setState(ALIVE);
                            } else {
                                lattice[curr](x, y).setState(DEAD);
                            }
                            break;
                        }
        }
      }
    }


public:

    //! Constructor
    LifeTypeAutomaton(const Dimension& c, const Dimension& r)
      : CellularAutomaton2D(r, c)
    {   toSurvive<<2<<3; toBeBorn<<3; /* Life as default */   }

    //! Constructor
    LifeTypeAutomaton(const Dimension& c, const Dimension& r,
                      LifeTypeRuleSpec to_survive, LifeTypeRuleSpec to_be_born)
      : CellularAutomaton2D(r, c), toSurvive(to_survive), toBeBorn(to_be_born)
    { }

    //! Copy constructor
    LifeTypeAutomaton(const LifeTypeAutomaton& C) 
      : CellularAutomaton2D(C), toSurvive(C.getToSurvive()), toBeBorn(C.getToBeBorn())
    { }

    //! Destructor
    ~LifeTypeAutomaton() {}

    LifeTypeRuleSpec getToSurvive() const {
        return toSurvive;
    }
    LifeTypeRuleSpec getToBeBorn()  const {
        return toBeBorn;
    }

    //! Changes rule of cyclic automaton
    void changeRule(LifeTypeRuleSpec to_survive, LifeTypeRuleSpec to_be_born)
    {
        toSurvive.clear(); toBeBorn.clear();
        toSurvive.unite(to_survive); toBeBorn.unite(to_be_born);
    }

    //! This automaton doesn't change states count
    virtual void setStatesCount(const StateCount& s) {}

    //! Count live cells
    int CellCount() const 
    {
        int sum = 0;
        Dimension i, j;
        for (i = 0; i < rows(); i++)
          for (j = 0; j < columns(); j++)
            if (lattice[curr](i, j).state())
              ++sum;
        return sum;
    }

public slots:
    //! Randomize implementation with inverted probability parameter
    virtual void randomize(int iprob = 10)
    {
      Dimension i, j; // row, col index counters      
      // randomly assign life to each of the cells
      // based upon the probability defined by invP.
      for (i = 0; i < rows(); i++)
        for (j = 0; j < columns(); j++)
          if (random() % iprob == 0)
            lattice[curr](i, j).setState(ALIVE);
      emit firstBang(&lattice[curr]);
    }
};

#endif // __LIFETYPEAUTOMATON_H
