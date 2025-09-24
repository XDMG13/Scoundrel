#include "deck.h"

// Constructor
Deck::Deck(int x, int y, int height, int width) {
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    num_total_cards = 44;
    cards = std::list<Card>();
    
    // Card attributes
    const char * suit_symbol1 = "H";
    const char * suit_symbol2 = "D";
    const char * suit_symbol3 = "S";
    const char * suit_symbol4 = "C";
    const char * number = "-";
    const char * border1 = "-";
    const char * border2 = "|";
    const char * corner1 = "+";
    const char * corner2 = "+";
    const char * corner3 = "+";
    const char * corner4 = "+";
    const char * background = " ";

    // Generate Hearts
    for (int i = 2; i <= 10; i++) {
        cards.push_back(Card(i, to_string(i).c_str(), suit_symbol1, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    }

    // Generate Diamonds
    for (int i = 2; i <= 10; i++) {
        cards.push_back(Card(i, to_string(i).c_str(), suit_symbol2, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    }

    // Generate Clubs
    cards.push_back(Card(14, "A", suit_symbol3, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    for (int i = 2; i <= 10; i++) {
        cards.push_back(Card(i, to_string(i).c_str(), suit_symbol3, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    }
    cards.push_back(Card(11, "J", suit_symbol3, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    cards.push_back(Card(12, "Q", suit_symbol3, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    cards.push_back(Card(13, "K", suit_symbol3, height, width, border1, border2, corner1, corner2, corner3, corner4, background));

    // Generate Spades
    cards.push_back(Card(14, "A", suit_symbol4, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    for (int i = 2; i <= 10; i++) {
        cards.push_back(Card(i, to_string(i).c_str(), suit_symbol4, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    }
    cards.push_back(Card(11, "J", suit_symbol4, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    cards.push_back(Card(12, "Q", suit_symbol4, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
    cards.push_back(Card(13, "K", suit_symbol4, height, width, border1, border2, corner1, corner2, corner3, corner4, background));
}

// Mezclar
void Deck::shuffle() {
    std::vector<Card> vec(cards.begin(), cards.end());

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vec.begin(), vec.end(), g);

    cards.assign(vec.begin(), vec.end());
}

// Sacar carta
void Deck::drawCard() {
    if (cards.empty()) room_cards.push_back(Card(0, "#", "#", 9, 11, "-", "|", "+", "+", "+", "+", "#")); // Blank card if no cards left
    Card top = cards.front();
    cards.pop_front();

    drawn_cards.push_back(top);

    room_cards.push_back(top);
}

// Draw Deck
void Deck::drawDeck() {
    Card placeholder = Card(0, "#", "#", 9, 11, "-", "|", "+", "+", "+", "+", "#");
    placeholder.setPosition(x, y);
    placeholder.draw();

    if (getNumCards() >= getNumTotalCards() / 3 * 2) {
        mvprintw(y + 9, x + 1, "+---------+");
        mvprintw(y + 1, x + 11, "+");
        mvvline(y + 2, x + 11, '|', 7);

        mvprintw(y + 10, x + 2, "+---------+");
        mvprintw(y + 2, x + 12, "+");
        mvvline(y + 3, x + 12, '|', 7);
    } else if (getNumCards() >= getNumTotalCards() / 3) {
        mvprintw(y + 9, x + 1, "+---------+");
        mvprintw(y + 1, x + 11, "+");
        mvvline(y + 2, x + 11, '|', 7);
    }

    // Draw controls
    attron(COLOR_PAIR(3));
    mvprintw(y - 2, x, "[Spacebar]");
    if (!getRerolled()) {
        mvprintw(7, 5, "Reroll");
        mvprintw(8, 7, "[R]");
    }
    int num_cards = getRoomCards().size();
    if (num_cards > 0) mvprintw(13, 44, "[1]");
    if (num_cards > 1) mvprintw(13, 62, "[2]");
    if (num_cards > 2) mvprintw(13, 80, "[3]");
    if (num_cards > 3) mvprintw(13, 98, "[4]");
    attroff(COLOR_PAIR(3));


}

// Devolver carta
void Deck::returnCard(const Card& card) {
    cards.push_back(card);
}

void Deck::generateRoomCards() {
    room_cards.clear();
    for (int i = 0; i < 4 && !cards.empty(); i++) {
        drawCard();
    }
}

void Deck::rerollRoomCards() {
    for (auto& card : room_cards) {
        returnCard(card);
    }
    room_cards.clear();
    generateRoomCards();
    rerolled = true;
}

void Deck::drawRoomCards() {
    for (int i = 0; i < 3 && !cards.empty(); i++) {
        drawCard();
    }
}

int Deck::getLooseScore() {
    int score = 0;

    for (const auto& card : cards) {
        if (card.getSuitSymbol() == "S" || card.getSuitSymbol() == "C") score -= card.getValue();
    }

    for (const auto& card : getRoomCards()) {
        if (card.getSuitSymbol() == "S" || card.getSuitSymbol() == "C") score -= card.getValue();
    }

    return score;
}
