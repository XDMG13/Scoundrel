#include "card.h"

Card::Card(int value, string number, string suit_symbol, int height, int width,
           string border1, string border2,
           string corner1, string corner2, string corner3, string corner4,
           string background)
    : value(value), number(number), suit_symbol(suit_symbol), x(0), y(0),
      border1(border1), border2(border2),
      corner1(corner1), corner2(corner2),
      corner3(corner3), corner4(corner4),
      background(background)
{
    if (height % 2 == 0) height -= 1;
    if (width % 2 == 0) width -= 1;
    this->height = height;
    this->width  = width;
}

Card::~Card() {}

void Card::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Card::draw() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int color = 0; // 0 = default
            char ch = background[0]; // predeterminado

            // Bordes horizontales
            if (i == 0 || i == height - 1) {
                ch = border1[0];
                if (is_selected) color = 3;
            }
            // Bordes verticales
            else if (j == 0 || j == width - 1) {
                ch = border2[0];
                if (is_selected) color = 3;
            }
            // Número arriba izquierda
            else if (i == 1 && j == 1) {
                if (number.length() > 1) { // "10"
                    color = (suit_symbol == "H" || suit_symbol == "D") ? 2 : (is_selected ? 3 : 0);
                    if (color != 0) attron(COLOR_PAIR(color));
                    mvaddch(y + i, x + j, number[0]);
                    mvaddch(y + i, x + j + 1, number[1]);
                    if (color != 0) attroff(COLOR_PAIR(color));
                    j++; // saltamos la siguiente posición
                    continue;
                } else {
                    ch = number[0];
                    if (suit_symbol == "H" || suit_symbol == "D") color = 2;
                }
            }
            // Número abajo derecha
            else if (i == height - 2 && j == width - 3) { // ajustado para "10"
                if (number.length() > 1) {
                    color = (suit_symbol == "H" || suit_symbol == "D") ? 2 : (is_selected ? 3 : 0);
                    if (color != 0) attron(COLOR_PAIR(color));
                    mvaddch(y + i, x + j, number[0]);
                    mvaddch(y + i, x + j + 1, number[1]);
                    if (color != 0) attroff(COLOR_PAIR(color));
                    j++; // saltamos la siguiente posición
                    continue;
                } else {
                    ch = number[0];
                    if (suit_symbol == "H" || suit_symbol == "D") color = 2;
                }
            }
            // Palo
            else if (i == height / 2 && j == width / 2) {
                ch = suit_symbol[0];
                if (suit_symbol == "H" || suit_symbol == "D") color = 2;
            }
            // Relleno
            else {
                ch = background[0];
                if (is_selected) color = 3;
            }

            if (color != 0) attron(COLOR_PAIR(color));
            mvaddch(y + i, x + j, ch);
            if (color != 0) attroff(COLOR_PAIR(color));
        }
    }

    // Esquinas
    struct Corner { int dx, dy; char c; };
    Corner corners[4] = {
        {0, 0, corner1[0]},
        {width-1, 0, corner2[0]},
        {0, height-1, corner3[0]},
        {width-1, height-1, corner4[0]}
    };
    for (int k = 0; k < 4; k++) {
        if (is_selected) attron(COLOR_PAIR(3));
        mvaddch(y + corners[k].dy, x + corners[k].dx, corners[k].c);
        if (is_selected) attroff(COLOR_PAIR(3));
    }
}
