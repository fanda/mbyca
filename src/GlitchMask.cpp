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
 * File:    GlitchMask.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Mask widget fo GlitchMusic program. It is like
            cellular automaton graphics view, but do not display
            any automaton, only colors in the grid
 */

#include "GlitchMask.h"

GlitchMask::GlitchMask(int amountWidth,int amountHeight,int width,int height)
    : cellWidth(width), cellHeight(height), active(1)
{
    scene = new QGraphicsScene;
    setScene(scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    color << QColor("white");
    for (int x = 0; x < amountWidth; x++) {
        QList<QGraphicsRectItem*> line;
        QVector<int> row;
        for (int y = 0; y < amountHeight; y++) {
          line << scene->addRect(cellWidth*x,cellHeight*y,cellWidth,cellHeight,QPen(),QBrush(color[0],Qt::SolidPattern));
          row  << 0;
        }
        grid << line;
        mask << row;
    }
    leftMousePressed = false;
    rightMousePressed = false;
}


GlitchMask::~GlitchMask() {
    delete scene;
}


void GlitchMask::setRect(Dimension x, Dimension y, State s)
{
    grid[x][y]->setBrush(QBrush(color[s],Qt::SolidPattern));
    mask[x][y] = s;
}


QGraphicsRectItem* GlitchMask::getRect(const QPoint& pos)
{
    int x = pos.x() / cellWidth,
        y = pos.y() / cellHeight;
    if (x < 0 || x >= width() || y < 0 || y >= height())
        return 0;
    else
        return grid[x][y];
}


void GlitchMask::mouseMoveEvent(QMouseEvent* event)
{
    if (!leftMousePressed && !rightMousePressed) return;
    QGraphicsRectItem* rect;
    if ((rect = getRect(event->pos())) == 0) return;
    if (leftMousePressed || rightMousePressed) {
        int x = event->x() / cellWidth,
            y = event->y() / cellHeight,
            value = 0;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return;
        if (leftMousePressed) {
            value = active;
            rect->setBrush(QBrush(color[active],Qt::SolidPattern));
        } else
        if (rightMousePressed)
            rect->setBrush(QBrush(color[0],Qt::SolidPattern));
        mask[x][y] = value;
    }
}


void GlitchMask::mousePressEvent(QMouseEvent* event)
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
            value = 0;
        if (x < 0 || x >= width() || y < 0 || y >= height()) return;
        if (leftMousePressed) {
            value = active;
            rect->setBrush(QBrush(color[active],Qt::SolidPattern));
        } else
        if (rightMousePressed)
            rect->setBrush(QBrush(color[0],Qt::SolidPattern));
        mask[x][y] = value;
    }
}


void GlitchMask::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        leftMousePressed = false;
    if (event->button() == Qt::RightButton)
        rightMousePressed = false;
}
