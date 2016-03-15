/*
 * File:    CommonGraphicsView.h
 * Authors: Pavel Novotny, xnovot28@stud.fit.vutbr.cz
 * Project: Music Creation Using Cellular Automata
 * About:   Graphics View for many 2D cellular automata
 */

#ifndef COMMONGRAPHICSVIEW_H
#define COMMONGRAPHICSVIEW_H

#include "GridGraphicsView.h"

/*!
  Graphics View for many 2D cellular automata
*/
class CommonGraphicsView : public GridGraphicsView
{
    Q_OBJECT

public slots:
    //! Receiving and showing current lattice of automaton
    void receiveBang(Lattice2D * l)
    {
        if (lattice == NULL) { // oh, it's the first lattice, init colors
            color.resize(l->cellStates());
            color[0] = inactiveColor;
            for (int i = 1; i < l->cellStates(); i++)
                color[i] = QColor((Qt::GlobalColor)(i+6));
        }
        lattice = l;// save the lattice
        for (int y = 0; y < height(); y++)
            for (int x = 0; x < width(); x++) // draw cells
                gridOfRects[x][y]->setBrush(QBrush(color[lattice->get(x, y).state()],Qt::SolidPattern));
    }

    //! Sets the active color (color, that can be drawn)
    void setActive(int state) {
        if (state > 0) activeState = (State)state;
    }

public:
    //! Constructor
    CommonGraphicsView(int amountWidth, int amountHeight, int width, int height);

    //! Sets state of cell in graphics view
    void setRect(Dimension x, Dimension y, State s);

    //! Change color for some state
    void changeColor(State state);

    //! Sets color for given state
    void setColor(State s, QColor c);

    //! Removes all colors and cleans lattice
    void removeAllColors();

    //! Returns color for given state
    QColor getColor(State state) {
        return color[state];
    }

protected:
    QVector<QColor> color;

    void mouseMoveEvent(QMouseEvent* event);    
    void mousePressEvent(QMouseEvent* event);    

private:
    State activeState;

};

#endif // COMMONGRAPHICSVIEW_H
