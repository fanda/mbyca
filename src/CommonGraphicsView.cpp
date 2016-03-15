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
 * File:    CommonGraphicsView.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Graphics View for many 2D cellular automata - implementation
 */

#include "CommonGraphicsView.h"

CommonGraphicsView::CommonGraphicsView(int amountWidth, int amountHeight, int w, int h)
    : GridGraphicsView(amountWidth,amountHeight,w,h), color(NULL)
{
    activeState = 1;
    leftMousePressed = false;
    rightMousePressed = false;
    inactiveColor = QColor("white");
    color << inactiveColor;
    for (int y = 0; y < height(); y++)
        for (int x = 0; x < width(); x++)
            gridOfRects[x][y]->setBrush(QBrush(inactiveColor, Qt::SolidPattern));
}


void CommonGraphicsView::changeColor(State state)
{
    QColor c = QColorDialog::getColor(color[state]);
    if (c.isValid() && c != color[state]) {
        color[state] = c;
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++)
                if (lattice->get(x,y).state() == state)
                    setRect(x,y,state);
    }
}


void CommonGraphicsView::setColor(State s, QColor c)
{
    if (s < color.size()) {
        if (c != color[s])
            color[s] = c;
        else
            return;
    }
    else if (s == color.size())
        color << c;
    else {
        color.resize(s + 1);
        color.insert(s, c);
    }
}


void CommonGraphicsView::removeAllColors()
{
    color.clear();
    lattice = NULL;
}


void CommonGraphicsView::setRect(Dimension x, Dimension y, State s)
{
    gridOfRects[x][y]->setBrush(QBrush(color[s],Qt::SolidPattern));
    lattice->get(x,y).setState(s);
}


void CommonGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    if (!leftMousePressed && !rightMousePressed) return;
    QGraphicsRectItem* rect;
    if ((rect = getRect(event->pos())) == 0) return;
    if (leftMousePressed || rightMousePressed) {
        int x = event->x() / cellWidth,
            y = event->y() / cellHeight,
            state = 0;
        if(x < 0 || x >= width() || y < 0 || y >= height()) return;
        if (leftMousePressed) {
            state = activeState;
            rect->setBrush(QBrush(color[activeState],Qt::SolidPattern));
        } else
        if (rightMousePressed)
            rect->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
        lattice->get(x, y).setState(state);
    }
}


void CommonGraphicsView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        leftMousePressed = true;
    if (event->button() == Qt::RightButton)
        rightMousePressed = true;
    QGraphicsRectItem* rect;
    if ((rect = getRect(event->pos())) == 0) return;
    if (leftMousePressed || rightMousePressed) {
        int x = event->x() / cellWidth,
            y = event->y() / cellHeight,
            state = 0;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return;
        if (leftMousePressed) {
            state = activeState;
            rect->setBrush(QBrush(color[activeState],Qt::SolidPattern));
        } else
        if (rightMousePressed)
            rect->setBrush(QBrush(inactiveColor,Qt::SolidPattern));
        lattice->get(x, y).setState(state);
    }
}
