#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "card.h"
#include <list>

class Player {
private:
    int hp;
    int max_hp;
    Card weapon;
    int last_enemy_value;
    std::list<Card> cards_defeated;
    bool use_weapon;
    bool has_weapon;
    Card last_card_played;

public:
    Player(int max_hp) : hp(max_hp), max_hp(max_hp) {
        last_enemy_value = -1;
        use_weapon = false;
        has_weapon = false;
    }

    ~Player() {}

    int getHp() const { return hp; }
    
    int getMaxHp() const { return max_hp; }

    void takeDamage(int damage);

    void heal(int amount);

    void equipWeapon(Card &weapon);

    bool attack(Card card);

    void drawWeapon(int x, int y);

    bool playCard(Card card, bool use_weapon);

    bool getUseWeapon() { return use_weapon; }

    void setUseWeapon(bool use);

    int getWinScore();
    
};

#endif
