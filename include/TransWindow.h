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
 * File:    TransWindow.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Window for TransMusic
 */

#ifndef TRANSWINDOW_H
#define TRANSWINDOW_H


#include "Window.h"
#include "ui_TransWindow.h"

#include "CommonGraphicsView.h"
#include "TransMusify.h"

#include "CA/LifeTypeAutomaton.h"
#include "CA/CyclicAutomaton.h"

/*!
  Window for TransMusic
  User interface logic and control above cellular automaton
*/
class TransWindow : public Window
{
    Q_OBJECT

public:
    //! Constructor
    TransWindow(int xC, int yC, QWidget* parent = 0);

    //! Destructor
    virtual ~TransWindow();

public slots:

    //! Action for Play/Stop button
    void play_stop();

    //! Logic and iteration loop for cellular automaton
    void beat();

    //! Action for Play/Stop Loop button
    void start_stopLoop();

    //! Changes cellular automaton type (Cyclic <-> Life)
    void changeAutomatonFamily(int index);

    //! Changes cellular automaton rule
    void changeAutomaton(int index);

private:
    Ui::TransWindow * ui;

    CellularAutomaton2D * ca;

    CommonGraphicsView * view;

    TransMusify * muse;

    int xCells, yCells;

};

#endif // TRANSWINDOW_H
