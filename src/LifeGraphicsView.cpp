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
 * File:    LifeGraphicsView.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Graphics View for Game of Life
 */

#include "LifeGraphicsView.h"

LifeGraphicsView::LifeGraphicsView(int amountWidth, int amountHeight, int w, int h)
    : GridGraphicsView(amountWidth, amountHeight, w, h)
{
    leftMousePressed = false;
    rightMousePressed = false;
    color = QColor("gray");
    inactiveColor = QColor("white");
    for (int y = 0; y < height(); y++)
        for (int x = 0; x < width(); x++)
            gridOfRects[x][y]->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
}


void LifeGraphicsView::changeColor()
{
    QColor c = QColorDialog::getColor(color);
    if (c.isValid() && c != color) {
        color = c;
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++)
                if (lattice->get(x,y).state() == 1)
                    setRect(x, y, 1);
    }
}


void LifeGraphicsView::setRect(Dimension x, Dimension y, State s)
{
    if (s)
        gridOfRects[x][y]->setBrush(QBrush(color,Qt::SolidPattern));
    else
        gridOfRects[x][y]->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
    lattice->get(x,y).setState(s);
}


void LifeGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (!leftMousePressed && !rightMousePressed) return;
    QGraphicsRectItem* rect;
    if ((rect = getRect(event->pos())) == 0) return;
    if (leftMousePressed || rightMousePressed) {
        int x = event->x() / cellWidth,
            y = event->y() / cellHeight;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return;
        lattice->get(x, y).setState((int)leftMousePressed || !rightMousePressed);
        if (leftMousePressed)  rect->setBrush(QBrush(color,Qt::SolidPattern)); else
        if (rightMousePressed) rect->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
    }
}


void LifeGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        leftMousePressed = true;
    if (event->button() == Qt::RightButton)
        rightMousePressed = true;
    QGraphicsRectItem* rect;
    if ((rect = getRect(event->pos())) == 0) return;
    if (leftMousePressed || rightMousePressed) {
        int x = event->x() / cellWidth,
            y = event->y() / cellHeight;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return;
        lattice->get(x, y).setState((int)leftMousePressed || !rightMousePressed);
        if (leftMousePressed)  rect->setBrush(QBrush(color, Qt::SolidPattern)); else
        if (rightMousePressed) rect->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
    }
}
