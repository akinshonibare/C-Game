#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>
#include <vector>

#include <..\scugog_project\src\card.h>

using namespace std;

class Graveyard {
public:
	// Constructor
	Graveyard();

	// Other Functions
	void add_card_to_graveyard(Card); // adds a single card to the graveyard vector

private:
	vector<Card> graveyard;
};

// Basic Exception Class
class GraveyardException : public exception {
public:
	GraveyardException(const string& message);
	string& what();

private:
	string message;
};