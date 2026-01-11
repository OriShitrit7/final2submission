#pragma once
#include "GameBase.h"
#include "Utils.h"
#include "Steps.h"
#include "Results.h"


class KeyboardGame : public GameBase {
private:
    bool saveMode;
    Steps steps;
    Results results;
    Screen fixedScreens[NUM_SCREENS];  // Constant screens like menu\instructions

protected:
    KeyboardGame();

    void handleInput() override;
    void pauseGame();

public:
    KeyboardGame(bool save = false);
    ~KeyboardGame();

    int getDelay() override {return 150;} // was it 150?

    void showMenu();
    void showInstructions();

    bool reloadRoom(int roomID);

    void showError(const std::string &msg);

    void showMessage(const std::string &msg);

    void applyLifeLoss(Player &player);

    void onScreenChange(Player p, int room) override {
        if (saveMode) results.addScreenChange(getGameCycle(), p, room);
    }

    void onLifeLost(Player p) override {
        if (saveMode) results.addLifeLost(getGameCycle(), p);
    }

    void onRiddle(Player p, bool correct) override {
        if (saveMode) results.addRiddle(getGameCycle(), p, correct);
    }

    void onGameEnd() override {
        if (!saveMode) return;
        Player* players=getPlayersArr();
        results.addGameEnd(getGameCycle(), players[0].getScore(), players[1].getScore());
    }

};
