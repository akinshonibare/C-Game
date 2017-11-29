#include "stdafx.h"
#include "SplashScreen.h"

int SplashScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	sf::Font font, font1;
	if (!font.loadFromFile("../scugog_project/resources/fonts/sansation.ttf")) {
		return -1;
	}
	if (!font1.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}
	if (texture.loadFromFile("../scugog_project/resources/images//splash_screen.png") != true)
	{
		return -1;
	}


	sf::Vector2u windowSize = renderWindow.getSize();

	sf::Text text;
	text.setFont(font);
	text.setString("Click anywhere to continue!");
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(windowSize.x/2 - tsize.width/2, windowSize.y / 2 - tsize.height /2));

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.draw(text);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				return -2;
			}
			else if (event.type == sf::Event::EventType::MouseButtonPressed) {
				return 0;
			}
		}
	}
}
