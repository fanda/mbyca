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
 * File:    Instruments.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Selection based factory for instruments
            Based on Gary P. Scavone's idea
 */

#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

// STK Instrument Classes
#include "Clarinet.h"
#include "BlowHole.h"
#include "Saxofony.h"
#include "Flute.h"
#include "Brass.h"
#include "BlowBotl.h"
#include "Bowed.h"
#include "Plucked.h"
#include "StifKarp.h"
#include "Sitar.h"
#include "Mandolin.h"
#include "Rhodey.h"
#include "Wurley.h"
#include "TubeBell.h"
#include "HevyMetl.h"
#include "PercFlut.h"
#include "BeeThree.h"
#include "FMVoices.h"
#include "VoicForm.h"
#include "Moog.h"
#include "Simple.h"
#include "Drummer.h"
#include "BandedWG.h"
#include "Shakers.h"
#include "ModalBar.h"
#include "Mesh2D.h"
#include "Resonate.h"
#include "Whistle.h"
#include "Instrmnt.h"

#include <QStringList>

using namespace stk;

/*!
  Selection based factory for instruments
*/
struct InstrumentFactory
{
    QStringList instrument_names;//! All instrument's names

    QList<StkFloat> tones;//! All 7 octaves frequencies

    //! Constructor
    InstrumentFactory()
    {
        instrument_names << "Clarinet" << "BlowHole" << "Saxofony" << "Flute" << "Brass" <<
        "BlowBotl" << "Bowed" << "Plucked" << "StifKarp" << "Sitar" << "Mandolin" <<
        "Rhodey" << "Wurley" << "TubeBell" << "HevyMetl" << "PercFlut" <<
        "BeeThree" << "FMVoices" << "VoicForm" << "Moog" << "Simple" << "Drummer" <<
        "BandedWG" << "Shakers" << "ModalBar" << "Mesh2D" << "Resonate" << "Whistle";
        i = instrument_names.size();
        //! Set frequencies for 7 octaves
        tones << 16.35 << 18.35 << 20.60 << 21.83 << 24.50 << 27.50 << 30.87;
        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 7; j++)
                tones << tones[i*7 + j]*2;

    }

    //! Creates instrument object
    Instrmnt * operator()(QString name)
    {        
        find(name);
        if      (i==0)  return new Clarinet(10.0);
        else if (i==1)  return new BlowHole(10.0); // XXX
        else if (i==2)  return new Saxofony(10.0);
        else if (i==3)  return new Flute(10.0); // XXX
        else if (i==4)  return new Brass(10.0);
        else if (i==5)  return new BlowBotl();
        else if (i==6)  return new Bowed(10.0);
        else if (i==7)  return new Plucked(5.0);
        else if (i==8)  return new StifKarp(5.0);
        else if (i==9)  return new Sitar(5.0);
        else if (i==10) return new Mandolin(5.0);

        else if (i==11) return new Rhodey;
        else if (i==12) return new Wurley;
        else if (i==13) return new TubeBell;
        else if (i==14) return new HevyMetl();
        else if (i==15) return new PercFlut();
        else if (i==16) return new BeeThree;
        else if (i==17) return new FMVoices;

        else if (i==18) return new VoicForm();
        else if (i==19) return new Moog();
        else if (i==20) return new Simple();
        else if (i==21) return new Drummer();
        else if (i==22) return new BandedWG();
        else if (i==23) return new Shakers();
        else if (i==24) return new ModalBar();
        else if (i==25) return new Mesh2D(10, 10);
        else if (i==26) return new Resonate();
        else if (i==27) return new Whistle();

        else {
          return NULL;
        }
    }

    //! Returns frequencies for each instrument according to its properties
    /*!
      It is called for lastly created instrument
    */
    QList<StkFloat> toneList()
    {
        if      (i==0)  return tones.mid(21, 26); // Clarinet
        else if (i==1)  return tones.mid(0, 18); // BlowHole
        else if (i==2)  return tones.mid(0, 19); // Saxofony
        else if (i==3)  return tones.mid(11, 7);
        else if (i==4)  return tones.mid(15, 3); // Brass
        else if (i==5)  return tones.mid(12, 11); // BlowBotl
        else if (i==6)  return tones.mid(10, 8); // Bowed
        else if (i==7)  return tones.mid(0, 20); // Plucked
        else if (i==8)  return tones.mid(0, 20); // StifKarp
        else if (i==9)  return tones.mid(0, 20); // Sitar
        else if (i==10) return tones.mid(0, 20); // Mandolin

        else if (i==11) return tones.mid(0, 22); // Rhodey
        else if (i==12) return tones.mid(0, 22); // Wurley
        else if (i==13) return tones.mid(2, 22); // TubeBell
        else if (i==14) return tones.mid(2, 20); // HevyMetl
        else if (i==15) return tones.mid(2, 20); // PercFlut
        else if (i==16) return tones.mid(2, 20); // BeeThree
        else if (i==17) return tones.mid(2, 20); // FMVoices

        else if (i==18) return tones; // VoicForm
        else if (i==19) return tones.mid(2, 18); // Moog
        else if (i==20) return tones.mid(2, 18); // Simple
        else if (i==21) return tones.mid(2, 1); // Drummer
        else if (i==22) return tones.mid(11, 7); // BandedWG
        else if (i==23) return tones.mid(2, 1); // Shakers
        else if (i==24) return tones.mid(7, 12); // ModalBar
        else if (i==25) return tones.mid(2, 1); // Mesh2D
        else if (i==26) return tones.mid(2, 1); // Resonate
        else if (i==27) return tones.mid(0, 19); // Whistle

        else {
          return QList<StkFloat>();
        }
    }

private:
    int i;

    void find(QString name)
    {
        int not_found = 1;
        for ( i = 0; i < instrument_names.size(); i++ ) {
            if ( name == instrument_names[i] ) {
              not_found = 0;
              break;
            }
        }
        if (not_found) ++i;
    }
};

#endif // INSTRUMENTS_H
