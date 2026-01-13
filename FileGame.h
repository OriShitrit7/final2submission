#pragma once
#include "GameBase.h"
#include "Steps.h"
#include "Results.h"

constexpr int FALSE_SILENT_DELAY=10;

class FileGame : public GameBase {
private:
    bool silentMode;
    Steps steps;
    Results expectedResults, actualResults;
    bool testPassed;
    int delay;
    std::vector<std::string> errors;

protected:
    void handleInput() override;

    bool handleRiddles(Player &player) override;

    void render() override;

    bool loadStepsFromFile();

    void onScreenChange(PlayerID id, int room) override {
        actualResults.addScreenChange(gameCycles, id, room);
    }

    void onLifeLost(PlayerID id) override {
        actualResults.addLifeLost(gameCycles, id);
    }

    void onRiddle(PlayerID id, bool correct) override {
        actualResults.addRiddle(gameCycles, id, correct);
    }

    void onGameEnd() override {
        actualResults.addGameEnd(gameCycles,players[0].getScore(), players[1].getScore());
    }

    int getDelay() const override { return silentMode ? 0 : FALSE_SILENT_DELAY; }

    void handleError(const std::string& msg) override;
    void handleMessage(const std::string& msg) override;

public:
    explicit FileGame(bool silent);

    ~FileGame();

    bool didTestPass() const { return testPassed; }
    void compareResults();

};