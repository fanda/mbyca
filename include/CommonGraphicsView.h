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
 * File:    CommonGraphicsView.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Graphics View for many 2D cellular automata
 */

#ifndef COMMONGRAPHICSVIEW_H
#define COMMONGRAPHICSVIEW_H

#include "GridGraphicsView.h"

/*!
  Graphics View for many 2D cellular automata
*/
class CommonGraphicsView : public GridGraphicsView
{
    Q_OBJECT

public slots:
    //! Receiving and showing current lattice of automaton
    void receiveBang(Lattice2D * l)
    {
        if (lattice == NULL) { // oh, it's the first lattice, init colors
            color.resize(l->cellStates());
            color[0] = inactiveColor;
            for (int i = 1; i < l->cellStates(); i++)
                color[i] = QColor((Qt::GlobalColor)(i+6));
        }
        lattice = l;// save the lattice
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++) // draw cells
                gridOfRects[x][y]->setBrush(QBrush(color[lattice->get(x, y).state()],Qt::SolidPattern));
    }

    //! Sets the active color (color, that can be drawn)
    void setActive(int state) {
        if (state > 0) activeState = (State)state;
    }

public:
    //! Constructor
    CommonGraphicsView(int amountWidth, int amountHeight, int width, int height);

    //! Sets state of cell in graphics view
    void setRect(Dimension x, Dimension y, State s);

    //! Change color for some state
    void changeColor(State state);

    //! Sets color for given state
    void setColor(State s, QColor c);

    //! Removes all colors and cleans lattice
    void removeAllColors();

    //! Returns color for given state
    QColor getColor(State state) {
        return color[state];
    }

protected:
    QVector<QColor> color;

    void mouseMoveEvent(QMouseEvent* event);    
    void mousePressEvent(QMouseEvent* event);    

private:
    State activeState;

};

#endif // COMMONGRAPHICSVIEW_H
