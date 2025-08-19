#include "Menu.h"

extern short menuChoice = 0; //extern example to share data with menu and gameSource

short Menu::startMenu()
{
    bool valid = false;
    int choice;
    do {
        system("cls");
        std::cout << "Pick a Game:" << std::endl << "1. Space Invaders" << std::endl << "2. Frogger" << std::endl << "3. Quit" << std::endl << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            valid = true;
            game = make_unique<SpaceInvaders>();
            *game->gameState = GameSource::SPACEINVADERS;
            game->initialiseGame();
            system("cls");
            break;
        case 2:
            game = make_unique<SpaceInvaders>();
            *game->gameState = GameSource::GAMEOVER;
            game->gameOver();
            return 3;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl << "Press any key to continue..." << std::endl;
            _getch();
            break;
        }
    } while (!valid);

    return choice;
}
void Menu::update()
{
    while (*game->gameState != GameSource::GameState::EXIT )
    {
        switch (*game->gameState)
        {
        case GameSource::STARTSCREEN:
            *game->gameState = static_cast<GameSource::GameState>(this->startMenu());
            update();
        case GameSource::SPACEINVADERS:
            game = make_unique<SpaceInvaders>();
            game->initialiseGame();
            break;

        case GameSource::GAMEOVER:
            game->gameOver();
            break;

        case GameSource::EXIT:
            return;
        }
    }
}