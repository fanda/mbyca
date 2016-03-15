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
 * File:    ConfigDialog.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Dialog for settings
 */

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "Window.h"
#include "CA/CellularAutomaton2D.h"

#include "ui_ConfigDialog.h"

namespace Ui {
    class Dialog;
}

/*!
  Dialog for settings of the program
*/
class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    //! Constructor
    ConfigDialog(QWidget *parent = 0) : QDialog(parent), ui(new Ui::Settings)
    {
        ui->setupUi(this);
        QSettings settings;
        ui->bpm->setValue(settings.value("tempo", DEFAULT_BPM).toUInt());
        ui->history->setValue(settings.value("history", DEFAULT_BACKSPASE_STEPS).toInt());
    }

    //! Destructor
    ~ConfigDialog() {
        delete ui;
    }

    //! Returns default tempo for settings
    int tempo() const {
        return ui->bpm->value();
    }

    //! Returns number of lattices in history of cellular automaton for settings
    int history() const {
        return ui->history->value();
    }

private:
    Ui::Settings *ui;
};

#endif // CONFIGDIALOG_H
