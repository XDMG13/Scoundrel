#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <curses.h>
#include <string>

using namespace std;

class Card {
private:
    int value;        // 2-14 (2-10, 11=J, 12=Q, 13=K, 14=A)
    string number; 
    string suit_symbol;
    int x;            // posición X
    int y;            // posición Y
    int height;       // altura
    int width;        // anchura
    string border1;
    string border2;
    string corner1;
    string corner2;
    string corner3;
    string corner4;
    string background;
    bool is_selected = false;

public:
    // Constructors

    Card() : value(0), suit_symbol(" "), number(" "), height(0), width(0),
      border1(" "), border2(" "), corner1(" "), corner2(" "), corner3(" "), corner4(" "), background(" ") {}


    Card(int value, string number, string suit_symbol, int height, int width,
         string border1, string border2,
         string corner1, string corner2, string corner3, string corner4,
         string background);

    // Destructor
    ~Card();

    // Setters de posición
    void setPosition(int x, int y);

    // Dibujar
    void draw();

    void setIsSelected(bool selected) { is_selected = selected; }

    bool getIsSelected() const { return is_selected; }

    string getSuitSymbol() const { return suit_symbol; }

    int getValue() const { return value; }
};

#endif
