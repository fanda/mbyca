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
 * File:    SizeDialog.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Dialog for choosing size of lattice
 */

#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include "ui_SizeDialog.h"

namespace Ui {
    class SizeDialog;
}

/*!
  Dialog for choosing size of lattice and name of the window
*/
class SizeDialog : public QDialog
{
    Q_OBJECT

public slots:
    //! Handles correct displaying of values
    void valueChanged(int i)
    {
        ui->width->setValue(i);
    }

public:
    //! Constructor
    SizeDialog(QWidget *parent = 0) : QDialog(parent), ui(new Ui::SizeDialog)
    {
        ui->setupUi(this);
        connect(ui->width,  SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    }

    //! Destructor
    ~SizeDialog() {
        delete ui;
    }

    //! Returns choosed width
    int width() const {
        return ui->width->value();
    }

    //! Returns choosed height
    int height() const {
        return ui->width->value();
    }

    //! Returns name of the window given by the user
    QString id() const {
        return ui->id->text();
    }

    //! Sets correct name of the window
    void setId(QString t) {
        ui->id->setText(t);
    }

private:
    Ui::SizeDialog *ui;
};

#endif // SIZEDIALOG_H
