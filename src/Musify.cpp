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
 * File:    Musify.cpp
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Base class for musifycation of cellular automaton
 */

#include "Musify.h"

extern RtAudio Musify::dac;
extern int Musify::instance_count = 0;

Musify::Musify(QWidget *parent)
  : QWidget(parent), tdata(), lattice(NULL), instrument_buttons(new QButtonGroup(this))
{    
    Stk::setSampleRate( 44100.0 );
    Stk::setRawwavePath( RAWWAVEPATH.toStdString() );

    if (instance_count++ == 0)
    {
        // Setup the RtAudio stream.
        RtAudio::StreamParameters parameters;
        parameters.deviceId = dac.getDefaultOutputDevice();
        // Count of channels
        parameters.nChannels = 1;
        // Figure out how many bytes in an StkFloat
        RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
        unsigned int bufferFrames = RT_BUFFER_SIZE;

        try {
        dac.openStream(&parameters,NULL,format,(unsigned int)Stk::sampleRate(),&bufferFrames,&tick,(void*)&tdata);
        }
        catch ( RtError& error ) { error.printMessage(); }
        play();
    }

    // init menu
    instrument_menu = new QMenu();
    InstrumentFactory iFactory;
    for (int i = 0; i < iFactory.instrument_names.size(); i++)
        instrument_menu->addAction(iFactory.instrument_names[i]);
    connect(instrument_menu, SIGNAL(triggered(QAction*)), this, SLOT(saveName(QAction*)));
    connect(instrument_buttons, SIGNAL(buttonPressed(int)), this, SLOT(changeInstrument(int)));
}


Musify::~Musify()
{
    QList<QAbstractButton*> buttons = instrument_buttons->buttons();
    for (int i = 0; i < buttons.size(); i++)
        delete buttons[i];
    delete instrument_buttons;
    delete instrument_menu;
    if (--instance_count == 0) {
        stop();
        try { dac.closeStream(); }
        catch ( RtError &error ) { error.printMessage(); }
        for (int i = instruments.size() - 1; i >= 0; i--)
            delete instruments[i];
    }
}


void Musify::selectInstrument(QString name, unsigned index)
{
    if (name == "") {
        instruments.push_back(NULL);
        instruments_tones.resize(instruments.size());
        return;
    }
    InstrumentFactory instr;
    if (index >= instruments.size()) {
        // add new instrument
        index = instruments.size();
        instruments.push_back( instr(name) );
        instruments_tones.push_back(instr.toneList());
        tdata.voicer.addInstrument(instruments[index], index);
    }
    else {
        removeInstrument(index);
        instruments[index] = instr(name);
        instruments_tones[index] = instr.toneList();
        tdata.voicer.addInstrument(instruments[index], index);
    }
}


void Musify::changeInstrument(int index)
{
    if (index <= 0) return;
    QToolButton* tb = (QToolButton*)instrument_buttons->button(index);
    selectInstrument(activeActionText, index - 1);
    tb->setText(activeActionText);
}


void Musify::removeInstrument(int index)
{
    Instrmnt * tmpi = instruments[index];
    if (tmpi != NULL) {
        tdata.voicer.removeInstrument(tmpi);
        delete tmpi;
    }
    instruments_tones[index].clear();
}


void Musify::play()
{
    try { dac.startStream(); }
    catch ( RtError &error ) { error.printMessage(); }
}


void Musify::stop()
{   // Shut down the callback and output stream
    try { dac.stopStream(); }
    catch ( RtError &error ) { error.printMessage(); }
}


void Musify::start_stopRecord()
{
    if (tdata.wavOutput != NULL) {
        delete tdata.wavOutput;
        tdata.wavOutput = NULL;
        QString newname = QFileDialog::getSaveFileName(this, "Save file as");
        if (newname == "")
            QFile::remove(filename);
        else {
            if (QFile::exists(newname))
                QFile::remove(newname);
            QFile::copy(filename, newname);
            QFile::remove(filename);
        }
    }
    else {
        int i = 1;
        do { filename = TMPFILENAME.arg(i++); }
        while (QFile::exists(filename));
        tdata.wavOutput = new FileWvOut(filename.toStdString());
    }
}
