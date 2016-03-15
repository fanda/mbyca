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
 * File:    GlitchMusify.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   GlitchMusic musify method
 */

#ifndef GLITCHMUSIFY_H
#define GLITCHMUSIFY_H

#include "Musify.h"
#include "GlitchMask.h"

/*!
  GlitchMusic musify method
  Uses mask for declaring active colors (instruments).
  Has own button control widget.
*/
class GlitchMusify : public Musify
{
    Q_OBJECT

public slots:
    //! Receiving and mapping cellular automaton lattice to music
    void receiveBang(Lattice2D * l)
    {
        Skini::Message m;
        m.type = __SK_NoteOn_;
        m.floatValues.reserve(2);
        lattice = l;
        cellCount.fill(0);
        // check lattice
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++)
                if (lattice->get(x, y).state() && mask->get(x,y)) {
                    int instr_index = mask->get(x,y);
                    // modular mapping
                    if (++cellCount[instr_index] >= instruments_tones[instr_index-1].size())
                        cellCount[instr_index] = 0;
                }
        // send notes
        int states = cellCount.size();
        for (int i = 1; i < states; i++) {
            if (cellCount[i] > 0) {
                m.channel = i-1;
                m.time = (cellCount[i]%states)/(StkFloat)states;
                m.floatValues[0] = instruments_tones[i-1][cellCount[i]];// frequency
                m.floatValues[1] = 80;// amplitude
                tdata.messager.push(m);
                tdata.done = false;
            }
        }
    }

public:
    //! Constructor
    explicit GlitchMusify(int amountWidth,int amountHeight,int width,int height,QWidget *parent = 0)
        : Musify(parent),
          mask(new GlitchMask(amountWidth, amountHeight, width, height)),
          color_buttons(new QButtonGroup(this))
    {
        connect(color_buttons, SIGNAL(buttonPressed(int)), mask, SLOT(setActive(int)));
    }

    //! Destructor
    virtual ~GlitchMusify()
    {
        QList<QAbstractButton*> buttons = color_buttons->buttons();
        for (int i; i < buttons.size(); i++)
            delete buttons[i];
        delete color_buttons;
        delete mask;
    }

    //! Pointer to the mask, for connecting with outer widgets
    GlitchMask * getMask() {
        return mask;
    }

    //! Adds instrument for mapping and color to the mask
    void addColor(QColor c)
    {
        int count = instruments.size();
        int y = count * 30;
        // color button adding
        QToolButton * color_button = new QToolButton(this);
        color_button->setStyleSheet(COLOR_STYLE.arg(c.name()));
        color_button->setCheckable(true);
        color_button->show();
        // instrument menu
        QToolButton * instrument_button = new QToolButton(this);
        instrument_button->setMenu(instrument_menu);
        instrument_button->setText("");
        instrument_button->setPopupMode(QToolButton::InstantPopup);
        // geometry of subwidgets
        instrument_button->setGeometry(30, y, 75, 25);
        color_button->setGeometry(0, y, 25, 25);
        color_button->show();
        instrument_button->show();

        if (0 == count++) color_button->setChecked(true);// if first instrument/color/
        color_buttons->addButton(color_button, count);// count == buttonId
        instrument_buttons->addButton(instrument_button, count);// count == instrumentID
        cellCount.resize(++count);// needs to be little bigger

        mask->addColor(c);
        selectInstrument("");
    }

private:
    GlitchMask * mask;

    QVector<int> cellCount;

    QButtonGroup * color_buttons;

};

#endif // GLITCHMUSIFY_H
