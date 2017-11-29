#pragma once
#include <stdlib.h>
#include <iostream>
#include <random>

#include <..\scugog_project\src\player.h>
#include <..\scugog_project\src\graveyard.h>


using namespace std;

// Exception
PlayerException::PlayerException(const string& message) : message(message) {}
string& PlayerException::what() { return message; }

// Default Constructor
Player::Player() {
	Deck deck_of_cards = NULL;
	player_number = -1;

}
// Constructor
Player::Player(int deck_number, int player_numb) {
	Deck deck_of_cards(deck_number);
	current_deck = deck_of_cards;
	player_number = player_numb;
	for (int i = 0; i < 6; i++) {
		draw_card();
	}
	hitpoints = 40;
	current_resources = 3;
}

// Accessors
Deck Player::get_deck() {
	return current_deck;
}
vector<Card> Player::get_hand() {
	return hand;
}
int Player::get_hp() {
	return hitpoints;
}
int Player::get_player_number() {
	return player_number;
}
int Player::get_current_resources() {
	return current_resources;
}

// Set Functions
void Player::set_hp(int hp_value) {
	hitpoints = hp_value;
}
void Player::set_current_resources(int resources) {
	current_resources = resources;
}

// Other Functions
void Player::draw_card() {
	int size_of_deck = current_deck.get_size() - 1;
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0, size_of_deck);
	if (size_of_deck > 1) {
		int card_num = distr(eng);
		Card card_drew = current_deck.pop_card(card_num);
		add_card_to_hand(card_drew);
	}
}

void Player::add_card_to_hand(Card card_value) {
	hand.push_back(card_value);
}

Card Player::remove_card_from_hand(int index) {
	Card card_return = hand.at(index);
	hand.erase(hand.begin()+index);
	return card_return;
}
