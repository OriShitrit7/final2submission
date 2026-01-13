#pragma once
#include "GameBase.h"
#include "Utils.h"
#include "Steps.h"
#include "Results.h"
#include <vector>


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

    void showMenu();
    void showInstructions();

    void drawPlayers();

    void handleError(const std::string& msg) override;
    void handleMessage(const std::string& msg) override;

    bool restartCurrentRoom();
    bool reloadRoom(int roomID);

    void applyLifeLoss(Player &player) override;

    void onScreenChange(PlayerID id, int room) override {
        if (saveMode) results.addScreenChange(gameCycles, id, room);
    }

    void onLifeLost(PlayerID id) override {
        if (saveMode) results.addLifeLost(gameCycles, id);
    }

    void onRiddle(PlayerID id, bool correct) override {
        if (saveMode) results.addRiddle(gameCycles, id, correct);
    }

    void onGameEnd() override {
        if (!saveMode) return;
        results.addGameEnd(gameCycles, players[0].getScore(), players[1].getScore());
    }

    int getDelay() const override {return KEYBOARD_DELAY;}

};
