#include "stdafx.h"
#include "ErrorScreen.h"

void ErrorScreen::Show(sf::RenderWindow & renderWindow)
{
	//sf::Image image;
	sf::Texture texture;
	if (texture.loadFromFile("../scugog_project/resources/images/error_screen.png") != true)
	{
		return;
	}
	sf::Font font;
	if (!font.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return;
	}

	sf::Vector2u windowSize = renderWindow.getSize();
	sf::Text text;
	text.setFont(font);
	text.setString("The city is encroaching on your farm, stand your ground!");
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(windowSize.x - tsize.width - 75, 100));

	sf::Text text1;
	text1.setFont(font);
	text1.setString("You are missing files, redownload the game");
	text1.setCharacterSize(60);
	text1.setFillColor(sf::Color::White);
	text1.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize_text1 = text1.getGlobalBounds();
	text1.setPosition(sf::Vector2f(windowSize.x - tsize_text1.width - 65, windowSize.y - tsize_text1.height - 75));

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.draw(text1);
	renderWindow.draw(text);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}
