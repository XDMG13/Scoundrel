#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <list>
#include <string>
#include <curses.h>
#include <algorithm>
#include <random>
#include "card.h"

using namespace std;

class Deck {
private:
    int x;            // posición X
    int y;            // posición Y
    int height;       // altura
    int width;        // anchura
    int num_total_cards;
    std::list<Card> cards;
    bool is_selected = false;
    bool rerolled = true;
    vector<Card> room_cards;

    std::list<Card> drawn_cards; // Cards that have been drawn

public:
    // Constructor
    Deck(int x, int y, int height, int width);

    // Mezclar
    void shuffle();

    // Sacar carta
    void drawCard();

    // Draw Deck
    void drawDeck();

    // Devolver carta
    void returnCard(const Card& card);

    // Número de cartas
    int getNumCards() const { return cards.size(); }

    int getNumTotalCards() const { return num_total_cards; }

    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void setIsSelected(bool selected) { is_selected = selected; }

    bool getIsSelected() const { return is_selected; }

    bool isColided(int px, int py) const {
        return (px >= x && px < x + width && py >= y && py < y + height);
    }

    bool getRerolled() const { return rerolled; }

    void setRerolled(bool val) { rerolled = val; }

    vector<Card> getRoomCards() const { return room_cards; }

    void generateRoomCards();

    void rerollRoomCards();

    void emptyRoomCards() { room_cards.clear(); }

    int getCardsInRoom() const { return room_cards.size(); }

    void drawRoomCards();

    void removeRoomCard(int index) { if (index >= 0 && index < room_cards.size()) room_cards.erase(room_cards.begin() + index); }

    int getLooseScore();

};


#endif
