#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <boost/shared_ptr.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <..\scugog_project\src\deck.h>

using namespace std;

// Exception
DeckException::DeckException(const string& message) : message(message) {}
string& DeckException::what() { return message; }

// Constructor
Deck::Deck() {
}
Deck::Deck(int deck_number) {
	deck_num = deck_number;
	retrieve_cards();
}


// Accessor
int Deck::get_deck_num() {
	return deck_num;
}
int Deck::get_size() {
	return cards.size();
}
Card Deck::access_card(int index) {
	if (index >= get_size()) {
		throw DeckException("Index is not allowed because it falls outside the size of the deck.");
	} else {
		return cards[index];
	}
}

// Set Functions
void Deck::add_card_to_deck(Card card_value) {
	cards.push_back(card_value);
}

Card Deck::pop_card(int index) {
	if (index >= get_size()) {
		throw DeckException("Index is not allowed because it falls outside the size of the deck.");
	}
	else {
		Card requested_card = cards[index];
		cards.erase(cards.begin() + index);
		return requested_card;
	}
}

void Deck::retrieve_cards() {
	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::ResultSet *res;
		sql::PreparedStatement *pstmt;
		sql::ResultSet *res2 = nullptr;
		sql::PreparedStatement *pstmt2 = nullptr;
		/* Create a connection */
		//tcp://138.197.148.75
		//guest
		//guestUser
		driver = get_driver_instance();
		//con = driver->connect("tcp://192.168.2.96:3306", "guest", "cisc320");
		con = driver->connect("tcp://70.54.133.31:3306", "guest", "cisc320");
		/* Connect to the MySQL test database */
		con->setSchema("CISC320");
		/* Select in ascending order */
		//pstmt = con->prepareStatement("SELECT * FROM card WHERE idcard IN(0,1,2)");
		pstmt = con->prepareStatement("SELECT * FROM deck WHERE iddeck = " + std::to_string(get_deck_num()));
		res = pstmt->executeQuery();



		/* Fetch in reverse = descending order! */
		//res->afterLast();
		while (res->next()) {
			pstmt2 = con->prepareStatement("SELECT * FROM card WHERE idcard = " + std::to_string(res->getInt("card")));
			res2 = pstmt2->executeQuery();
			while (res2->next()) {
				Card test(res2->getInt("idcard"), res2->getInt("attack"), res2->getInt("defense"), res2->getInt("power"), res2->getInt("ability"), res2->getInt("cost"), res2->getString("image"), res2->getString("description"), res2->getString("name"));
				add_card_to_deck(test);
			}
		}
		delete pstmt2;
		delete res2;
		delete res;
		delete pstmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}