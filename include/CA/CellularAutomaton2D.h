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
 * File:    CellularAutomaton2D.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Cellular automata "abstract" class
 *          Matthew Meyer's ideas
 */

#ifndef __CELLULARAUTOMATON2D_H
#define __CELLULARAUTOMATON2D_H

#include <cstdlib>

#include "Lattice2D.h"

#include <QObject>
#include <QSettings>

const int DEFAULT_BACKSPASE_STEPS = 50;// default steps back

/*!
  Parent class of all 2D cellular automata
*/
class CellularAutomaton2D : public QObject
{
    Q_OBJECT

    // lattice indexes - current and previous
    enum LatticeIndex {
        FST_LATTICE, SEC_LATTICE,
        LATTICES // total number of lattices for the simulation (=2)
    };

signals:
    //! Sends current lattice
    void bang(Lattice2D * curr_lattice);
    //! Sends lattice after cretation, clear or randomizing
    void firstBang(Lattice2D * curr_lattice);

public slots:    
    //! Sets default state to all cells
    void clear()
    {
        Dimension i, j;
        for (i = 0; i < rows(); i++)
            for (j = 0; j < columns(); j++) {
                lattice[curr](i, j) = 0;
                lattice[prev](i, j) = 0;
            }
        emit firstBang(&lattice[curr]); // send lattice
    }

    //! Gets "value'th" state of cellular automaton after saved lattice
    void backspase(int value)
    {
        if (steps > value) { // come back
            iters -= steps - value;
        }
        else { // come forward
            iters += value - steps;
        }
        steps = value;
        lattice[curr] = backspaseLattice;
        for (int i = 0; i < value; i++)
            rule();       
        emit firstBang(&lattice[curr]);
    }

public:
    //! Default constructor
    CellularAutomaton2D(const Dimension& r, const Dimension& c)
        : iters(0), curr(FST_LATTICE), prev(SEC_LATTICE), steps(0)
    {
        lattice = new Lattice2D[LATTICES];
        for (int j = 0; j < LATTICES; j++)
            lattice[j].setDimensions(r, c);
        backspaseLattice = lattice[curr];
        QSettings settings;
        backspaseSteps = settings.value("history", DEFAULT_BACKSPASE_STEPS).toInt();
    }


    //! Copy constructor
    CellularAutomaton2D(const CellularAutomaton2D& C)
        : QObject(0), iters(C.iters),
          curr(FST_LATTICE), prev(SEC_LATTICE), steps(0)
    {
        lattice = new Lattice2D[LATTICES];
        for (int j = 0; j < LATTICES; j++)
            lattice[j] = C.lattice[j];
        backspaseLattice = lattice[curr];
        QSettings settings;
        backspaseSteps = settings.value("history", DEFAULT_BACKSPASE_STEPS).toInt();
    }


    //! Destructor
    ~CellularAutomaton2D() {
        delete[] lattice;
    }


    //! Rule definition (virtual function)
    virtual void rule()   {}

    //! Randomizes lattice
    virtual void randomize(int p = 0) {
        emit firstBang(&lattice[curr]);
    }

    //! Sets number of states for cells in lattice
    virtual void setStatesCount(const StateCount& s)
    {
        lattice[curr].setCellStatesCount(s);
        lattice[prev].setCellStatesCount(s);
    }


    //! Performs one iteration of the cellular automaton
    void iterate()
    {
        if (++iters > backspaseSteps || iters == 1)
            backspaseLattice = lattice[curr];
        if (steps < backspaseSteps) steps++;
        rule();
        emit bang(&lattice[curr]);
    }


    //! Returns how many iterations have been done
    unsigned long iterations() const {
        return iters;
    }

    Dimension rows() const {
        return lattice[curr].rows();
    }

    Dimension columns()   const {
        return lattice[curr].columns();
    }

    StateCount statesCount() const {
        return lattice[curr].cellStates();
    }

    Lattice2D& currentLattice() const {
        return lattice[curr];
    }        

    //! Sets new current lattice
    void setLattice(Lattice2D * l)
    {
        lattice[curr] = *l;
        emit bang(&lattice[curr]);
    }

    //!
    void setBackspaseLattice()
    {
        backspaseLattice = lattice[curr];
    }

    //! Counts cells of given state
    int cellCount(State state) const
    {
        Dimension i, j;
        int sum = 0;
        for (i=0; i<rows(); i++)
            for (j=0; j<columns(); j++)
                if (lattice[curr](i, j).state() == state)
                    ++sum;
        return sum;
    }

protected:
    unsigned long iters; // for history

    LatticeIndex  curr, // current iteration lattice index
                  prev; // previous iteration lattice index

    Lattice2D * lattice; // will be array of two lattices

    Lattice2D backspaseLattice;

    int steps, backspaseSteps;


    inline void swap()
    {
        LatticeIndex temp = curr;
        curr = prev;
        prev = temp;
    }

};

#endif // __CELLULARAUTOMATON2D_H
