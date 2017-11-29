# Food Fight

## Overview

The project our team has chosen to work on is a C++ based game. This game will be a 2-player only, trading-card style game in which the two players must duel using their selected deck of premade cards and attempt to beat the other. The cards will all have individual statistics which will come into play during the game. Beyond the basic elements of game play we also hope to implement the ability for each player to customize their own deck of cards, dividing an allotted number of ‘points’ between the statistics for each card in the manner they think best. If customized decks are added to the game then a saving functionality will be implemented to save these custom decks for later use. No saving will be possible during an instance of the game however. This project will give all members a chance to explore the logic that goes into creating a complex game-play experience as well the opportunity for expansion by allowing users to connect from different computers and allowing for other user customization of the decks. 

## Libraries

You need Boost. The project also uses cppconn 1.1.9 on 32 bit architecture and SFML VC 14 32 bit architecture however they are in the repository. I also suggest having MySQL workbench if you are adding to the database for simple use.

## Motivation

Project is/was created for CISC 320 at Queen's University for Professor McLeod in 2017.

## Installation

Clone the repository

The only change you should need to make to the project properties is change where boost is located in your file system. Boost has file names that are too long to upload to BitBucket.

Under scugog_project project properties go to C/C++, then go to general under that tab and click on the "Additional Include Directories" and change the current directory path to wherever your boost is located.

## Tests

To check to see if both projects are running smoothly, right click on each project and set as startup project. Each project should not error out if configurations are set properly. To test individual configurations comment out all main functions other than those in verify_sfml.cpp and verify_connection.cpp individually to test each piece. These are located in scugog_project.

If SQL is erroring out then you might need to go into deck.cpp and comment out line 79 and uncomment line 80. Sometimes Ryan forgets to swap comments in debug mode.

## Contributors

Eric Chau, Connor Jenkins, Grace Pigeau, Logan Roth, Akinkunmi Shonibare, Ryan van Huuksloot

## License

MIT License