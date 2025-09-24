#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <list>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "layout.h"

using namespace std;

#define MAX_LIFE 20

void init_curses() {
    initscr();
    noecho();
    // nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();

        init_color(COLOR_BLACK, 0, 0, 0);
        init_color(COLOR_WHITE, 1000, 1000, 1000);
        init_color(COLOR_BLACK, 0, 0, 0);
        init_color(COLOR_RED, 1000, 0, 0);
        init_color(COLOR_YELLOW, 1000, 1000, 0);

        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);

        bkgd(COLOR_PAIR(1));
    }
}

void draw(int x, int y, char* str) {
    mvprintw(y, x, "%s", str);
}

void loose(int score){

    while (true) {

        clear();
        box(stdscr, 0, 0);

        // Title
        int start_x = 26;
        int start_y = 3;

        mvprintw(start_y + 0, start_x, " #####     ##   #      #  #######      ######  ##     ## ####### ##### ");
        mvprintw(start_y + 1, start_x, "##    ##  #  #  ###   ### ##          ##    ## ##     ## ##      #    #");
        mvprintw(start_y + 2, start_x, "##       #    # #### #### ##          #      # ##     ## ##      #    #");
        mvprintw(start_y + 3, start_x, "##  ###  ###### ## ### ## #######     #      #  ##   ##  ####### ######");
        mvprintw(start_y + 4, start_x, "##    ## #    # ##     ## ##          #      #   ## ##   ##      #  ## ");
        mvprintw(start_y + 5, start_x, "##    ## #    # ##     ## ##          ##    ##    ###    ##      #   ##");
        mvprintw(start_y + 6, start_x, " ######  #    # ##     ## #######      ######      #     ####### #    #");

        attroff(COLOR_PAIR(2));
        attron(COLOR_PAIR(2));
        mvprintw(22, 57, "SCORE: %d", score);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
        mvprintw(26, 55, "Q-Return to Menu");
        attroff(COLOR_PAIR(3));

        refresh();

        char ch = getch();
        if (ch == 'q' || ch == ' ') break;

        clear();
    }
}

void win(int score) {

    while (true) {

        clear();
        box(stdscr, 0, 0);

        // Title
        int start_x = 15;
        int start_y = 3;

        mvprintw(start_y + 0, start_x, "#     #  ######  #       #     #           #  ######  ##    ##");
        mvprintw(start_y + 1, start_x, " #   #  ##    ## #       #     #           # ##    ## ###   ##");
        mvprintw(start_y + 2, start_x, "  # #   #      # #       #     #     #     # #      # ####  ##");
        mvprintw(start_y + 3, start_x, "   #    #      # #       #     #     #     # #      # ## ## ##");
        mvprintw(start_y + 4, start_x, "   #    #      # #       #      #   # #   #  #      # ##  ####");
        mvprintw(start_y + 5, start_x, "   #    ##    ##  #     #        #  # #  #   ##    ## ##   ###");
        mvprintw(start_y + 6, start_x, "   #     ######    #####          ##   ##     ######  ##    ##");

        mvprintw(22, 55, "SCORE: %d", score);

        attron(COLOR_PAIR(3));
        mvprintw(26, 55, "Q-Return to Menu");
        attroff(COLOR_PAIR(3));

        refresh();

        char ch = getch();
        if (ch == 'q' || ch == ' ') break;

        clear();
    }
}

void game() {
    char ch;

    // Create a deck of cards
    int deck_x = 15; // X position for the deck
    int deck_y = 4; // Y position for the deck
    int deck_height = 9; // Height of the deck
    int deck_width = 11; // Width of the deck

    Deck deck(deck_x, deck_y, deck_height, deck_width);
    deck.shuffle();

    int x_card1 = 40; // X position for the first room card
    int y_card1 = 4; // Y position for the room cards
    int card_space = 18; // Space between room cards

    // Weapon Card
    int x_weapon_card = 20; // X position for the weapon card
    int y_weapon_card = 17; // Y position for the weapon card

    // Player
    Player player(MAX_LIFE);

    // Draw the layout
    drawLayout(deck, player);

    // Draw the deck
    deck.drawDeck();

    while(true) {

        if (deck.getNumCards() == 0 && deck.getCardsInRoom() == 0) {
            win(player.getWinScore());
            break;
        }
        else if (player.getHp() == 0) {
            loose(deck.getLooseScore());
            break;
        }

        ch = getch();
        if (ch == 'f') {
            player.setUseWeapon(!player.getUseWeapon());
        }
        if (ch == 'r' && !deck.getRerolled()) {
            // Reroll room
            deck.rerollRoomCards();
        }
        else if (ch == ' ' && deck.getNumCards() == 44 && deck.getRoomCards().size() == 0) {
            // Draw initial room cards
            deck.generateRoomCards();
            deck.setRerolled(false);
        } else if (ch == ' ' && deck.getCardsInRoom() <= 1) { // Draw a room
            deck.drawRoomCards();
            deck.setRerolled(false);
        } else if ((ch == '1' && (deck.getCardsInRoom() > 1)) || (deck.getNumCards() == 0 && deck.getCardsInRoom() > 0)) {
            if (player.playCard(deck.getRoomCards()[0], player.getUseWeapon())) {
                deck.removeRoomCard(0); // Remove the first card
            }
        } else if (ch == '2' && deck.getCardsInRoom() > 1) {
            if (player.playCard(deck.getRoomCards()[1], player.getUseWeapon())) {
                deck.removeRoomCard(1); // Remove the second card
            }
        } else if (ch == '3' && deck.getCardsInRoom() > 2) {
            if (player.playCard(deck.getRoomCards()[2], player.getUseWeapon())) {
                deck.removeRoomCard(2); // Remove the third card
            }
        } else if (ch == '4' && deck.getCardsInRoom() > 3) {
            if (player.playCard(deck.getRoomCards()[3], player.getUseWeapon())) {
                deck.removeRoomCard(3); // Remove the fourth card
                deck.setRerolled(false);
            }
        } else if (ch == 'q') {
            break; // Salir con 'q'
        }
        clear();

        // Draw the layout
        drawLayout(deck, player);

        // Draw the room cards
        int x_card = x_card1;
        for(auto& card : deck.getRoomCards()) {
            card.setPosition(x_card, y_card1);
            card.draw();
            x_card += card_space; // Espacio entre cartas
        }

        // Draw weapon
        player.drawWeapon(x_weapon_card, y_weapon_card);

        // Draw the deck
        deck.drawDeck();

        refresh();
        napms(10);
    }

}

void instructions() {

    while (true) {

        clear();
        box(stdscr, 0, 0);

        // Title
        int start_x = 15;
        int start_y = 3;

        mvprintw(start_y + 0,  start_x, "Scoundrel is a single player rogue-like card game for use with a standard deck of playing cards.");
        mvprintw(start_y + 1,  start_x, "It was developed by Zach Gage and Kurt Bieg.");
        mvprintw(start_y + 3,  start_x, "All Jokers, red face cards, and red aces are removed from the deck. The remaining cards serve as");
        mvprintw(start_y + 4,  start_x, "monsters (spades and clubs), weapons (diamonds), and health potions (hearts) valued from 2-14");
        mvprintw(start_y + 5,  start_x, "(with face cards being valued 11-14). The rooms of the dungeon are created by laying out cards in");
        mvprintw(start_y + 6,  start_x, "groups of four. Progress is made through the dungeon by resolving three of the four dungeon cards");
        mvprintw(start_y + 7,  start_x, "in each room. The fourth card serves as the foundation for a new room. Rooms can be deferred if");
        mvprintw(start_y + 8,  start_x, "needed, but never twice in a row - and the player will eventually need to come back to deferred rooms.");
        mvprintw(start_y +10,  start_x, "Weapons may be equipped to attack multiple monsters, as long as each defeated monster is of lower");
        mvprintw(start_y +11,  start_x, "value than the last monster defeated with that same weapon. To attack a monster of higher value,");
        mvprintw(start_y +12,  start_x, "a new weapon must be equipped. Monsters can also always be attacked barehanded, but this depletes");
        mvprintw(start_y +13,  start_x, "the player's health for the full value of the monster. Health potions may be used to recover life");
        mvprintw(start_y +14,  start_x, "points up to the maximum starting value of 20. Playing a second potion in succession nullifies the");
        mvprintw(start_y +15,  start_x, "effect of the second potion.");
        mvprintw(start_y +17,  start_x, "The game ends in a loss when life points reach zero or in a victory if the player manages to clear");
        mvprintw(start_y +18,  start_x, "all rooms of the dungeon.");

        attron(COLOR_PAIR(3));
        mvprintw(26, 55, "Q-Return to Menu");
        attroff(COLOR_PAIR(3));

        refresh();

        char ch = getch();
        if (ch == 'q' || ch == ' ' || ch == '\n') break;

        clear();
    }
}

void menu() {

    int op = 1;

    while (true) {

        clear();
        box(stdscr, 0, 0);

        // Title
        int start_x = 33;
        int start_y = 5;
        mvprintw(start_y + 0, start_x, " ####  ####  ###  #   # #   # ####  ####  ##### #    ");
        mvprintw(start_y + 1, start_x, "#     #     #   # #   # ##  # #   # #   # #     #    ");
        mvprintw(start_y + 2, start_x, "#     #     #   # #   # # # # #   # #   # #     #    ");
        mvprintw(start_y + 3, start_x, " ###  #     #   # #   # #  ## #   # ####  ##### #    ");
        mvprintw(start_y + 4, start_x, "    # #     #   # #   # #   # #   # # #   #     #    ");
        mvprintw(start_y + 5, start_x, "    # #     #   # #   # #   # #   # #  #  #     #    ");
        mvprintw(start_y + 6, start_x, "####   ####  ###   ###  #   # ####  #   # ##### #####");


        // Instructions
        if (op == 1) attron(COLOR_PAIR(3));
        mvprintw(18, 55, "0-Play");
        if (op == 1) attroff(COLOR_PAIR(3));

        if (op == 2) attron(COLOR_PAIR(3));
        mvprintw(20, 55, "1-How to Play");
        if (op == 2) attroff(COLOR_PAIR(3));

        if (op == 3) attron(COLOR_PAIR(3));
        mvprintw(22, 55, "Q-Exit Game");
        if (op == 3) attroff(COLOR_PAIR(3));

        refresh();

        int ch = getch();
        if (ch == 'w' || ch == KEY_UP) {
            op--;
            if (op == 0) op = 3;
        }
        else if (ch == 's' || ch == KEY_DOWN) {
            op++;
            if (op == 4) op = 1;
        }
        else if (ch == 'q') break;
        else if (ch == '1' || (op == 1 && (ch == '\n' || ch == ' '))) {
            clear();
            refresh();
            //endwin();
            game();

        }
        else if (ch == '2' || (op == 2 && (ch == '\n' || ch == ' '))) {
            clear();
            refresh();
            //endwin();
            instructions();
        }

        clear();
    }
}

int main(void) {

    srand(time(NULL));

    init_curses();
    
    menu();

    endwin();

    return 0;
}