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
 * File:    LifeGraphicsView.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Graphics View for Game of Life
 */

#ifndef LIFEGRAPHICSVIEW_H
#define LIFEGRAPHICSVIEW_H

#include "GridGraphicsView.h"

/*!
  Graphics View widget for Game of Life
*/
class LifeGraphicsView : public GridGraphicsView
{
    Q_OBJECT

public slots:
    //! Receiving and showing current lattice of automaton
    void receiveBang(Lattice2D * l)
    {
        // first lattice isn't special like in common view
        // all colors are initialized in constructor
        lattice = l;// save the lattice
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++) // draw cells
                if (lattice->get(x, y).state() == 1)
                    gridOfRects[x][y]->setBrush(QBrush(color,Qt::SolidPattern));
                else
                    gridOfRects[x][y]->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
    }

public:
    //! Constructor
    LifeGraphicsView(int amountWidth,int amountHeight,int w,int h);

    //! Sets the active color (color, that can be drawn)
    void setRect(Dimension x, Dimension y, State s);

    //! Adds color that can be displayed with color dialog
    void changeColor();

    //! Sets color of alive cell
    QColor getColor() {
        return color;
    }

protected:
    QColor color;

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

};

#endif // LIFEGRAPHICSVIEW_H
