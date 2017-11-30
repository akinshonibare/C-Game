#include "stdafx.h"
#include "PlayGame.h"
#include <random>
#include "Instructions.h"

PlayGame::PlayGame() {

}
PlayGame::PlayGame(Environment enviro) {
	env = enviro;
	cardType = -1;
	secondClickType = -1;
	players = enviro.get_players();
	fields = enviro.getField();
	abilities = { {},{} };
}

// Return 0 for player 1 win		
// Return 1 for player 2 win		
// Return -1 for Resource error		
// Return -2 for closed window
int PlayGame::Play(sf::RenderWindow & renderWindow)
{
	sf::Texture texture, texture2, card, money, deck1, deck2, cBoard, button, oLine;
	int deck1Index = players[0].get_deck().get_deck_num();
	int deck2Index = players[1].get_deck().get_deck_num();
	//cout << deck1Index << endl;
	//cout << deck2Index << endl;
	sf::Font font;
	// load images needed
	if (!font.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}


	// =========================================================================================================================================================================================================
	sf::Text instructions_text, exit_text;
	instructions_text.setFont(font);
	instructions_text.setString("INSTRUCTIONS");
	instructions_text.setCharacterSize(50);
	instructions_text.setFillColor(sf::Color::Black);
	instructions_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> instructions_text_size = instructions_text.getGlobalBounds();
	instructions_text.setPosition(sf::Vector2f(1700 - instructions_text_size.width / 2, 100  - instructions_text_size.height / 2));

	exit_text.setFont(font);
	exit_text.setString("EXIT");
	exit_text.setCharacterSize(50);
	exit_text.setFillColor(sf::Color::Black);
	exit_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> exit_text_size = exit_text.getGlobalBounds();
	exit_text.setPosition(sf::Vector2f(1700 - exit_text_size.width / 2, 150 - exit_text_size.height / 2));
	//==========================================================================================================================================================================================================
		

	if (texture.loadFromFile("../scugog_project/resources/images/bg3.jpg") != true)
	{
		return -1;
	}
	if (texture2.loadFromFile("../scugog_project/resources/images/loading_screen.jpg") != true)
	{
		return -1;
	}

	if (cBoard.loadFromFile("../scugog_project/resources/images/cuttingboard.png") != true)
	{
		return -1;
	}

	if (button.loadFromFile("../scugog_project/resources/images/button.png") != true)
	{
		return -1;
	}

	if (oLine.loadFromFile("../scugog_project/resources/images/outline.png") != true)
	{
		return -1;
	}

	if (card.loadFromFile("../scugog_project/resources/images/card_pictures/cardc.png") != true)
	{
		return -1;
	}
	if (money.loadFromFile("../scugog_project/resources/images/money.png") != true)
	{
		return -1;
	}
	if (deck1Index == 0) {
		if (deck1.loadFromFile("../scugog_project/resources/images/farmer.png") != true)
		{
			return -1;
		}
	}
	else {
		if (deck1.loadFromFile("../scugog_project/resources/images/farmer2.png") != true)
		{
			return -1;
		}
	}

	if (deck2Index == 0) {
		if (deck2.loadFromFile("../scugog_project/resources/images/farmer.png") != true)
		{
			return -1;
		}
	}
	else {
		if (deck2.loadFromFile("../scugog_project/resources/images/farmer2.png") != true)
		{
			return -1;
		}
	}
	// default
	string p1Name = "";
	string p2Name = "";
	if (deck1Index == 0) {
		p1Name = "Bert 1";
	}
	else {
		p1Name = "Franny 1";
	}
	if (deck2Index == 0) {
		p2Name = "Bert 2";
	}
	else {
		p2Name = "Franny 2";
	}
	Card dfltCard(0, 0, 0, 0, 0, 0, "cardc.png", "", "");
	sf::Sprite dflt(card);
	sf::Text dText;
	dText.setString("");
	pair <sf::Sprite, sf::Text> dfltPair;
	dfltPair = make_pair(dflt, dText);

	bool gameover = env.get_game_on();

	sf::Vector2u windowSize = renderWindow.getSize();
	sf::Text error;
	error.setFont(font);
	error.setString("");
	error.setCharacterSize(30);
	error.setFillColor(sf::Color::Blue);
	error.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> error_size = error.getGlobalBounds();
	error.setPosition(sf::Vector2f(windowSize.x / 2 - error_size.width / 2, 650));

	able.setFont(font);
	able.setCharacterSize(30);
	able.setFillColor(sf::Color::Blue);
	able.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> able_size = able.getGlobalBounds();
	able.setPosition(sf::Vector2f(windowSize.x / 2 - able_size.width / 2, 650));

	sf::Text p1Label;
	p1Label.setFont(font);
	p1Label.setCharacterSize(50);
	p1Label.setFillColor(sf::Color::Black);
	p1Label.setStyle(sf::Text::Style::Italic);

	sf::Text p2Label;
	p2Label.setFont(font);
	p2Label.setCharacterSize(50);
	p2Label.setFillColor(sf::Color::Black);
	p2Label.setStyle(sf::Text::Style::Italic);

	sf::Text switch_text;
	switch_text.setFont(font);
	switch_text.setString("Click anywhere when player is ready");
	switch_text.setCharacterSize(60);
	switch_text.setFillColor(sf::Color::Black);
	switch_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> switch_text_size = switch_text.getGlobalBounds();
	switch_text.setPosition(sf::Vector2f(windowSize.x - switch_text_size.width - 75, 100));

	sf::Text moneyText;
	moneyText.setFont(font);
	moneyText.setCharacterSize(60);
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setStyle(sf::Text::Style::Italic);
	sf::Sprite sprite_money(money);
	sprite_money.setScale(0.15f, 0.15f);
	sprite_money.setColor(sf::Color::Black);

	sf::Sprite p1Deck(deck1);
	sf::Sprite p2Deck(deck2);
	sf::Sprite cutBoard(cBoard);
	cutBoard.setPosition(1650, 500);
	sf::Sprite bbutton(button);
	bbutton.setPosition(1600, 325);
	sf::Sprite outline(oLine);

	sf::Sprite sprite(texture);
	sf::Sprite sprite2(texture2);

	sf::Event event;

	hand = { dfltPair, dfltPair , dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	f1 = { dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	f2 = { dfltPair , dfltPair , dfltPair , dfltPair , dfltPair };
	fields[0] = { dfltCard, dfltCard, dfltCard, dfltCard, dfltCard };
	fields[1] = { dfltCard, dfltCard, dfltCard, dfltCard, dfltCard };
	vector<pair<sf::Sprite, sf::Text>> temp;
	h1Full = { true, true, true, true, true, true, false };
	h2Full = { true, true, true, true, true, true, false };
	f1Full = { false, false, false, false, false };
	f2Full = { false, false, false, false, false };
	vector<bool> tempFull;
	int player1Click = 1;
	int player2Click = 2;
	int handCard = 3;
	int fieldCard = 4;
	int indexOne = -1;
	int indexTwo = -1;
	ableSet = -1;
	vector<sf::Sprite> clicks;
	vector<Card> cardClicks;
	// need to change these to match indexes later
	int player_turn = env.get_current_player().get_player_number();

	// intiate waiting screen with switching of player sprites
	bool initial_screen = true;
	while (initial_screen) {
		renderWindow.draw(sprite2);
		switch_text.setString("Click anywhere when player " + to_string(env.get_current_player().get_player_number() + 1) + " is ready");
		renderWindow.draw(switch_text);
		renderWindow.display();
		while (renderWindow.pollEvent(event)) {
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				initial_screen = false;
			}
			if (event.type == sf::Event::Closed) {
				return -2;
			}
		}
	}

	abilities[0] = { false, false, false, false, false };
	abilities[1] = { false, false, false, false, false };
	// essentially idea is to place cards as sprites
	// even if they aren't a game card and then use that so
	// that you can click them to move cards and attack
	while (gameover)
	{
		player_turn = env.get_current_player().get_player_number();
		int toReset1 = 0;
		int toReset2 = 0;
		bool player_turn_on = true;
		bool full_deck = true;
		bool start = true; // used to indicate if it is the start of a players turn
		clickable = { true, true, true, true, true };

		while (player_turn_on)
		{
			// intialize hand and field sprites as neccessary depending on who is playing
			if (start) {
				// draw cards at start of turn

				int tempIndex(0);
				for (int i = 0; i < size(h1Full); i++) {
					if (h1Full[i] == false) {
						full_deck = false;
						tempIndex = i;
						break;
					}
				}
				if (full_deck == false) {
					h1Full[tempIndex] = true;
					players[player_turn].draw_card();
				}
				start = false;

			}
			renderWindow.draw(sprite);
			for (int i = 0; i < size(players[player_turn].get_hand()); i++) {
				Card card_from_hand = players[player_turn].get_hand()[i];
				pair <sf::Sprite, sf::Text> card_graphic_pair = card_from_hand.draw_card(300 + 200 * i, 700);
				hand[i] = card_graphic_pair;
				renderWindow.draw(hand[i].first);
				renderWindow.draw(hand[i].second);
			}
			for (int i = 0; i < size(f1); i++) {
				if (env.get_current_player().get_player_number() == 0) {
					Card card_from_field1 = fields[0][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f1 = card_from_field1.draw_card(500 + 200 * i, 350);
					f1[i] = card_graphic_pair_f1;
					Card card_from_field2 = fields[1][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f2 = card_from_field2.draw_card(500 + 200 * i, 50);
					f2[i] = card_graphic_pair_f2;
					renderWindow.draw(f1[i].first);
					renderWindow.draw(f2[i].first);
					renderWindow.draw(f1[i].second);
					renderWindow.draw(f2[i].second);
				}
				else {
					Card card_from_field1 = fields[1][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f1 = card_from_field1.draw_card(500 + 200 * i, 350);
					f1[i] = card_graphic_pair_f1;
					Card card_from_field2 = fields[0][i];
					pair <sf::Sprite, sf::Text> card_graphic_pair_f2 = card_from_field2.draw_card(500 + 200 * i, 50);
					f2[i] = card_graphic_pair_f2;
					renderWindow.draw(f1[i].first);
					renderWindow.draw(f2[i].first);
					renderWindow.draw(f1[i].second);
					renderWindow.draw(f2[i].second);
				}
			}
			renderWindow.draw(bbutton);
			p1Label.setString(p1Name + "\n" + to_string(players[0].get_hp()));
			p2Label.setString(p2Name + "\n" + to_string(players[1].get_hp()));
			if (players[player_turn].get_player_number() == 0) { // p1 at bottom, p2 at top
				p1Label.setPosition(sf::Vector2f(80, 670));
				p2Label.setPosition(sf::Vector2f(80, 55));
			}
			else {
				p2Label.setPosition(sf::Vector2f(80, 670));
				p1Label.setPosition(sf::Vector2f(80, 55));
			}

			moneyText.setPosition(sf::Vector2f(120, 450));
			moneyText.setString(to_string(players[player_turn].get_current_resources()));
			sprite_money.setPosition(sf::Vector2f(50, 450));
			if (env.get_current_player().get_player_number() == 0) {
				p1Deck.setPosition(sf::Vector2f(50, 800));
				renderWindow.draw(p1Deck);
				p2Deck.setPosition(sf::Vector2f(50, 170));
				renderWindow.draw(p2Deck);
			}
			else {
				p2Deck.setPosition(sf::Vector2f(50, 800));
				renderWindow.draw(p2Deck);
				p1Deck.setPosition(sf::Vector2f(50, 170));
				renderWindow.draw(p1Deck);

			}
			renderWindow.draw(moneyText);
			renderWindow.draw(sprite_money);
			renderWindow.draw(p1Label);
			renderWindow.draw(p2Label);
			sf::Rect<float> error_size = error.getGlobalBounds();
			error.setPosition(sf::Vector2f(windowSize.x / 2 - error_size.width / 2 + 40, 650));
			renderWindow.draw(error);
			renderWindow.draw(cutBoard);
			if (!clicks.empty()) {
				renderWindow.draw(outline);
			}
			if (ableSet != player_turn) {
				sf::Rect<float> able_size = able.getGlobalBounds();
				able.setPosition(sf::Vector2f(windowSize.x / 2 - able_size.width / 2 + 60, 650));
				renderWindow.draw(able);
			}
			renderWindow.draw(instructions_text);
			renderWindow.draw(exit_text);
			renderWindow.display();
			while (renderWindow.pollEvent(event))
			{

				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					if (ableSet != player_turn) {
						able.setString("");
					}
					sf::Vector2i mousePos = sf::Mouse::getPosition();
					float horz = mousePos.x;
					float vert = mousePos.y;
					if (inCard(bbutton, horz, vert)) {
						player_turn_on = false;
						players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 2);
						env.change_turn();
					}
					if (inText2(instructions_text, horz, vert)) {
						Instructions instructions;
						int instructions_return = instructions.Show(renderWindow);
						if (instructions_return == -1) {
							return -1;
						}
					}
					if (inText2(exit_text, horz, vert)) {
						return -3;
					}
					if (clicks.empty()) {
						// first "card click event", i.e. who to move to field or attack with
						error.setString("");
						for (int i = 0; i < size(hand); i++) {
							if (inCard(hand[i].first, horz, vert) && h1Full[i]) {
								clicks.push_back(hand[i].first);
								hand[i].first.setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								cardClicks.push_back(players[player_turn].get_hand()[i]);
								cardType = handCard;
								indexOne = i;
								outline.setPosition(hand[i].first.getPosition().x - 11, hand[i].first.getPosition().y - 10);
							}
						}
						for (int i = 0; i < size(f1); i++) {
							if (inCard(f1[i].first, horz, vert) && f1Full[i]) {
								clicks.push_back(f1[i].first);
								f1[i].first.setColor(sf::Color(0, 255, 0));
								toReset1 = i;
								cardClicks.push_back(fields[player_turn][i]);
								outline.setPosition(f1[i].first.getPosition().x - 11, f1[i].first.getPosition().y - 10);
								cardType = fieldCard;
								indexOne = i;
							}
						}
					}
					else if (size(clicks) == 1) {
						// this is the second "card click events" i.e. who to attack
						if (cardType == 3) { //hand card 
							for (int i = 0; i < size(f1); i++) {
								if (inCard(f1[i].first, horz, vert) && !f1Full[i]) {
									secondClickType = fieldCard;
									f1[i].first.setColor(sf::Color(0, 255, 0));
									toReset2 = i;
									indexTwo = i;
								}
							}
							if (inGrave(cutBoard, horz, vert)) {
								secondClickType = 5;
							}
						}
						else {
							for (int i = 0; i < size(f2); i++) {
								if (inCard(f2[i].first, horz, vert) && f2Full[i]) {
									clicks.push_back(f2[i].first);
									f2[i].first.setColor(sf::Color(255, 0, 0));
									toReset2 = i;
									cardClicks.push_back(fields[(player_turn + 1) % 2][i]);
									secondClickType = fieldCard;
									indexTwo = i;
								}
							}
							if (inGrave(cutBoard, horz, vert)) {
								secondClickType = 5;
							}
							if (players[player_turn].get_player_number() == 0) {
								if (inPerson(p2Deck, horz, vert)) {
									secondClickType = player2Click;
								}
							}
							else {
								if (inPerson(p1Deck, horz, vert)) {
									secondClickType = player1Click;
								}
							}
							for (int i = 0; i < size(f1); i++) {
								if (inCard(f1[i].first, horz, vert)) {
									indexTwo = i;
									if (indexOne == indexTwo) {
										secondClickType = 6;
									}
								}
							}
						}
						//handle the cards clicked
						int worked = handleClicks(clicks, cardClicks, indexOne, indexTwo);
						error.setString(handleError(worked));
						//reset the colour of any clicked sprites
						hand[toReset1].first.setColor(sf::Color(255, 255, 255));
						f1[toReset1].first.setColor(sf::Color(255, 255, 255));
						f1[toReset2].first.setColor(sf::Color(255, 255, 255));
						f2[toReset2].first.setColor(sf::Color(255, 255, 255));
						// and the end of this need to clear the "clicks" vector
						clicks.clear();
						cardClicks.clear();
						// and set selectors back to -1 when done
						cardType = -1;
						secondClickType = -1;
						indexOne = -1;
						indexTwo = -1;
					}

				}

				if (event.type == sf::Event::Closed) {
					return -2;
				}
			}
			start = false;
			if (players[0].get_hp() <= 0) {
				env.end_game();
				gameover = env.get_game_on();
				return 1;
			}
			if (players[1].get_hp() <= 0) {
				env.end_game();
				gameover = env.get_game_on();
				return 0;
			}
		}
		// intiate waiting screen with switching of player sprites
		bool switching = true;
		while (switching) {
			renderWindow.draw(sprite2);
			switch_text.setString("Click anywhere when player " + to_string(env.get_current_player().get_player_number() + 1) + " is ready");
			renderWindow.draw(switch_text);
			renderWindow.display();
			while (renderWindow.pollEvent(event)) {
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					switching = false;
				}
				if (event.type == sf::Event::Closed) {
					return -2;
				}
			}
		}
		// swapping fields
		temp = f1;
		f1 = f2;
		f2 = temp;
		tempFull = f1Full;
		f1Full = f2Full;
		f2Full = tempFull;
		tempFull = h1Full;
		h1Full = h2Full;
		h2Full = tempFull;
	}

}

bool PlayGame::inText2(sf::Text text, float mpx, float mpy)
{
	sf::Rect<float> tsize = text.getGlobalBounds();
	float cd1L = tsize.left + 15;
	float cd1R = tsize.left + tsize.width + 15;
	float cd1T = tsize.top;
	float cd1B = tsize.top + tsize.height;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

bool PlayGame::inCard(sf::Sprite crd, float mpx, float mpy)
{
	sf::Rect<float> csize = crd.getGlobalBounds();
	float cd1L = csize.left;
	float cd1R = csize.left + csize.width;
	float cd1T = csize.top;
	float cd1B = csize.top + csize.height;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

bool PlayGame::inText(sf::Text text, float mpx, float mpy)
{
	sf::Rect<float> tsize = text.getGlobalBounds();
	float cd1L = tsize.left;
	float cd1R = tsize.left + tsize.width;
	float cd1T = tsize.top;
	float cd1B = tsize.top + tsize.height + 70;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

bool PlayGame::inGrave(sf::Sprite crd, float mpx, float mpy) {
	sf::Rect<float> csize = crd.getGlobalBounds();
	float cd1L = csize.left;
	float cd1R = csize.left + csize.width;
	float cd1T = csize.top;
	float cd1B = csize.top + csize.height + 100;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

bool PlayGame::inPerson(sf::Sprite crd, float mpx, float mpy) {
	sf::Rect<float> csize = crd.getGlobalBounds();
	float cd1L = csize.left;
	float cd1R = csize.left + csize.width;
	float cd1T = csize.top;
	float cd1B = csize.top + csize.height + 50;
	if ((mpx > cd1L) && (mpx < cd1R) && (mpy > cd1T) && (mpy < cd1B)) {
		return true;
	}
	return false;
}

int PlayGame::handleClicks(vector<sf::Sprite> clicks, vector<Card> cardClicks, int indexOne, int indexTwo) {
	if (secondClickType == 6) {
		return handleAbility(cardClicks[0], indexOne);
	}

	if (cardType == 4) {
		if (!clickable[indexOne]) {
			return 1;
		}
	}
	// 1 = player 1
	// 2 = player 2
	// 3 = hand card
	// 4 = field card
	// 5 = clicked on grave
	// 6 = ability use
	// -1 = no click
	sf::Texture card;
	// load images needed for default
	if (card.loadFromFile("../scugog_project/resources/images/cardcc.png") != true)
	{
		return -2;
	}
	// default 
	int player_turn = env.get_current_player().get_player_number();
	Card dfltCard(0, 0, 0, 0, 0, 0, "cardc.png", "", "");
	sf::Sprite dflt(card);
	sf::Text dText;
	dText.setString("");
	pair <sf::Sprite, sf::Text> dfltPair;
	dfltPair = make_pair(dflt, dText);
	//if no valid click for second object exit
	if (secondClickType == -1) {
		return 0;
	}

	//if moving a card from hand to field
	else if ((cardType == 3) && (secondClickType == 4)) {
		if (f1Full[indexTwo] || !h1Full[indexOne] || !clickable[indexTwo]) {
			return 1;
		}
		if (cardClicks[0].get_cost() <= players[player_turn].get_current_resources()) {
			pair<sf::Sprite, sf::Text> pair = cardClicks[0].draw_card(0, 0);
			f1[indexTwo] = pair;
			f1Full[indexTwo] = true;
			fields[player_turn][indexTwo] = cardClicks[0];
			for (int i = 0; i < size(hand); i++) {
				if (h1Full[i] == false) {
					h1Full[i - 1] = false;
				}
				else if (i == size(hand) - 1) {
					h1Full[6] = false;
				}
			}
			fields[player_turn][indexTwo] = players[player_turn].remove_card_from_hand(indexOne);
			players[player_turn].set_current_resources(players[player_turn].get_current_resources() - cardClicks[0].get_cost());
			clickable[indexTwo] = false;
			if (cardClicks[0].get_ability() == 3) {
				clickable[indexTwo] = true;
			}
		}
		else {
			return -1;
		}
	}
	//if attacking another card
	//if attacking another card
	else if ((cardType == 4) && (secondClickType == 4)) {
		clickable[indexOne] = false;
		cout << "attacking card" << endl;
		//get attack and defense values
		int opponent_defense = cardClicks[1].get_defense();
		int opponent_attack = cardClicks[1].get_attack();
		int player_defense = cardClicks[0].get_defense();
		int player_attack = cardClicks[0].get_attack();
		cout << "cClicks size: " << size(cardClicks) << endl;
		cout << "Player Def " << player_defense << endl;
		cout << "Opponent Def " << opponent_defense << endl;
		cout << "Player Atk " << player_attack << endl;
		cout << "Opponent Atk " << opponent_attack << endl;
		cardClicks[1].set_defense(opponent_defense - player_attack);


		cout << "Player Def " << cardClicks[1].get_defense() << endl;
		cout << "Opponent Def " << cardClicks[0].get_defense() << endl;
		if (cardClicks[1].get_defense() <= 0) {
			// enemy died
			fields[(player_turn + 1) % 2][indexTwo] = dfltCard;
			f2[indexTwo] = dfltPair;
			f2Full[indexTwo] = false;
			abilities[(player_turn + 1) % 2][indexTwo] = false;
			if (cardClicks[1].get_ability() == 5) {
				int health = players[player_turn].get_hp();
				players[player_turn].set_hp(health - 1);
			}
		}
		else {
			//enemy didn't die
			fields[(player_turn + 1) % 2][indexTwo] = cardClicks[1];
			f2[indexTwo] = fields[(player_turn + 1) % 2][indexTwo].draw_card(0, 0);
			f2Full[indexTwo] = true;
			if (opponent_defense > player_attack) {
				// you get attacked
				cardClicks[0].set_defense(player_defense - opponent_attack);
				if (cardClicks[0].get_defense() <= 0) {
					// you died
					fields[player_turn][indexOne] = dfltCard;
					f1[indexOne] = dfltPair;
					f1Full[indexOne] = false;
					clickable[indexOne] = true;
					abilities[player_turn][indexOne] = false;
					if (cardClicks[0].get_ability() == 5) {
						int health = players[(player_turn + 1) % 2].get_hp();
						players[(player_turn + 1) % 2].set_hp(health - 1);
					}
				}
				else {
					// you're hurt
					fields[player_turn][indexOne] = cardClicks[0];
					f1[indexOne] = fields[player_turn][indexOne].draw_card(0, 0);
					f1Full[indexOne] = true;
				}
			}
			else {
				// you didn't get attacked
				fields[player_turn][indexOne] = cardClicks[0];
				f1[indexOne] = fields[player_turn][indexOne].draw_card(0, 0);
				f1Full[indexOne] = true;
			}
		}
	}
	//if you attack the player
	else if ((secondClickType == 1) || (secondClickType == 2)) {
		if (!clickable[indexOne]) {
			return 1;
		}
		int toAttack = cardClicks[0].get_power();
		int currenthp = players[(player_turn + 1) % 2].get_hp();
		players[(player_turn + 1) % 2].set_hp(currenthp - toAttack);
		clickable[indexOne] = false;
	}
	else if ((cardType == 4) && (secondClickType == 5) && clickable[indexOne]) {
		fields[player_turn][indexOne] = dfltCard;
		f1[indexOne] = dfltPair;
		f1Full[indexOne] = false;
		abilities[player_turn][indexOne] = false;
		players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 1);
	}
	else if ((cardType == 3) && (secondClickType == 5)) {
		Card tempCard = players[player_turn].remove_card_from_hand(indexOne);
		players[player_turn].set_current_resources(players[player_turn].get_current_resources() + 1);
		for (int i = 0; i < size(hand); i++) {
			if (h1Full[i] == false) {
				h1Full[i - 1] = false;
			}
			else if (i == size(hand) - 1) {
				h1Full[6] = false;
			}
		}
	}
	//if you killed the opponent
	if (players[(player_turn + 1) % 2].get_hp() <= 0) {
		env.end_game();
	}

	return 3;
}

string PlayGame::handleError(int worked) {
	// -2 = no default card
	// -1 = not enough resources
	// 0 = no second card clicked
	// 1 = illegal move
	// 2 = no ability
	// 3 = all good
	if (worked == -2) {
		return "no default card";
	}
	else if (worked == -1) {
		return "not enough resources";
	}
	else if (worked == 0) {
		return "no second card clicked";
	}
	else if (worked == 1) {
		return "illegal move";
	}
	else if (worked == 2) {
		return "no ability available";
	}
	else if (worked == 3) {
		return "";
	}
	else if (worked == 4) {
		return "ability failed";
	}
	else if (worked == 5) {
		return "ability already used";
	}
	return "unknown error";
}

int PlayGame::handleAbility(Card card, int index) {
	int turn = env.get_current_player().get_player_number();
	if (abilities[turn][index]) {
		return 5;
	}
	sf::Texture crd;
	// load images needed for default
	if (crd.loadFromFile("../scugog_project/resources/images/cardcc.png") != true)
	{
		return -2;
	}
	// default 
	int player_turn = env.get_current_player().get_player_number();
	Card dfltCard(0, 0, 0, 0, 0, 0, "cardc.png", "", "");
	sf::Sprite dflt(crd);
	sf::Text dText;
	dText.setString("");
	pair <sf::Sprite, sf::Text> dfltPair;
	dfltPair = make_pair(dflt, dText);

	int ability = card.get_ability();
	if (ability == 0) {
		return 2;
	}
	else if (ability == 1) {
		clickable[index] = true;
		abilities[turn][index] = true;
	}
	else if (ability == 2) {
		for (int i = 0; i < size(hand); i++) {
			if (players[turn].get_hand()[i].get_ability() == 2) {
				for (int index2 = 0; index2 < size(f1); index2++) {
					if (!f1Full[index2]) {
						clickable[index] = false;
						pair<sf::Sprite, sf::Text> pair = players[turn].get_hand()[i].draw_card(0, 0);
						f1[index2] = pair;
						f1Full[index2] = true;
						for (int i = 0; i < size(hand); i++) {
							if (h1Full[i] == false) {
								h1Full[i - 1] = false;
							}
							else if (i == size(hand) - 1) {
								h1Full[6] = false;
							}
						}
						fields[player_turn][index2] = players[player_turn].remove_card_from_hand(i);
						clickable[index2] = false;
						return 3;
					}
				}
			}
		}
		return 4;
	}
	else if (ability == 3) {
		return 2;
	}
	else if (ability == 4) {
		clickable[index] = false;
		abilities[turn][index] = true;
		for (int i = 0; i < size(f2); i++) {
			if (f2Full[i]) {
				Card temp = fields[(turn + 1) % 2][i];
				temp.set_defense(temp.get_defense() - 1);
				fields[(turn + 1) % 2][i] = temp;
				if (temp.get_defense() <= 0) {
					// enemy died
					fields[(player_turn + 1) % 2][i] = dfltCard;
					f2[i] = dfltPair;
					f2Full[i] = false;
					abilities[(player_turn + 1) % 2][i] = false;
					if (temp.get_ability() == 5) {
						int health = players[turn].get_hp();
						players[turn].set_hp(health - 1);
					}
				}
			}
		}
	}
	else if (ability == 5) {
		return 2;
	}
	else if (ability == 6) {
		int res = players[(turn + 1) % 2].get_current_resources();
		if (res > 0) {
			players[(turn + 1) % 2].set_current_resources(res - 1);
			abilities[turn][index] = true;
			able.setString("Enemy stole a resource!");
			ableSet = turn;
			clickable[index] = false;
		}
		else {
			return 4;
		}
	}
	else if (ability == 7) {
		random_device rd;
		mt19937 eng(rd());
		uniform_int_distribution<> distr(0, size(players[(turn + 1) % 2].get_hand()) - 1);
		int kill = distr(eng);
		if (size(players[(turn + 1) % 2].get_hand()) > 1) {
			Card temp = players[(turn + 1) % 2].remove_card_from_hand(kill);
			//players[turn].add_card_to_hand(temp);
			abilities[turn][index] = true;
			able.setString("Enemy killed a card in your hand!");
			ableSet = turn;
			for (int j = 0; j < size((h2Full)); j++) {
				if (h2Full[j] == false) {
					h2Full[j - 1] = false;
				}
				else if (j == size(hand) - 1) {
					h2Full[6] = false;
				}
			}
			clickable[index] = false;
		}
		else {
			return 4;
		}
	}
	else if (ability == 8) {
		random_device rd;
		mt19937 eng(rd());
		uniform_int_distribution<> distr(0, size(players[(turn + 1) % 2].get_hand()) - 1);
		int kill = distr(eng);
		if ((size(players[(turn + 1) % 2].get_hand()) > 1) && (size(players[turn].get_hand()) < 7)) {
			Card temp2 = players[(turn + 1) % 2].remove_card_from_hand(kill);
			players[turn].add_card_to_hand(temp2);
			abilities[turn][index] = true;
			able.setString("Enemy stole a card from your hand!");
			ableSet = turn;
			for (int j = 0; j < size((h1Full)); j++) {
				if (h1Full[j] == false) {
					h1Full[j] = true;
					break;
				}
			}
			for (int j = 0; j < size((h2Full)); j++) {
				if (h2Full[j] == false) {
					h2Full[j - 1] = false;
				}
				else if (j == size(hand) - 1) {
					h2Full[6] = false;
				}
			}
			clickable[index] = false;
		}
		else {
			return 4;
		}
	}
	return 3;
}