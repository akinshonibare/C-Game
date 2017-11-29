#pragma once
#include <stdlib.h>
#include <iostream>
#include <random>

#include <..\scugog_project\src\environment.h>

using namespace std;

// Exception
EnvironmentException::EnvironmentException(const string& message) : message(message) {}
string& EnvironmentException::what() { return message; }

// Constructor
Environment::Environment() {

}
Environment::Environment(int num_of_players, vector<int> decks_chosen) {
	game_on = true;
	number_of_players = num_of_players;
	for (int num = 0; num < number_of_players; num++) {
		Player player(decks_chosen[num], num);
		players.push_back(player);
	}
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(0, number_of_players-1);
	current_player = distr(eng);
	field = { {}, {} };
}

// Accessors
bool Environment::get_game_on() {
	return game_on;
}

Player Environment::get_current_player() {
	return players[current_player];
}

vector<Player> Environment::get_players() {
	return players;
}

void Environment::putCardInPlace(Card card, int index) {
	field[current_player][index] = card;
}

// Other Functions
void Environment::change_turn() {
	if (current_player == 0) {
		current_player = 1;
	}
	else if (current_player == 1) {
		current_player = 0;
	}
}
void Environment::end_game() {
	game_on = false;
}

vector<vector<Card>> Environment::getField() {
	return field;
}

Player Environment::get_current_opponent() {
	int opponent = (current_player + 1) % 2;
	return players[opponent];
}