#pragma once
#include "GameBase.h"
#include "Utils.h"
#include "Steps.h"
#include "Results.h"
#include <vector>

class KeyboardGame : public GameBase {
private:
    bool saveMode;
    Screen fixedScreens[NUM_SCREENS];  // Constant screens like menu\instructions

protected:
    void handleInput() override;
    void pauseGame();
    void onGameEnd() override;
    void onPlayerDeath(Player&) override;
    int getDelay() const override { return KEYBOARD_DELAY; }

public:
    explicit KeyboardGame(bool save = false);
    ~KeyboardGame() override;   // why override?

    void showMenu();
    void showInstructions();



};
