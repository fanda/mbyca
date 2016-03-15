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
 * File:    Musify.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Base class for musifycation of cellular automaton
 */

#ifndef MUSIFY_H
#define MUSIFY_H

#include <QWidget>
#include <QButtonGroup>
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QVector>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>

#include <vector>
#include <queue>
#include <iostream>

#include "RtAudio.h"
#include "FileWvOut.h"
#include "Voicer.h"
#include "Skini.h"
#include "SKINI.msg"
#include "FileWvOut.h"

#include "Instruments.h"

#include "CA/Lattice2D.h"

// Button background style - helper string
const QString COLOR_STYLE = "QToolButton { background-color : %1; }";
const QString RAWWAVEPATH = "./stk/rawwaves/";
const QString TMPFILENAME = ".mbyca%1.wav~";

using namespace stk;

/*!
  Base class for musifycation of cellular automaton
  It is interface between cellular automaton and STK sound library.
  Supports real-time playing and controls STK (Synthesis ToolKit).
*/
class Musify : public QWidget
{
    Q_OBJECT

    /*!
      Carrier of data about currently playing sound
    */
    struct TickData
    {
      Voicer voicer;
      std::queue<Skini::Message> messager;
      unsigned int counter;
      bool done;
      FileWvOut * wavOutput;

      TickData() : counter(0), done(true), wavOutput(NULL) {}
    };

    //! Automatic callback function for STK
    /*!
      Receives sound informations and fill output sound buffer if needed.
    */
    static
    int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
             double streamTime, RtAudioStreamStatus status, void *userData )
    {        
      TickData *data = (TickData*)userData;
      register StkFloat *samples = (StkFloat *) outputBuffer;
      unsigned int counter;
      // should some sound by played?
      if (data->done) { // no sounds
          if (data->counter == 1) {
              --data->counter     ;
              for ( unsigned i=0; i<nBufferFrames; i++ ) *samples++ = 0;
          }
      }
      else while (nBufferFrames > 0) {// fill the sound card buffer
        while (!data->messager.empty()) {
            // parse sound information from text format
            Skini::Message m = data->messager.front(); data->messager.pop();
            if ( m.type > 0 ) {
                if (m.type == __SK_NoteOn_) {
                    if (m.floatValues[1] == 0.0)
                        data->voicer.noteOff(m.floatValues[0], 64.0);
                    else {
                        data->voicer.setFrequency(m.floatValues[0], m.channel);
                        data->voicer.noteOn(m.floatValues[0], m.floatValues[1], m.channel);
                    }
                }
                else if (m.type == __SK_NoteOff_)
                    data->voicer.noteOff(m.floatValues[0], m.floatValues[1]);
                data->counter = (long) (m.time * Stk::sampleRate());
            }
            else data->counter = 64;
        }
        // set counter
        counter = qMin( nBufferFrames, data->counter );
        data->counter -= counter;
        // fill buffer
        for ( unsigned i=0; i<counter; i++ ) {
          *samples = data->voicer.tick();
          //std::cerr<<"tick"<<std::endl;
          if (data->wavOutput != NULL) {
              //std::cerr<<"output"<<std::endl;
              data->wavOutput->tick(*samples);
          }
          *samples++;
          --nBufferFrames;
        }
        if (data->counter <= 0) {
            data->done = true;
            data->counter = 1;
            break;
        }
      }
      return 0;
    }


public:
    //! Constructor
    explicit Musify(QWidget *parent = 0);
    //! Destructor
    virtual ~Musify();

    //! Creates selected instrument object and adds it into voicer
    void selectInstrument(QString name, unsigned index = 0);

    //! Removes instrument from voicer and destroys it
    void removeInstrument(int index);

    //! Start sound output buffer filling
    void play();

    //! Stop all sound
    void stop();

    //! Number of columns in 2D cellular automaton
    int width() {
        return lattice ? lattice->columns() : 0;
    }

    //! Number of rows in 2D cellular automaton
    int height() {
        return lattice ? lattice->rows() : 0;
    }

public slots:
    //! Helper slot for remembering instrument name
    void saveName(QAction* a) {
        activeActionText = a->text();
    }

    //! Replaces instrument in voicer
    void changeInstrument(int index);

    //! Starts or stops recording and manages target file
    void start_stopRecord();

protected:
    TickData tdata;
    std::vector<Instrmnt*> instruments;
    QVector< QList<StkFloat> > instruments_tones;

    Lattice2D * lattice;

    QString activeActionText;
    QMenu * instrument_menu;
    QButtonGroup * instrument_buttons;

private:    
    static RtAudio dac;
    static int instance_count;
    QString filename;
};

#endif // MUSIFY_H
