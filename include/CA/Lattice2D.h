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
 * File:    Lattice2D.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   2D lattice template of "cells"
 *          Matthew Meyer's ideas
 */

#ifndef __LATTICE2D_H
#define __LATTICE2D_H

#include "Cell.h"

typedef int Dimension; // dimension type

/*!
  2D Lattice of cells for cellular automaton
*/
class Lattice2D
{

public:
    //! Default constructor
    Lattice2D() : _rows(0), _cols(0), lattice(NULL) {}
    //! Constructor for dimension arguments
    Lattice2D(const Dimension& r, const Dimension& c) : _rows(r), _cols(c) {
        createLattice();
    }

    //! Copy constructor
    Lattice2D(const Lattice2D& L) : _rows(L._rows), _cols(L._cols)
    {
        createLattice();
        copy(L);
    }

    //! Assignment operator
    Lattice2D& operator=(const Lattice2D& L)
    {
        if (this != &L) {
            if (_rows != L._rows || _cols != L._cols) {
                destroyLattice();
                _rows = L._rows;
                _cols = L._cols;
                createLattice();
            }
            copy(L);
        }
        return *this;
    }

    //! Destructor
    ~Lattice2D() {
        destroyLattice();
    }

    //! Returns a reference to the cell by () operator (cell indexing)
    Cell& operator()(const Dimension& i, const Dimension& j) {
        return lattice[i][j];
    }

    //! Returns a reference to the cell (cell indexing)
    Cell& get(const Dimension& i, const Dimension& j) {
        return lattice[i][j];
    }


    //! Sets the 2D lattice dimensions and allocates the lattice
    void setDimensions(const Dimension& r, const Dimension& c)
    {
        if (lattice != NULL)
            destroyLattice();
        _rows = r; _cols = c;
        createLattice();
    }


    //! Number of rows in lattice
    Dimension rows() const {
        return _rows;
    }

    //! Number of columns in lattice
    Dimension columns() const {
        return _cols;
    }

    //! Number of states (of first cell in lattice)
    StateCount cellStates() const {
        return lattice[0][0].stateCount();
    }

    //! Sets number of states
    void setCellStatesCount(const StateCount& s)
    {
        for (Dimension i = 0; i < _rows; i++)
            for (Dimension j = 0; j < _cols; j++)
                lattice[i][j].setStateCount(s);
    }

private:

    Dimension _rows, _cols; // rows, columns for 2D lattice

    Cell ** lattice;  // Two dimension array of cells Cell


    //! Lattice memory allocation
    void createLattice()
    {
        if ( !(lattice = new Cell*[_rows]) ) {
            std::cerr<< "Error with memory allocation" <<std::endl;
            throw;
        }
        for (Dimension i = 0; i < _rows; i++)
            if ( !(lattice[i] = new Cell[_cols]) ) {
                std::cerr<< "Error with memory allocation" <<std::endl;
                throw;
            }           
    }

    //! Lattice memory deallocation
    void destroyLattice()
    {
        if (lattice == NULL) return;
        for (int i=0; i<_rows; i++)
            delete[] lattice[i];
        delete[] lattice;
    }

    //! Copies data from lattice
    void copy(const Lattice2D& L)
    {
        for (Dimension i = 0; i < _rows; i++)
            for (Dimension j = 0; j < _cols; j++)
                lattice[i][j] = L.lattice[i][j];                    
    }
};

#endif // __LATTICE2D_H
