#include "player.h"

void Player::takeDamage(int damage) {
    this->hp -= damage;
    if (this->hp < 0) hp = 0;
}

void Player::heal(int amount) {
    this->hp += amount;
    if (this->hp > max_hp) this->hp = max_hp;
}

void Player::drawWeapon(int x, int y) {
    if (has_weapon == true) {
        weapon.setPosition(x, y);
        weapon.draw();

        int x_aux = x;
        x_aux += 6;
        for(auto& card : cards_defeated) {
            card.setPosition(x_aux, y + 1);
            card.draw();
            x_aux += 2;
        }
        // Draw controls
        attron(COLOR_PAIR(3));
        mvprintw(y + 10, x + 4, "[F]");
        attroff(COLOR_PAIR(3));
    }

}

bool Player::attack(Card card) {
    if (has_weapon == true) {
        int card_value = card.getValue();
        int weapon_value = weapon.getValue();
        if (last_enemy_value == -1) {
            int damage = card_value - weapon_value;
            if (damage > 0) {
                this->takeDamage(damage);
            }
            last_enemy_value = card_value;
            cards_defeated.push_back(card);
            return true;
        } else if (card_value < last_enemy_value) {
            int damage = card_value - weapon_value;
            if (damage > 0) {
                this->takeDamage(damage);
            }
            last_enemy_value = card_value;
            cards_defeated.push_back(card);
            return true;
        }
    }
    return false;
}

void Player::equipWeapon(Card& weapon) {
    if (this->weapon.getIsSelected()) {
        weapon.setIsSelected(true);
    }
    this->weapon = weapon;  // se hace copia
    this->has_weapon = true;
    last_enemy_value = -1;
    cards_defeated.clear();
}

void Player::setUseWeapon(bool use) {
    use_weapon = use;
    weapon.setIsSelected(use);
}

bool Player::playCard(Card card, bool use_weapon) {
    last_card_played = card;
    string symbol = card.getSuitSymbol();
    if (symbol == "H") {
        this->heal(card.getValue());
        return true;
    }
    else if (symbol == "D") {
        this->equipWeapon(card);
        return true;
    }
    else if (symbol == "C" || symbol == "S") {
        if (use_weapon) {
            return attack(card);
        }
        else {
            this->takeDamage(card.getValue());
            return true;
        }
    }
    return false;
}

int Player::getWinScore() {
    int score = hp;

    if (hp == max_hp && last_card_played.getSuitSymbol() == "H") score += last_card_played.getValue();

    return score;
}