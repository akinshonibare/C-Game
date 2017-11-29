#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\deck.h>
#include <..\scugog_project\src\graveyard.h>

using namespace std;

class Player {
public:
	// Default Constructor
	Player();
	// Constructor
	Player(int deck_number, int player_number);

	// Accessors
	Deck get_deck();
	int get_hp();
	vector<Card> get_hand();
	int Player::get_player_number();
	int get_current_resources();

	// Set Functions
	void set_hp(int hitpoints);
	void set_current_resources(int resources);

	// Other Functions
	void draw_card(); // draws a random card from whatever cards are still in the deck
	void add_card_to_hand(Card card); // adds a card to the player's hand
	Card remove_card_from_hand(int index);

private:
	int hitpoints;
	vector<Card> hand;
	Deck current_deck;
	int current_resources;
	int max_resources;
	int player_number;
};

// Basic Exception Class
class PlayerException : public exception {
public:
	PlayerException(const string& message);
	string& what();

private:
	string message;
};