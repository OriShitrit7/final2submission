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

public:
    FileGame(bool silent = false);
    ~FileGame();

    bool didTestPass() const { return testPassed; }
    void compareResults();

    int getDelay(){return silentMode?0:50;}

    //bool loadStepsFromFile(const std::string& filename) {steps=loadSteps();}

};