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
 * File:    TransWindow.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Window for TransMusic
 */

#include "TransWindow.h"

TransWindow::TransWindow(int xC, int yC, QWidget* parent)
    : Window(parent), ui(new Ui::TransWindow), xCells(xC), yCells(yC)
{
    ui->setupUi(this);
    ui->tempo->setValue(bpm);

    ui->caFamily->insertItem(0, "Cyclic");
    ui->caFamily->insertItem(1, "Life");

    int cellWidth = 250 / xCells;
    int cellHeight = 250 / yCells;

    // params: states, threshold, extended, moore
    ca = new CyclicAutomaton(xCells, yCells, 3, 1, false, true);
    QStringList automata_names;
    automata_names<<"3 s. Moore"<<"4 s. Moore"<<"5 s. Moore"<<"6 s. Moore"
                  <<"3 s. Neumann"<<"4 s. Neumann"<<"5 s. Neumann"<<"6 s. Neumann";
    ui->caSelect->addItems(automata_names);
    QSettings settings;
    ui->backspase->setMaximum(settings.value("history", DEFAULT_BACKSPASE_STEPS).toInt());

    muse = new TransMusify(this);
    muse->setGeometry(280,20,120,200);
    for (int i = 1; i < ca->statesCount(); i++)
        muse->addColor(QColor((Qt::GlobalColor)(i+6)));
    muse->show();

    view = new CommonGraphicsView(xCells, yCells, cellWidth, cellHeight);
    ui->caView->setCurrentIndex( ui->caView->addWidget(view) );


    connect(ui->tempo, SIGNAL(valueChanged(int)), this, SLOT(setBpm(int)));
    connect(ui->steps, SIGNAL(valueChanged(int)), this, SLOT(setLoopSteps(int)));
    connect(ui->caFamily, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAutomatonFamily(int)));
    connect(ui->caSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAutomaton(int)));
    connect(ui->playButton, SIGNAL(pressed()), this, SLOT(play_stop()));
    connect(ui->loopButton, SIGNAL(pressed()), this, SLOT(start_stopLoop()));
    connect(ui->recordButton, SIGNAL(pressed()), muse, SLOT(start_stopRecord()));
    connect(timer,          SIGNAL(timeout()), this, SLOT(beat()));
    connect(ca, SIGNAL(firstBang(Lattice2D*)), view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      muse, SLOT(receiveBang(Lattice2D*)));
    connect(muse->colorButtons(), SIGNAL(buttonPressed(int)), view, SLOT(setActive(int)));
    connect(ui->clearButton,  SIGNAL(pressed()), ca, SLOT(clear()));
    connect(ui->randomButton, SIGNAL(pressed()), ca, SLOT(randomize()));
    connect(ui->backspase, SIGNAL(sliderMoved(int)), ca, SLOT(backspase(int)));

    ca->randomize();
    ca->setBackspaseLattice();
    //timer->start(60000/bpm);
}

TransWindow::~TransWindow()
{
    delete view;
    delete muse;
    delete ca;
}


void TransWindow::beat()
{
    ca->iterate();
    ui->backspase->setValue(ui->backspase->value()+1);
    if (loop != NULL) {
        if (++loop->step >= loop->steps) {
            ca->setLattice(&loop->firstLattice);
            loop->step = 0;
        }
    }
}


void TransWindow::play_stop()
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


void TransWindow::start_stopLoop()
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


void TransWindow::changeAutomatonFamily(int index)
{
    bool active = timer->isActive();
    if (active) timer->stop();
    delete ca;
    QStringList automata_names;
    switch (index) {
        case 0:
            ca = new CyclicAutomaton(xCells, yCells);
            automata_names<<"3 s. Moore"<<"4 s. Moore"<<"5 s. Moore"<<"6 s. Moore"
                          <<"3 s. Neumann"<<"4 s. Neumann"<<"5 s. Neumann"<<"6 s. Neumann";
            break;
        case 1:
            ca = new LifeTypeAutomaton(xCells, yCells);
            automata_names<<"Life"<<"2x2"<<"Amoeba"<<"Assimilation"<<"Coral"
                          <<"Flakes"<<"Maze"<<"Pseudo life"<<"Serviettes";
            break;
    }
    ui->caSelect->clear();
    ui->caSelect->addItems(automata_names);
    connect(ca, SIGNAL(firstBang(Lattice2D*)), view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      view, SLOT(receiveBang(Lattice2D*)));
    connect(ca, SIGNAL(bang(Lattice2D*)),      muse, SLOT(receiveBang(Lattice2D*)));
    connect(ui->clearButton,  SIGNAL(pressed()), ca, SLOT(clear()));
    connect(ui->randomButton, SIGNAL(pressed()), ca, SLOT(randomize()));
    muse->removeAllColors();
    view->removeAllColors();
    for (int i = 1; i < ca->statesCount(); i++) {
        muse->addColor(QColor((Qt::GlobalColor)(i+6)));
    }
    view->setActive(1);
    ca->clear();
    if (active) timer->start(60000/bpm);
}


void TransWindow::changeAutomaton(int index)
{
    bool active = timer->isActive();
    if (active) timer->stop();
    if (ui->caFamily->currentIndex() == 0) {
        int states = 3, threshold = 1, moore = true;
        switch (index) {
            case 0: states = 3; break;
            case 1: states = 4; break;
            case 2: states = 5; break;
            case 3: states = 6; break;
            case 4: states = 3; moore = false; break;
            case 5: states = 4; moore = false; break;
            case 6: states = 5; moore = false; break;
            case 7: states = 6; moore = false; break;
        }
        CyclicAutomaton * cca = (CyclicAutomaton *)ca;
        cca->changeRule(states, threshold, false, moore);
        muse->removeAllColors();
        view->removeAllColors();
        for (int i = 1; i < ca->statesCount(); i++) {
            muse->addColor(QColor((Qt::GlobalColor)(i+6)));
        }
        view->setActive(1);
        ca->clear();
    }
    else if (ui->caFamily->currentIndex() == 1) {
        QList<int> toSurvive, toBeBorn;
        switch (index) {
            case 0: toSurvive<<2<<3; toBeBorn<<3; break;
            case 1: toSurvive<<1<<2<<5; toBeBorn<<3<<6; break;
            case 2: toSurvive<<1<<3<<5<<8; toBeBorn<<3<<5<<7; break;
            case 3: toSurvive<<4<<5<<6<<7; toBeBorn<<3<<4<<5; break;
            case 4: toSurvive<<4<<5<<6<<7<<8; toBeBorn<<3; break;
            case 5: toSurvive<<0<<1<<2<<3<<4<<5<<6<<7<<8; toBeBorn<<3; break;
            case 6: toSurvive<<1<<2<<3<<4<<5; toBeBorn<<3;       break;
            case 7: toSurvive<<2<<3<<8; toBeBorn<<3<<5<<7; break;
            case 8: toBeBorn<<2<<3<<4;  break;
        }
        LifeTypeAutomaton* ltca = (LifeTypeAutomaton*)ca;
        ltca->changeRule(toSurvive.toSet(), toBeBorn.toSet());
    }
    if (active) timer->start(60000/bpm);
}
