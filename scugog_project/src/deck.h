#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\card.h>

using namespace std;

class Deck {
public:
	// Constructors
	Deck();
	Deck(int deck_num); // Calls retrieve_cards()

	// Accessors
	int get_deck_num();
	int get_size(); // Returns the size of the deck

	// Other Functions
	Card access_card(int index); // provides access to a single card in the deck
	Card pop_card(int index); // remove a single card from the deck and return that card
	void retrieve_cards(); // Extracts all the cards associated to this deck from the database (calls add_card_to_deck)
	void add_card_to_deck(Card); // adds a single card to the deck, i.e. to cards

private:
	int deck_num;
	vector<Card> cards;
};

// Basic Exception Class
class DeckException : public exception {
public:
	DeckException(const string& message);
	string& what();

private:
	string message;
};