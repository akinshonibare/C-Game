//
//  Game.cpp
//  gui
//
//  Created by Akin Shonibare on 2017-10-30.
//  Copyright © 2017 Akin Shonibare. All rights reserved.
//

#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Instructions.h"
#include "ChooseDeck1.h"
#include "ChooseDeck2.h"
#include "PlayGame.h"
#include "WalkthroughGame.h"
#include "EndGameScreen.h"
#include "LoadingScreen.h"
#include "ErrorScreen.h"


// The city is encroaching, stand your ground, redownload our game (you are missing files)
void Game::Start(void)
{
    if(_gameState != Uninitialized)
        return;
    
    _mainWindow.create(sf::VideoMode(1920,1080,64),"Food Fight", sf::Style::Titlebar | sf::Style::Close);
	_mainWindow.setPosition(sf::Vector2i(0, 0));
    _gameState= Game::ShowingSplash;

	GameLoop();
    _mainWindow.close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}

void Game::GameLoop()
{
	int deck1 = 1;
	int deck2 = 1;
	while (_gameState != Game::Exiting) {
		vector<int> decks = { deck1, deck2 };
		switch (_gameState)
		{
			case Game::ShowingMenu:
			{
				ShowMenu();
				break;
			}
			case Game::ShowingSplash:
			{
				int splash_screen = ShowSplashScreen();
				if (splash_screen == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else if (splash_screen == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;	
					break;
				}
				else if (splash_screen == 0) {
					_gameState = Game::ShowingMenu;
					break;
				}
			}
			case Game::ShowingInstructions:
			{
				int instruction_screen_return = ShowInstructions();
				if (instruction_screen_return == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else if (instruction_screen_return == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				else if (instruction_screen_return == 0) {
					_gameState = Game::ShowingMenu;
					break;
				}
			}
			case Game::WalkthroughGameScreen:
			{
				int loading_screen_return = ShowLoadingScreen("Rome wasn't built in a day, neither are walkthroughs");
				if (loading_screen_return == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else if (loading_screen_return == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				Environment env(2, { 1,0 });
				int walkthrough_game_return = Game::ShowWalkthroughGame(env);
				if (walkthrough_game_return == -2) {
					_gameState = Game::Exiting;
				}
				else if (walkthrough_game_return == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
				}
				else {
					ShowEndGame(0);
					_gameState = Game::ShowingMenu;
				}
				break;
			}
			case Game::ShowingCD1:
			{
				deck1 = ShowCD1();
				if (deck1 == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				else if (deck1 == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else {
					_gameState = Game::ShowingCD2;
				}
				break;
			}
			case Game::ShowingCD2:
			{
				deck2 = ShowCD2();
				if (deck2 == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				else if (deck2 == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else {
					_gameState = Game::Playing;
				}
				break;
			}
			case Game::Playing:
			{
				int loading_screen_return = ShowLoadingScreen("It's early in the morning, We are still setting up your fields");
				if (loading_screen_return == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else if (loading_screen_return == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				Environment env(2, decks);
				int player_won = Game::ActivateGame(env);
				if (player_won == -2) {
					_gameState = Game::Exiting;
					break;
				}
				else if (player_won == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
				}
				else {
					int end_game_return = ShowEndGame(player_won);
					if (end_game_return == -2) {
						_gameState = Game::Exiting;
						break;
					}
					else if (end_game_return == -1) {
					ShowErrorScreen();
					_gameState = Game::Exiting;
					break;
					}
					else {
						_gameState = Game::ShowingMenu;
					}
				}
			}
		}
	}
}

int Game::ShowSplashScreen()
{
    SplashScreen splashScreen;
    int splash_screen_return = splashScreen.Show(_mainWindow);
	return splash_screen_return;
}

void Game::ShowMenu()
{
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
    switch(result)
    {
		case MainMenu::Error:
			ShowErrorScreen();
			_gameState = Game::Exiting;
			break;
        case MainMenu::Play:
            _gameState = Game::ShowingCD1;
            break;
        case MainMenu::Instruction:
            _gameState = Game::ShowingInstructions;
            break;
		case MainMenu::Walkthrough:
			_gameState = Game::WalkthroughGameScreen;
			break;
        case MainMenu::Exit:
            _gameState = Game::Exiting;
            break;
    }
}


int Game::ShowInstructions()
{
    Instructions instr;
    int instructions_screen_return = instr.Show(_mainWindow);
	return instructions_screen_return;
}

int Game::ActivateGame(Environment env)
{
	PlayGame gm(env);
	int player_won = gm.Play(_mainWindow);
	return player_won;
}

int Game::ShowCD1()
{
    ChooseDeck1 cd1;
    int deckN = cd1.Show(_mainWindow);
	return deckN;
}

int Game::ShowCD2()
{
    ChooseDeck2 cd2;
    int deckN = cd2.Show(_mainWindow);
	return deckN;
}

int Game::ShowWalkthroughGame(Environment env)
{
	WalkthroughGame walkthrough(env);
	int player_won = walkthrough.Play(_mainWindow);
	return player_won;
}

int Game::ShowEndGame(int player_won)
{
	EndGameScreen endgamescreen;
	int end_game_return = endgamescreen.Show(_mainWindow, player_won);
	return end_game_return;
}

int Game::ShowLoadingScreen(string string_input)
{
	LoadingScreen loadingscreen;
	int loading_screen_return = loadingscreen.Show(_mainWindow, string_input);
	return loading_screen_return;
}

void Game::ShowErrorScreen()
{
	ErrorScreen errorscreen;
	errorscreen.Show(_mainWindow);
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
