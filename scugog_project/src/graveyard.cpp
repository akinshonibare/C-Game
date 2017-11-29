#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <..\scugog_project\src\graveyard.h>

using namespace std;

// Exception
GraveyardException::GraveyardException(const string& message) : message(message) {}
string& GraveyardException::what() { return message; }

// Constructor
Graveyard::Graveyard() {}

// Set Functions
void Graveyard::add_card_to_graveyard(Card card_value) {
	graveyard.push_back(card_value);
}

