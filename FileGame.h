#pragma once
#include "GameBase.h"
#include "Steps.h"
#include "Results.h"

class FileGame : public GameBase {
private:
    bool silentMode;
    Steps steps;
    Results expectedResults;
    Results actualResults;
    bool testPassed;
    int delay;

protected:
    void handleInput() override;

    //void delay() override; // why is it needed?

    bool loadStepsFromFile();

    void onScreenChange(Player p, int room) override {
        actualResults.addScreenChange(getGameCycle(), p, room);
    }

    void onLifeLost(Player p) override {
        actualResults.addLifeLost(getGameCycle(), p);
    }

    void onRiddle(Player p, bool correct) override {
        actualResults.addRiddle(getGameCycle(), p, correct);
    }

    void onGameEnd() override {
        Player* players=getPlayersArr();
        actualResults.addGameEnd(getGameCycle(),players[0].getScore(), players[1].getScore());
    }

    int getDelay() const override { return silentMode ? 0 : 10; }


public:
    FileGame(bool silent = false);
    ~FileGame();

    bool didTestPass() const { return testPassed; }
    void compareResults();

    int getDelay(){return silentMode?0:50;}

    //bool loadStepsFromFile(const std::string& filename) {steps=loadSteps();}

};