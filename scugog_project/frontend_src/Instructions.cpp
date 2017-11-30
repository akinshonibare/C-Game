#include "stdafx.h"
#include "Instructions.h"



int Instructions::Show(sf::RenderWindow & renderWindow)
{
	// New instruction page uses an image wallpaper instead of sfml now
	sf::Texture wallpaper;
	if (wallpaper.loadFromFile("../scugog_project/resources/images/new_instruction_page.png") != true)
	{
		return -1;
	}
	sf::Sprite wallpaperSprite(wallpaper);
	renderWindow.draw(wallpaperSprite);

	// Old sfml code used to make old instructions page
	/*
	sf::Texture texture, card, attackIcon, defenceIcon, costIcon, powerIcon, cuttingBoard;
	if (texture.loadFromFile("../scugog_project/resources/images/bg5.png") != true)
	{
		return -1;
	}
	if (card.loadFromFile("../scugog_project/resources/images/cardExample.png") != true)
	{
		return -1;
	}

	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	sf::Font font, font1;

	sf::Sprite cardSprite(card);
	cardSprite.setPosition(sf::Vector2f(130, 600));
	renderWindow.draw(cardSprite);

	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return -1;
	}
	if (!font1.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}

	sf::Text text2;
	text2.setFont(font1);
	text2.setString("Instructions");
	text2.setCharacterSize(60);
	text2.setFillColor(sf::Color(20, 20, 20));
	text2.setStyle(sf::Text::Style::Regular);
	sf::Rect<float> tsize2 = text2.getGlobalBounds();
	text2.setOrigin(sf::Vector2f(tsize2.width / 2, tsize2.height / 2));
	text2.setPosition(sf::Vector2f(960, 25));

	sf::Text text3;
	text3.setFont(font);
	text3.setString("press 'ENTER' or click anywhere to continue");
	text3.setCharacterSize(30);
	text3.setFillColor(sf::Color(20, 20, 20));
	text3.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize3 = text3.getGlobalBounds();
	text3.setOrigin(sf::Vector2f(tsize3.width / 2, tsize3.height / 2));
	text3.setPosition(sf::Vector2f(945, 80));


	sf::Text instr;
	instr.setFont(font);
	instr.setString("\
		The goal of Food Fight is to use your cards to lower your opponent's life points to 0 while protecting your life points from the opponent's cards.\n\
		Start:\n\
		Start the game by clicking on the START button.\n\
		From there both players will be taken to a page where they will be asked to pick a deck by clicking on it.\n\
		At the start of the game, each player will be given 7 randomly drawn cards from their deck and 3 resource points.\n\
		Play:\n\
		Each card can only perform one of the following each turn.\n\
		1. A player may discard cards from their field or hand onto the cutting board in exchange for one resource point.\n\
		2. A player may place multiple cards on the field by clicking on any card in their hand and then on the field.\n\
		The cards that can be moved to the field is limited by the number of resources the player has.\n\
		3. A player may use any card on their field to attack their opponent directly.\n\
		To attack an opposing player click on a card in your field and then on the opponent farmer icon.\n\
		4. A player may use any card on their field to attack a card on the opponents field.\n\
		To attack an opposing player click on a card in your field and then on a card in the opponents field.\n\
		Attacking:\n\
		If the attacking card has more attack points than the opposing card has defense, the opposing card dies.\n\
		If the attacking card has less attack points than the opposing card has defense, they survived the attack! Their defense loses corresponding defense points but...\n\
		EITHER the opposing card has more attack points than the attacking card has defense points: the opposing card attacks back and the attacking card dies.\n\
		OR the opposing card has less attack points than the attacking card has defense points: they attack back but the attacking card is safe and unaffected.\n");

	instr.setCharacterSize(23);
	instr.setFillColor(sf::Color(20, 20, 20));
	instr.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize4 = instr.getGlobalBounds();
	instr.setPosition(sf::Vector2f(-40, 110));

	// cost icon
	if (costIcon.loadFromFile("../scugog_project/resources/images/icons/icon_cost.png") != true)
	{
		return -1;
	}
	sf::Sprite costSprite(costIcon);
	costSprite.setPosition(sf::Vector2f(490, 592));
	renderWindow.draw(costSprite);

	sf::Text costText;
	costText.setFont(font);
	costText.setString("\
	COST\n\
	How many resource points it costs to move the card  from the hand onto the field");
	costText.setCharacterSize(30);
	costText.setFillColor(sf::Color(20, 20, 20));
	costText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize8 = costText.getGlobalBounds();
	costText.setPosition(sf::Vector2f(580, 612));

	// power icon
	if (powerIcon.loadFromFile("../scugog_project/resources/images/icons/icon_power.png") != true)
	{
		return -1;
	}
	sf::Sprite powerSprite(powerIcon);
	powerSprite.setPosition(sf::Vector2f(490, 702));
	renderWindow.draw(powerSprite);

	sf::Text powerText;
	powerText.setFont(font);
	powerText.setString("\
	POWER\n\
	How many life points the card can take away from the opposing player.");
	powerText.setCharacterSize(30);
	powerText.setFillColor(sf::Color(20, 20, 20));
	powerText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize5 = powerText.getGlobalBounds();
	powerText.setPosition(sf::Vector2f(580, 722));

	//defence icon
	if (defenceIcon.loadFromFile("../scugog_project/resources/images/icons/icon_defence.png") != true)
	{
		return -1;
	}
	sf::Sprite defenceSprite(defenceIcon);
	defenceSprite.setPosition(sf::Vector2f(490, 822));
	renderWindow.draw(defenceSprite);

	sf::Text defenceText;
	defenceText.setFont(font);
	defenceText.setString("\
	DEFENCE\n\
	How many points can be taken from the card by an opponent's card's attack before it dies.");
	defenceText.setCharacterSize(30);
	defenceText.setFillColor(sf::Color(20, 20, 20));
	defenceText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize6 = defenceText.getGlobalBounds();
	defenceText.setPosition(sf::Vector2f(580, 842));

	// attack icon
	if (attackIcon.loadFromFile("../scugog_project/resources/images/icons/icon_attack.png") != true)
	{
		return -1;
	}
	sf::Sprite attackSprite(attackIcon);
	attackSprite.setPosition(sf::Vector2f(490, 942));
	renderWindow.draw(attackSprite);

	sf::Text attackText;
	attackText.setFont(font);
	attackText.setString("\
	ATTACK\n\
	How many defence points the card can take away from an opponent's card.");
	attackText.setCharacterSize(30);
	attackText.setFillColor(sf::Color(20, 20, 20));
	attackText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize7 = attackText.getGlobalBounds();
	attackText.setPosition(sf::Vector2f(580, 962));

	// cutting board
	if (cuttingBoard.loadFromFile("../scugog_project/resources/images/cuttingboard.png") != true)
	{
		return -1;
	}
	sf::Sprite boardSprite(cuttingBoard);
	boardSprite.setPosition(sf::Vector2f(1500, 250));
	renderWindow.draw(boardSprite);

	sf::Text boardText;
	boardText.setFont(font);
	boardText.setString("\
	\n\
	The CUTTING BOARD");
	boardText.setCharacterSize(30);
	boardText.setFillColor(sf::Color(20, 20, 20));
	boardText.setStyle(sf::Text::Style::Bold);
	sf::Rect<float> tsize9 = boardText.getGlobalBounds();
	boardText.setPosition(sf::Vector2f(1407, 340));

	renderWindow.draw(boardText);
	renderWindow.draw(costText);
	renderWindow.draw(powerText);
	renderWindow.draw(defenceText);
	renderWindow.draw(attackText);
	renderWindow.draw(text2);
	renderWindow.draw(text3);
	renderWindow.draw(instr);
	*/

	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed) {
				return -2;
			}
			else if (event.type == sf::Event::EventType::KeyPressed) {
				return 0;
			}
		}
	}
}

