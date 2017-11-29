#include "stdafx.h"
#include "LoadingScreen.h"
#include <string>

int LoadingScreen::Show(sf::RenderWindow & renderWindow, std::string string_input)
{
	//sf::Image image;
	sf::Texture texture;
	sf::Font font;
	if (!font.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return -1;
	}
	if (texture.loadFromFile("../scugog_project/resources/images/loading_screen.jpg") != true)
	{
		return -1;
	}

	sf::Vector2u windowSize = renderWindow.getSize();
	sf::Text text;
	text.setFont(font);
	text.setString(string_input);
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize = text.getGlobalBounds();
	text.setPosition(sf::Vector2f(windowSize.x - tsize.width - 75, 100));

	sf::Text text1;
	text1.setFont(font);
	text1.setString("Loading...");
	text1.setCharacterSize(60);
	text1.setFillColor(sf::Color::White);
	text1.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> tsize_text1 = text1.getGlobalBounds();
	text1.setPosition(sf::Vector2f(windowSize.x - tsize_text1.width - 65, windowSize.y - tsize_text1.height - 75));

	//texture.update(image);
	sf::Sprite sprite(texture);
	renderWindow.draw(sprite);
	renderWindow.draw(text);
	renderWindow.draw(text1);
	renderWindow.display();

	sf::Event event;
	renderWindow.pollEvent(event);
	if (event.type == sf::Event::EventType::Closed)
	{
		return -2;
	}

}
