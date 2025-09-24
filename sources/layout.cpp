#include "layout.h"

void drawBorders() {
    // Draw borders
    box(stdscr, 0, 0);

    attron(COLOR_PAIR(3));
    mvprintw(1, 1, " [Q] Quit");
    attroff(COLOR_PAIR(3));

}

void drawLifeArea(Player player) {
    int hp = player.getHp();
    int max_hp = player.getMaxHp();

    // Draw life area
    mvhline(24, 1, '#', 11);
    mvvline(25, 11, '#', 3);
    mvhline(28, 1, '#', 11);
    mvvline(25, 1, '#', 3);

    attron(COLOR_PAIR(2));
    if (hp >= 10) {
        mvprintw(26, 4, "%d/%d", hp, max_hp);
    } else {
        mvprintw(26, 4, " %d/%d", hp, max_hp);
    }
    attroff(COLOR_PAIR(2));
}

void drawLayout(Deck deck, Player player) {
    // Draw borders
    drawBorders();

    // Draw life area
    drawLifeArea(player);

    // Draw life area

    refresh();
}