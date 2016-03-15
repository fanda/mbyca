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
 * File:    GlitchWindow.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Window for GlitchMusic
 */

#include "GlitchWindow.h"

GlitchWindow::GlitchWindow(int xCells, int yCells, QWidget* parent)
    : Window(parent), ui(new Ui::GlitchWindow)
{
    ui->setupUi(this);
    ui->tempo->setValue(bpm);

    int cellWidth = 250 / xCells;
    int cellHeight = 250 / yCells;

    muse = new GlitchMusify(xCells, yCells, cellWidth, cellHeight, this);
    view = new LifeGraphicsView(xCells, yCells, cellWidth, cellHeight);

    ui->caView->addWidget(view);
    ui->caView->setCurrentWidget(view);
    ui->caView->addWidget(muse->getMask());

    automata_names<<"Life"<<"2x2"<<"Amoeba"<<"Assimilation"<<"Coral"<<"Flakes"<<"Maze"<<"Pseudo life"<<"Serviettes";
    ui->caSelect->addItems(automata_names);

    ca = new LifeTypeAutomaton(xCells, yCells);
    QSettings settings;
    ui->backspase->setMaximum(settings.value("history", DEFAULT_BACKSPASE_STEPS).toInt());

    connect(ui->tempo, SIGNAL(valueChanged(int)), this, SLOT(setBpm(int)));
    connect(ui->steps, SIGNAL(valueChanged(int)), this, SLOT(setLoopSteps(int)));
    connect(ui->playButton, SIGNAL(pressed()),    this, SLOT(play_stop()));

    connect(ca, SIGNAL(firstBang(Lattice2D*)), view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      muse, SLOT(receiveBang(Lattice2D*)));

    connect(ui->caSelect,   SIGNAL(currentIndexChanged(int)), this, SLOT(changeAutomaton(int)));
    connect(timer,          SIGNAL(timeout()),         this, SLOT(beat()));
    connect(ui->loopButton, SIGNAL(pressed()),         this, SLOT(start_stopLoop()));
    connect(ui->recordButton, SIGNAL(pressed()),       muse, SLOT(start_stopRecord()));
    connect(ui->showMask,   SIGNAL(stateChanged(int)), this, SLOT(switchViews(int)));
    connect(ui->clearButton,  SIGNAL(pressed()),     ca, SLOT(clear()));
    connect(ui->randomButton, SIGNAL(pressed()),     ca, SLOT(randomize()));
    connect(ui->backspase, SIGNAL(sliderMoved(int)), ca, SLOT(backspase(int)));


    ca->randomize(8);
    ca->setBackspaseLattice();

    muse->setGeometry(280,25,120,200);// set it right in GUI
    // create buttons
    muse->addColor(QColor((Qt::GlobalColor)7));
    muse->addColor(QColor((Qt::GlobalColor)8));
    muse->addColor(QColor((Qt::GlobalColor)9));
    muse->addColor(QColor((Qt::GlobalColor)10));
    muse->addColor(QColor((Qt::GlobalColor)11));
    muse->show();

    //timer->start(60000/bpm);
}

GlitchWindow::~GlitchWindow()
{
    delete view;
    delete muse;
    delete ca;
}

void GlitchWindow::play_stop()
{
    if (timer->isActive()) {
        timer->stop();
        ui->playButton->setText("play");
    }
    else {
        ca->setBackspaseLattice();
        timer->start(60000/bpm);
        ui->playButton->setText("stop");
    }
    if (loop != NULL)
        loop->firstLattice = ca->currentLattice();
}


void GlitchWindow::beat()
{
    ca->iterate();
    ui->backspase->setValue(ui->backspase->value()+1);
    if (loop != NULL)
        if (++loop->step >= loop->steps) {
            ca->setLattice(&loop->firstLattice);
            loop->step = 0;
        }
}


void GlitchWindow::start_stopLoop()
{
    if (loop == NULL) {
        loop = new Loop(ui->steps->value(), ca->currentLattice());
        ui->loopButton->setText("stop loop");
    }
    else {
        delete loop;
        loop = NULL;
        ui->loopButton->setText("start loop");
    }
}


void GlitchWindow::switchViews(int which) {
    if (which == 0)
        ui->caView->setCurrentIndex(0);
    else
        ui->caView->setCurrentIndex(1);
}


void GlitchWindow::changeAutomaton(int index)
{
    bool active = timer->isActive();
    if (active) timer->stop();
    QList<int> toSurvive, toBeBorn;
    switch (index) {
        case 0: toSurvive<<2<<3;          toBeBorn<<3; break;
        case 1: toSurvive<<1<<2<<5;       toBeBorn<<3<<6; break;
        case 2: toSurvive<<1<<3<<5<<8;    toBeBorn<<3<<5<<7; break;
        case 3: toSurvive<<4<<5<<6<<7;    toBeBorn<<3<<4<<5; break;
        case 4: toSurvive<<4<<5<<6<<7<<8; toBeBorn<<3; break;
        case 5: toSurvive<<0<<1<<2<<3<<4<<5<<6<<7<<8; toBeBorn<<3; break;
        case 6: toSurvive<<1<<2<<3<<4<<5; toBeBorn<<3;       break;
        case 7: toSurvive<<2<<3<<8;       toBeBorn<<3<<5<<7; break;
        case 8:                           toBeBorn<<2<<3<<4; break;
    }
    ca->changeRule(toSurvive.toSet(), toBeBorn.toSet());
    if (active) timer->start(60000/bpm);
}
