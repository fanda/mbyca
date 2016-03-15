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
 * File:    TransMusify.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   TransMusic musify method
 */

#ifndef TRANSMUSIFY_H
#define TRANSMUSIFY_H

#include "Musify.h"

#include <QPainter>
#include <QBrush>
#include <QRect>

/*!
  TransMusic musify method
  Has own button control widget.
  Counts all cells of some state in cellular automaton
*/
class TransMusify : public Musify
{
    Q_OBJECT

public slots:
    //! Receiving and mapping cellular automaton lattice to music
    void receiveBang(Lattice2D * l)
    {
        if (instruments_tones.size() == 0) return;
        Skini::Message m;
        m.type = __SK_NoteOn_;
        m.floatValues.reserve(2);
        lattice = l;
        cellCount.fill(0);
        int value;

        for (int y = 0; y < height(); y++) {
            for (int x = 0; x < width(); x++) {
                if ((value = lattice->get(x, y).state()))
                    ++cellCount[value];                
                else // count ZERO states
                    ++cellCount[0];
            }
        }
        // send notes
        for (int i = 1; i < cellCount.size(); i++) {
            if (cellCount[i] > 0) {
                m.channel = i-1;
                if (! instruments_tones[i-1].size()) continue;
                int delta = qAbs(cellCount[i] - lastCellCount[i]) % instruments_tones[i-1].size();
                m.floatValues[0] = instruments_tones[i-1][delta++];
                m.floatValues[1] = 80;
                m.time = (cellCount[0]%delta)/(StkFloat)delta;
                tdata.messager.push(m);
                tdata.done = false;
            }
        }
        lastCellCount = cellCount;
    }

public:
    //! Constructor
    explicit TransMusify(QWidget *parent = 0) : Musify(parent), color_buttons(new QButtonGroup(this))
    { }

    //! Destructor
    virtual ~TransMusify()
    {
        QList<QAbstractButton*> buttons = color_buttons->buttons();
        for (int i; i < buttons.size(); i++)
            delete buttons[i];
        delete color_buttons;
    }

    //! Pointer to ButtonGroup widget, for connecting with outter widgets
    QButtonGroup * colorButtons() {
        return color_buttons;
    }

    //! Adds instrument for mapping and color to the mask
    void addColor(QColor c)
    {
        int count = instruments.size();
        int y = count * 30;

        QToolButton * color_button = new QToolButton(this);
        color_button->setStyleSheet(COLOR_STYLE.arg(c.name()));
        color_button->setCheckable(true);
        color_button->setGeometry(0, y, 25, 25);
        color_button->show();

        QToolButton * instrument_button = new QToolButton(this);
        instrument_button->setMenu(instrument_menu);
        instrument_button->setText("");
        instrument_button->setPopupMode(QToolButton::InstantPopup);
        instrument_button->setGeometry(30, y, 75, 25);
        instrument_button->show();

        if (0 == count++) color_button->setChecked(true);
        color_buttons->addButton(color_button, count);
        instrument_buttons->addButton(instrument_button, count);

        cellCount.resize(++count);// needs to be little bigger
        lastCellCount.resize(count);
        lastCellCount.fill(0);

        selectInstrument("");
    }

    //! Clears all instruments and colors from mapping
    void removeAllColors()
    {
        QList<QAbstractButton*> buttons;
        buttons = color_buttons->buttons();
        for (int i = 0; i < buttons.size(); i++)
            delete buttons[i];
        buttons = instrument_buttons->buttons();
        for (int i = 0; i < buttons.size(); i++)
            delete buttons[i];
        for (int i = instruments.size() - 1; i >= 0; i--)
            removeInstrument(i);
        instruments.clear();
        instruments_tones.clear();
    }

private:
    QVector<int> cellCount;
    QVector<int> lastCellCount;

    QButtonGroup * color_buttons;

};

#endif // TRANSMUSIFY_H
