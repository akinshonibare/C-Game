#pragma once
#include "..\scugog_project\src\player.h"
#include "..\scugog_project\src\card.h"
#include "..\scugog_project\src\deck.h"
#include "..\scugog_project\src\environment.h"
#include "..\scugog_project\src\graveyard.h"
// ALL OF THIS IS TODO STILL WORKING ON IT
class WalkthroughGame
{
public:
	Environment env; // may need to make this private and add getters
	WalkthroughGame(Environment env);
	WalkthroughGame();
	int Play(sf::RenderWindow& window);
	bool inCard(sf::Sprite crd, float mpx, float mpy);
	bool inText(sf::Text text, float mpx, float mpy);
	bool inGrave(sf::Sprite crd, float mpx, float mpy);
	int handleClicks(vector<sf::Sprite> clicks, vector<Card> cardClicks, int indexOne, int indexTwo);
	string handleError(int worked);
	bool inPerson(sf::Sprite crd, float mpx, float mpy);
	//Environment getEnvironment();
private:
	vector<pair<sf::Sprite, sf::Text>> hand;
	vector<pair<sf::Sprite, sf::Text>> f1;
	vector<pair<sf::Sprite, sf::Text>> f2;
	vector<Player> players;
	vector<vector<Card>> fields;
	vector<bool> h1Full;
	vector<bool> h2Full;
	vector<bool> f1Full;
	vector<bool> f2Full;
	vector<bool> clickable;
	int cardType;
	int secondClickType;
	//Environment env;
};
