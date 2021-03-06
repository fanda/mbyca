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
 * File:    Window.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Base window class
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QTimer>
#include <QSettings>

#include "CA/Lattice2D.h"

const int DEFAULT_BPM = 190;// default music tempo


/*!
  Base window class
*/
class Window : public QWidget
{
    Q_OBJECT

protected:
    /*!
      Loop data store
    */
    struct Loop
    {
        int steps, step;
        Lattice2D firstLattice;

        Loop(int s, const Lattice2D & l) : steps(s), step(0), firstLattice(l) {}
    };

public:
    //! Contructor
    Window(QWidget* parent = 0)
      : QWidget(parent), timer(new QTimer), loop(NULL), id(0)
    {
        setAttribute(Qt::WA_DeleteOnClose, true);
        QSettings settings;
        bpm = settings.value("tempo", DEFAULT_BPM).toUInt();
    }

    //! Destructor
    virtual ~Window() {
        if (loop != NULL) delete loop;
    }

    //! Sets ID of window given by window manager
    void setId(int i) {
        id = i;
    }

public slots:
    //! Sets tempo of generated music
    void setBpm(int value)
    {
        bpm = value;
        if (timer->isActive())
            timer->start(60000/bpm);
    }

    //! Sets how many steps of automaton's iteration will be repeated
    void setLoopSteps(int value)
    {
        if (loop != NULL)
            loop->steps = value;
    }

signals:
    //! Signal of closing window
    void dying(int id);

protected:
    //! Closing slot for emitting closing signal
    void closeEvent(QCloseEvent *event) {
        emit dying(id);
     }

    QTimer * timer;

    Loop * loop;

    int id;

    unsigned int bpm;

};

#endif // WINDOW_H
