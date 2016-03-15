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
 * File:    GlitchMask.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Mask widget fo GlitchMusic program. It is like
            cellular automaton graphics view, but do not display
            any automaton, only colors in the grid
 */

#ifndef GLITCHMASK_H
#define GLITCHMASK_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QColorDialog>

#include "CA/Lattice2D.h"

/*!
  Mask widget fo GlitchMusic program.
  It is like cellular automaton graphics view, but do not display
  any automaton, only colors in the grid
*/
class GlitchMask : public QGraphicsView
{
    Q_OBJECT

public slots:
    //! Adds color which can be displayed
    void addColor(QColor & c) {
        color << c;
    }

    //! Sets active color (can be drawn by mouse)
    void setActive(int value) {
        if (value > 0) active = value;
    }

public:
    //! Constructor
    GlitchMask(int amountWidth, int amountHeight, int width, int height);

    //! Destructor
    ~GlitchMask();

    //! Sets state of cell in mask
    void setRect(Dimension x, Dimension y, State s);

    int width() {
        return mask.size();
    }

    int height() {
        return mask[0].size();
    }

    //! Gets value of one cell in the mask
    int& get(const int& i, const int& j) {
        return mask[i][j];
    }

private:
    //! Helper method for getting one rect in the grid
    QGraphicsRectItem* getRect(const QPoint& pos);

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


    QGraphicsScene * scene;
    QList<QList<QGraphicsRectItem*> > grid;

    QVector< QVector<int> > mask;
    QVector<QColor> color;

    int cellWidth;
    int cellHeight;
    int active;

    bool leftMousePressed;
    bool rightMousePressed;

};

#endif // GLITCHMASK_H
