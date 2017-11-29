#include "stdafx.h"
#include "ChooseDeck2.h"



int ChooseDeck2::Show(sf::RenderWindow & renderWindow)
{

	sf::Texture texture, card3, card4;
	sf::Font font, font1;
	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return -1;
	}

	if (!font1.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}

	if (texture.loadFromFile("../scugog_project/resources/images/bg.jpg") != true)
	{
		return -1;
	}

	if (card3.loadFromFile("../scugog_project/resources/images/farmer.png") != true)
	{
		return -1;
	}

	if (card4.loadFromFile("../scugog_project/resources/images/farmer2.png") != true)
	{
		return -1;
	}

	sf::Sprite cd1(card3);
	sf::Sprite cd2(card4);

	sf::Text text;
	text.setFont(font1);
	text.setString("Player Two Choose Your Farmer!");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize = text.getGlobalBounds();
	text.setOrigin(sf::Vector2f(tsize.width / 2, tsize.height / 2));
	text.setPosition(sf::Vector2f(960, 25));

	sf::Text text2;
	text2.setFont(font);
	text2.setString("Press 'Enter' when selected");
	text2.setCharacterSize(20);
	text2.setFillColor(sf::Color::Black);
	text2.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> t2size = text.getGlobalBounds();
	text2.setOrigin(sf::Vector2f(t2size.width / 2, t2size.height / 2));
	text2.setPosition(sf::Vector2f(960, 100));

	sf::Text deckDone;
	deckDone.setFont(font);
	deckDone.setString("");
	deckDone.setCharacterSize(30);
	deckDone.setFillColor(sf::Color::Black);
	deckDone.setStyle(sf::Text::Style::Regular);
	sf::Rect<float> dDsize = deckDone.getGlobalBounds();
	deckDone.setOrigin(sf::Vector2f(dDsize.width / 2, dDsize.height / 2));
	deckDone.setPosition(sf::Vector2f(960, 550));

	sf::Text tagLine;
	tagLine.setFont(font);
	tagLine.setString("");
	tagLine.setCharacterSize(15);
	tagLine.setFillColor(sf::Color::Black);
	tagLine.setStyle(sf::Text::Style::Regular);
	sf::Rect<float> tLsize = tagLine.getGlobalBounds();
	tagLine.setOrigin(sf::Vector2f(tLsize.width / 2, tLsize.height / 2));
	tagLine.setPosition(sf::Vector2f(960, 550));

	cd1.setOrigin(sf::Vector2f(106, 150));
	cd2.setOrigin(sf::Vector2f(106, 150));
	cd1.setPosition(sf::Vector2f(960 - 125, 350));
	cd2.setPosition(sf::Vector2f(960 + 125, 350));

	sf::FloatRect cd1Pos = cd1.getGlobalBounds();
	sf::FloatRect cd2Pos = cd2.getGlobalBounds();
	float cd1L = cd1Pos.left;
	float cd1R = cd1Pos.left + cd1Pos.width;
	float cd1T = cd1Pos.top;
	float cd1B = cd1Pos.top + cd1Pos.height+50;
	float cd2L = cd2Pos.left;
	float cd2R = cd2Pos.left + cd2Pos.width;
	float cd2T = cd2Pos.top;
	float cd2B = cd2Pos.top + cd2Pos.height+50;

	sf::Sprite sprite(texture);

	sf::Event event;
	int deckChoice = -1;
	while (true)
	{
		renderWindow.draw(sprite);
		renderWindow.draw(text);
		renderWindow.draw(text2);
		renderWindow.draw(cd1);
		renderWindow.draw(cd2);
		renderWindow.draw(deckDone);
		renderWindow.draw(tagLine);
		renderWindow.display();
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				if (deckChoice == -1) {
					deckDone.setString("No Farmer Chosen!");
					deckDone.setPosition(sf::Vector2f(825, 550));
				}
				else {
					return deckChoice;
				}
			}
			if (event.type == sf::Event::EventType::MouseButtonPressed) {
				sf::Vector2i mousePos = sf::Mouse::getPosition();
				float horz = mousePos.x;
				float vert = mousePos.y;
				if ((horz > cd1L) && (horz < cd1R) && (vert > cd1T) && (vert < cd1B)) {
					deckChoice = 0;
					deckDone.setString("Bert the Beet Farmer\n\"You can't 'beet' me!\"");
					tagLine.setString("\nHearty Vegetables Deck Chosen");
					deckDone.setPosition(sf::Vector2f(750, 400));
					tagLine.setPosition(sf::Vector2f(750, 450));
				}
				else if ((horz > cd2L) && (horz < cd2R) && (vert > cd2T) && (vert < cd2B)) {
					deckChoice = 1;
					deckDone.setString("Franny the Fruit Farmer\n\"'Peel' the burn!\"");
					tagLine.setString("\nSugar-Rush Fruit Deck");
					deckDone.setPosition(sf::Vector2f(960, 400));
					tagLine.setPosition(sf::Vector2f(960, 450));
				}
				else {
					deckChoice = -1;
					deckDone.setString("");
					tagLine.setString("");
				}
			}
			if (event.type == sf::Event::Closed) {
				return -2;
			}
		}
	}
}

