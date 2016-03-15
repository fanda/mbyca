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
 * File:    GridGraphicsView.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Base class for graphics views of cellular automata
 */

#ifndef GRIDGRAPHICSVIEW_H
#define GRIDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include <QSettings>

#include "CA/Lattice2D.h"

/*!
  Base class for graphics views of cellular automata
  Pure abstract (setRect)
*/
class GridGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    //! Constructor
    GridGraphicsView(int amountWidth,int amountHeight,int width,int height);

    //! Destructor
    ~GridGraphicsView() {
        delete scene;
    }

    //! Pure abstract method of setting state of the cell and color of the rect
    virtual void setRect(Dimension x, Dimension y, State s) = 0;

    //! Number of columns in lattice
    int width() {
        return lattice ? lattice->columns() : 0;
    }

    //! Number of rows in lattice
    int height() {
        return lattice ? lattice->rows() : 0;
    }

    //! Returns color of inactive cells (base color)
    QColor getInactiveColor() {
        return inactiveColor;
    }

    //! Sets color for inactive cells (base color)
    void changeInactiveColor();

protected:
    //! Helper method for getting one rect in the grid
    QGraphicsRectItem* getRect(const QPoint& pos);

    void mouseReleaseEvent(QMouseEvent* event);

    bool leftMousePressed;
    bool rightMousePressed;

    QGraphicsScene * scene;
    QList<QList<QGraphicsRectItem*> > gridOfRects;
    QColor inactiveColor;
    int cellWidth;
    int cellHeight;
    Lattice2D * lattice;

};

#endif // GRIDGRAPHICSVIEW_H
