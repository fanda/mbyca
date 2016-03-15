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
 * File:    MainWindow.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Main window of the program which handles subwindows
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "ui_MainWindow.h"

#include "SizeDialog.h"
#include "ConfigDialog.h"
#include "GlitchWindow.h"
#include "TransWindow.h"

namespace Ui {
    class MainWindow;
}

const int BUTTON_WIDTH = 90;
const int BUTTON_HEIGHT = 30;
const int BUTTON_X = 5;
const int BUTTON_MARGIN = 20;

/*!
  Main window of the program which handles subwindows
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor
    MainWindow(QWidget *parent = 0);

    //! Destructor
    ~MainWindow();

private slots:
    //! Creates new GlitchMusic window
    void newGlitchMusic();

    //! Creates new TransMusic window
    void newTransMusic();

    //! Handles configuration dialog
    void settings();

    //! Handles shutting down the program
    void quit();

    //! Handles dying window
    void subWindowIsDying(int id);

protected:
    //! Changes active window
    void changeEvent(QEvent *e);

private:
    //! Prepares button of the window
    void initButton(QString name);

    Ui::MainWindow *ui;

    QButtonGroup * windows_buttons;
    QMap<int, Window*> id_window;
    int highestId;

};

#endif // MAINWINDOW_H
