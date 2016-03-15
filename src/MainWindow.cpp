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
 * File:    MainWindow.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Main window of the program which handles subwindows
 */

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    windows_buttons(new QButtonGroup),
    highestId(1)
{
    ui->setupUi(this);
    connect(ui->actionNew_GlitchMusic, SIGNAL(triggered()), this, SLOT(newGlitchMusic()));
    connect(ui->actionNew_TransMusic,  SIGNAL(triggered()), this, SLOT(newTransMusic()));
    connect(ui->actionSettings,  SIGNAL(triggered()), this, SLOT(settings()));
    connect(ui->actionQuit,    SIGNAL(triggered()),   this, SLOT(quit()));
    setAttribute(Qt::WA_DeleteOnClose, true);
}

MainWindow::~MainWindow()
{
    QList<QAbstractButton*>::iterator i = windows_buttons->buttons().begin();
    for (int wid = 0; i != windows_buttons->buttons().end(); i++, wid++) {
        delete *i;
        delete id_window[wid];
    }
    delete windows_buttons;
    delete ui;
}

void MainWindow::initButton(QString name)
{
    int y = (windows_buttons->buttons().size()+1) * BUTTON_HEIGHT;
    QToolButton * window_button = new QToolButton(this);
    window_button->setGeometry(BUTTON_X, y, BUTTON_WIDTH, BUTTON_HEIGHT);
    window_button->setText(name);
    window_button->show();
    windows_buttons->addButton(window_button, highestId);
}

void MainWindow::newGlitchMusic()
{
    SizeDialog d(this);
    d.setId("GlitchMusic");
    d.exec();
    if ( ! d.result() ) return;
    Window * window = new GlitchWindow(d.width(), d.height(), this);
    id_window[highestId] = window;
    initButton(d.id());
    window->setId(highestId++);
    window->setWindowFlags(Qt::Window);
    window->setWindowTitle(d.id());
    connect(window, SIGNAL(dying(int)), this, SLOT(subWindowIsDying(int)));
    window->show();
}

void MainWindow::newTransMusic()
{
    SizeDialog d(this);
    d.setId("TransMusic");
    d.exec();
    if ( ! d.result() ) return;  
    Window * window = new TransWindow(d.width(), d.height(), this);
    id_window[highestId] = window;
    initButton(d.id());
    window->setId(highestId++);
    window->setWindowFlags(Qt::Window);
    window->setWindowTitle(d.id());
    connect(window, SIGNAL(dying(int)), this, SLOT(subWindowIsDying(int)));
    window->show();    
}

void MainWindow::settings()
{
    ConfigDialog d(this);
    d.exec();
    if ( ! d.result() ) return;
    QSettings settings;
    settings.setValue("history", d.history());
    settings.setValue("tempo", d.tempo());
}

void MainWindow::quit()
{
    qApp->quit();
}

void MainWindow::subWindowIsDying(int id)
{
    QAbstractButton * wb = windows_buttons->button(id);
    windows_buttons->removeButton(wb);
    delete wb;
    QList<QAbstractButton*>::iterator it = windows_buttons->buttons().begin();
    for (int i = 1; it != windows_buttons->buttons().end(); it++, i++) {
        wb = *it;
        wb->setGeometry(BUTTON_X, i*BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT);
    }
    id_window.remove(id);
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
