#include "stdafx.h"
#include "MainMenu.h"
#include <iostream>

using namespace std;


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Vector2u WindowSize;
	WindowSize = window.getSize();
    sf::Texture texture;
	if (!texture.loadFromFile("../scugog_project/resources/images/main_menu.png")) {
		return Error;
	}
    sf::Sprite sprite(texture);
	sf::Vector2u SpriteSize;

	sf::Text play_text, instructions_text, exit_text, walkthrough_text;
	sf::Font font;
	if (!font.loadFromFile("../scugog_project/resources/fonts/BerlinSansFBDemiBold.ttf")) {
		return Error;
	}

	sf::Vector2u windowSize = window.getSize();

	play_text.setFont(font);
	play_text.setString("START");
	play_text.setCharacterSize(100);
	play_text.setFillColor(sf::Color::Black);
	play_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> play_text_size = play_text.getGlobalBounds();
	play_text.setPosition(sf::Vector2f(450 - play_text_size.width / 2, 672 - play_text_size.height / 2));

	instructions_text.setFont(font);
	instructions_text.setString("INSTRUCTIONS");
	instructions_text.setCharacterSize(100);
	instructions_text.setFillColor(sf::Color::Black);
	instructions_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> instructions_text_size = instructions_text.getGlobalBounds();
	instructions_text.setPosition(sf::Vector2f(450 - instructions_text_size.width / 2, 672 - instructions_text_size.height / 2 + play_text_size.height + 10));

	walkthrough_text.setFont(font);
	walkthrough_text.setString("WALKTHROUGH");
	walkthrough_text.setCharacterSize(100);
	walkthrough_text.setFillColor(sf::Color::Black);
	walkthrough_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> walkthrough_text_size = walkthrough_text.getGlobalBounds();
	walkthrough_text.setPosition(sf::Vector2f(450 - walkthrough_text_size.width / 2, 672 - walkthrough_text_size.height / 2 + play_text_size.height + instructions_text_size.height + 20));

	exit_text.setFont(font);
	exit_text.setString("EXIT");
	exit_text.setCharacterSize(100);
	exit_text.setFillColor(sf::Color::Black);
	exit_text.setStyle(sf::Text::Style::Italic);
	sf::Rect<float> exit_text_size = exit_text.getGlobalBounds();
	exit_text.setPosition(sf::Vector2f(450 - exit_text_size.width / 2, 672 - exit_text_size.height / 2 + instructions_text_size.height/2 + play_text_size.height + instructions_text_size.height + walkthrough_text_size.height));

    //Setup clickable regions
    
    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top= 667;
    playButton.rect.height = play_text_size.height;
    playButton.rect.left = 310;
    playButton.rect.width = play_text_size.width;
    playButton.action = Play;
    
    //Play instructionButton item coordinates
    MenuItem instructionButton;
    instructionButton.rect.top= 756;
	instructionButton.rect.height = instructions_text_size.height;
	instructionButton.rect.left = 117;
	instructionButton.rect.width = instructions_text_size.width;
    instructionButton.action = Instruction;

	MenuItem walkthroughButton;
	walkthroughButton.rect.top = 833;
	walkthroughButton.rect.height = walkthrough_text_size.height;
	walkthroughButton.rect.left = 78;
	walkthroughButton.rect.width = walkthrough_text_size.width;
	walkthroughButton.action = Walkthrough;
    
    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 285;
    exitButton.rect.width = exit_text_size.width;
    exitButton.rect.top = 895;
    exitButton.rect.height = exit_text_size.height;
    exitButton.action = Exit;
    
    _menuItems.push_back(playButton);
    _menuItems.push_back(instructionButton);
	_menuItems.push_back(walkthroughButton);
    _menuItems.push_back(exitButton);
    
    window.draw(sprite);
	window.draw(play_text);
	window.draw(instructions_text);
	window.draw(walkthrough_text);
	window.draw(exit_text);
	window.display();
    
    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;
	//cout << "Mouse x: " << x << " Mouse y: " << y << endl;
    for ( it = _menuItems.begin(); it != _menuItems.end(); it++)
    {
        sf::Rect<int> menuItemRect = (*it).rect;
		//cout << "Top: " << menuItemRect.top << " Height: " << menuItemRect.height << " Left: " << menuItemRect.left << " Width: " << menuItemRect.width << endl;
        if( (menuItemRect.height + menuItemRect.top) > y && menuItemRect.top < y && menuItemRect.left < x && (menuItemRect.left + menuItemRect.width) > x)
        {
            return (*it).action;
            //std::cout << (*it).action << std::endl;
        }
    }
    
    return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    
    while(true)
    {
        while(window.pollEvent(menuEvent))
        {
            if(menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            if(menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}
