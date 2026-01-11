#pragma once
#include "GameBase.h"
#include "Utils.h"
#include "Steps.h"
#include "Results.h"


class KeyBoardGame : public GameBase {
private:
    bool saveMode;
    Steps steps;
    Results results;
    int delay;

protected:
    KeyBoardGame();

    void handleInput() override;
    void pauseGame() override;

public:
    KeyBoardGame(bool save = false);
    ~KeyBoardGame();

    int getDelay() {return delay;}

    void showMenu();
    void showInstructions();
};
