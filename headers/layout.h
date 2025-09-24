#ifndef LAYOUT_H
#define LAYOUT_H

#include <iostream>
#include <curses.h>
#include "card.h"
#include "deck.h"
#include "player.h"

using namespace std;

// Function to draw the borders of the layout
void drawBorders();

// Function to draw the life area
void drawLifeArea(Player player);

// Function to draw the layout of the game
void drawLayout(Deck deck, Player player);

#endif