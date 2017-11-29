#pragma once
#include "../frontend_src/stdafx.h"
#include <stdlib.h>
#include <iostream>

#include <..\scugog_project\src\card.h>

using namespace std;

// Exception
CardException::CardException(const string& message) : message(message) {}
string& CardException::what() { return message; }


// Constructor
Card::Card() {}
Card::Card(int id_value, int attack_value, int defense_value, int power_value, int ability_value, int cost_value, string image_value, string description_value, string name_value) {
	id = id_value;
	attack = attack_value;
	defense = defense_value;
	power = power_value;
	ability = ability_value;
	cost = cost_value;
	image = image_value;
	description = description_value;
	name = name_value;

	sf::Texture picture;
	sf::Font font;
}


// Accessors
int Card::get_id() {
	return id;
}
int Card::get_attack() {
	return attack;
}
int Card::get_defense() {
	return defense;
}
int Card::get_power() {
	return power;
}
int Card::get_ability() {
	return ability;
}
int Card::get_cost() {
	return cost;
}
string Card::get_image() {
	return image;
}
string Card::get_description() {
	return description;
}
string Card::get_name() {
	return name;
}


// Set Functions
void Card::set_attack(int attack_value) {
	attack = attack_value;
}
void Card::set_defense(int defense_value) {
	defense = defense_value;
}
void Card::set_power(int power_value) {
	power = power_value;
}
void Card::set_cost(int cost_value) {
	cost = cost_value;
}

// Draw Card Function
pair<sf::Sprite, sf::Text> Card::draw_card(int position_x, int position_y) {
	if (!picture.loadFromFile("../scugog_project/resources/images/card_pictures/" + image)) {
		cout << "error loading file" << endl;
	}
	sf::Sprite card(picture);
	card.setPosition(sf::Vector2f(position_x, position_y));

	// Texts
	if (!font.loadFromFile("../scugog_project/resources/fonts/ARLRDBD.ttf")) {
		cout << "error loading file" << endl;
	}

	sf::Text defense_text;
	defense_text.setFont(font);
	defense_text.setString("");
	if (defense != 0) {
		defense_text.setString(to_string(defense));
	}
	defense_text.setCharacterSize(24);
	defense_text.setFillColor(sf::Color::Black);
	defense_text.setStyle(sf::Text::Style::Italic);
	defense_text.setPosition(sf::Vector2f(position_x + 30, position_y + 122));

	pair <sf::Sprite, sf::Text> sprites = { card, defense_text };
	return sprites;

}

// Stream Overloading
ostream& operator<< (ostream& out, Card& card) {
	out << card.get_name() << endl;
	return out;
}