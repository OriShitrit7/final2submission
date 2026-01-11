#include "KeyboardGame.h"
// יכול להיות שצריכים לקרוא בלולאת משחק כל פעם עם player כארגומנט

KeyboardGame::KeyboardGame() {
    Utils::initConsole();

    fixedScreens[MENU_SCREEN].setMap(MENU_MAP);
    fixedScreens[INSTRUCTIONS_SCREEN].setMap(INSTRUCTIONS_MAP);

    setGame();
    showMenu();      // going into the main menu
}


void KeyboardGame::handleInput()
{
    if (!Utils::hasInput())   // no key pressed this frame
        return;

    char ch = Utils::getChar();
    char c = std::toupper(ch);

    // If the game is already over (final room):
    // only 'H' should work and return to the main menu
    if (gameOver)
    {
        if (c == HOME)
        {
            isRunning = false;      // leave run() and go back to menu
        }
        return;                     // ignore all other keys in final room
    }
    // Pause the game
    if (c == ESC)
    {
        pauseGame();
        return;
    }

    // Player wants to restart room
    if (c == RESTART)
    {
        if (!restartCurrentRoom()){

            isRunning = false;
            return;
        }
        return;
    }
    processKey(ch);
}

void KeyboardGame::showMenu() // is it only KeyBoardGame's function?
{
    char choice = '\0';

    while (true)
    {
        fixedScreens[MENU_SCREEN].drawBase();
        std::cout << std::flush;

        char ch = Utils::getChar();
        choice = std::toupper(ch);

        switch (choice)
        {
        case START: // Start new game
            initGame();          // prepares the game - map, objects, players

            if (!loadGameFiles())  // file-related error: return to main menu
                break;

            run();    // start game
            break;

        case INSTRUCTIONS:    // Show instructions
            showInstructions();
            break;

        case EXIT:    // Exit game
            setRunning(false);
            return;

        default:
            Utils::gotoxy(33, 14);
            std::cout << "Invalid choice.";
            Utils::delay(800);
            break;
        }
    }
}

void KeyboardGame::showInstructions()
{
    Utils::clearScreen();
    fixedScreens[INSTRUCTIONS_SCREEN].drawBase();   // Shows the instructions screen

    // Title
    Utils::gotoxy(30, 2);
    std::cout << "=== INSTRUCTIONS ===";

    // Goal & Basics
    Utils::gotoxy(2, 3);
    std::cout << "GOAL: Reach Final Room together! Move through rooms and earn points.";
    Utils::gotoxy(2, 4);
    std::cout << "RESTART ROOM: 'R' || GAME OVER: If any player has 0 Lives.";
    Utils::gotoxy(2, 5);
    std::cout << "POINTS: Key(10) Door(20) Riddle(10) Win(1st:100/2nd:50).";

    // Controls
    Utils::gotoxy(4, 7);
    std::cout << "CONTROLS:         PLAYER 1      PLAYER 2";
    Utils::gotoxy(4, 8);
    std::cout << "Move (U/L/D/R):   W/A/X/D       I/J/M/L";
    Utils::gotoxy(4, 9);
    std::cout << "Stay / Dispose:   S  /  E       K  /  O";

    Utils::gotoxy(4, 11);
    std::cout << "ITEMS (Walk over an item to pick it up, max 1 item per player):";
    Utils::gotoxy(6, 12);
    std::cout << "+ Key (" << BOARD_KEY << "): Collect to open matching doors.";
    Utils::gotoxy(6, 13);
    std::cout << "+ Bomb (" << BOARD_BOMB << "): Explodes in 5 turns. Destroys players & walls (" << WALL_VERT << ' ' << WALL_HORIZ << ").";
    Utils::gotoxy(6, 14);
    std::cout << "+ Torch (" << BOARD_TORCH << "): Reveals invisible DARK AREAS (" << DARK_CHAR << ").";
    Utils::gotoxy(6, 15);
    std::cout << "Doors: Open only when the required keys and switches are set,";
    Utils::gotoxy(6, 16);
    std::cout << "Riddle (" << BOARD_RIDDLE << "): Blocks path! Answer correctly to remove.";
    Utils::gotoxy(6, 17);
    std::cout << "Switch (" << BOARD_SWITCH_ON << ' ' << BOARD_SWITCH_OFF << "): Stepping on it toggles Doors.";
    Utils::gotoxy(6, 18);
    std::cout << "Spring (" << BOARD_SPRING << "): Launches player (High Speed!).";
    Utils::gotoxy(6, 19);
    std::cout << "Obstacle (" << BOARD_OBSTACLE << "): Heavy! Move by High Speed or Teamwork.";
    Utils::gotoxy(6, 20);
    std::cout << "Teleport (" << BOARD_TELEPORT << "): Move through portals in the room.";

    // Return
    Utils::gotoxy(2, 23);
    std::cout << "Press any key to return.";

    std::cout << std::flush;
    char c = Utils::getChar();   // Wait for user input
}

// Restart Functions

bool KeyboardGame::restartCurrentRoom()
{
    // Final room does not support restart
    if (isFinalRoom(currRoomID)) // צריך לטפל במקרה שאנחנו בfileGame
    {
        return true;
    }
    // Clear current room state
    screens[currRoomID].clearRoom();
    // Reload room from original file
    if (!reloadRoom(currRoomID))
    {
        return false;
    }
    // Reset players that are currently in this room
    for (int i = 0; i < NUM_PLAYERS; ++i)
    {
        if (playerRoom[i] == currRoomID)
            players[i].resetForRoom();
    }
    return true;
}

bool KeyboardGame::reloadRoom(int roomID) //
{
    // Reloads a specific room from its original source file.
    std::vector<Screen> *screens = getScreenArr();
    if (roomID < 0 || roomID >= screens->size())
        return false;

    std::string error, warning;
    const std::string& filename = screens[roomID].getSourceFile();
    // Room has no associated file (e.g., final room)
    if (filename.empty())
    {
        showError("Restarting room failed");
        return false;
    }
    // Reload screen from file
    if (!screens[roomID].loadScreenFromFile(filename, error, warning)) {
        showError(error);
        return false;
    }
    if (!loadRiddles(roomID))
    {
        return false;
    }
    if (!screens[roomID].validateLegendPlacement(error))
    {
        showError(error);
        return false;
    }
    screens[roomID].clearLegendAreaFromBoard();

    return true;
}

void KeyboardGame::showError(const std::string& msg)
{
    Utils::clearScreen();

    std::string line1, line2;
    bool foundNewline = false;

    for (size_t i = 0; i < msg.length(); i++)
    {
        if (msg[i] == '\n')
        {
            foundNewline = true;
            continue;
        }

        if (!foundNewline)
            line1 += msg[i];
        else
            line2 += msg[i];
    }

    std::string errorTitle = "ERROR:";
    int xError = (SCREEN_WIDTH - errorTitle.length()) / 2;
    Utils::gotoxy(xError, 10);
    std::cout << errorTitle;

    int xLine1 = (SCREEN_WIDTH - line1.length()) / 2;
    Utils::gotoxy(xLine1, 12);
    std::cout << line1;

    if (!line2.empty())
    {
        int xLine2 = (SCREEN_WIDTH - line2.length()) / 2;
        Utils::gotoxy(xLine2, 13);
        std::cout << line2;
    }

    std::string pressKey = "Press any key to continue ";
    int xPress = (SCREEN_WIDTH - pressKey.length()) / 2;
    Utils::gotoxy(xPress, 17);
    std::cout << pressKey;

    std::cout << std::flush;
    Utils::getChar();
}

void KeyboardGame::showMessage(const std::string& msg)
{
    Utils::clearScreen();
    std::string line1, line2;
    bool foundNewline = false;

    for (size_t i = 0; i < msg.length(); i++)
    {
        if (msg[i] == '\n')
        {
            foundNewline = true;
            continue;
        }

        (!foundNewline)?(line1 += msg[i]):(line2 += msg[i]);
    }

    int xLine1 = (SCREEN_WIDTH - line1.length()) / 2;
    Utils::gotoxy(xLine1, 12);
    std::cout << line1;
    if (!line2.empty())
    {
        int xLine2 = (SCREEN_WIDTH - line2.length()) / 2;
        Utils::gotoxy(xLine2, 13);
        std::cout << line2;
    }
    std::string pressKey = "Press any key to continue ";
    int xPress = (SCREEN_WIDTH - pressKey.length()) / 2;
    Utils::gotoxy(xPress, 17);
    std::cout << pressKey;

    std::cout << std::flush;
    Utils::getChar();
}


void KeyboardGame::applyLifeLoss(Player& player)
{
    // Decrease player's life and check if still alive
    bool stillAlive = player.lowerLife();

    // Player has no lives left -> end game
    if (!stillAlive)
    {
        showMessage("Player is dead. Better luck next time... -.-");
        setGameOver(true);
        setRunning(false);
    }
}
