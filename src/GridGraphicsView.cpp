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
 * File:    GridGraphicsView.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Base class for graphics views of cellular automata
 */

#include "GridGraphicsView.h"

GridGraphicsView::GridGraphicsView(int amountWidth,int amountHeight,int width,int height)
{
    // inicialization
    lattice = NULL;
    cellWidth = width;
    cellHeight = height;
    scene = new QGraphicsScene;
    // settings
    setScene(scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setFixedSize((amountWidth*cellWidth)+5, (amountHeight*cellHeight)+5);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // grid creating
    for (int x = 0; x < amountWidth; x++) {
        QList<QGraphicsRectItem*> line;
        for (int y = 0; y < amountHeight; y++) {
          line << scene->addRect(cellWidth*x,cellHeight*y,cellWidth,cellHeight,
                                 QPen(),QBrush(inactiveColor,Qt::SolidPattern));
        }
        gridOfRects << line;
    }
}


void GridGraphicsView::changeInactiveColor()
{
    QColor c = QColorDialog::getColor(inactiveColor);
    if (c.isValid() && c != inactiveColor) {
        inactiveColor = c;
        // setting new inactive color to dead cells
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++)
                if (lattice->get(x,y).state() == 0)
                    setRect(x,y,0);
    }
}


QGraphicsRectItem * GridGraphicsView::getRect(const QPoint& pos)
{
    int x = pos.x() / cellWidth,
        y = pos.y() / cellHeight;
    if (x < 0 || x >= width() || y < 0 || y >= height())
        return 0; // outside the grid
    else
        return gridOfRects[x][y];
}


void GridGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        leftMousePressed = false;
    if (event->button() == Qt::RightButton)
        rightMousePressed = false;
}
