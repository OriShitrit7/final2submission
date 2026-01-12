#include "FileGame.h"

/*void getAllBoardFileNames(std::vector<std::string>& vec_to_fill) {
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        auto filename = entry.path().filename();
        auto filenameStr = filename.string();
        if (filenameStr.substr(0, 5) == "board" && filename.extension() == ".screen") {
            std::cout << " ^ added!!\n";
            vec_to_fill.push_back(filenameStr);
        }
    }
}*/

void FileGame::handleError(const std::string &msg) {
    errors.push_back("Cycle " + std::to_string(gameCycles) + ": " + msg);
    testPassed = false;
}

void FileGame::handleMessage(const std::string &msg) {
    if (!silentMode) {
        //?
    }
}

FileGame::FileGame(bool silent) : GameBase(), silentMode(silent) {
    setGame();

    steps = Steps::loadSteps("adv-world.steps");
    expectedResults = Results::loadResults("adv - world.results");

    loadGameFiles();
    initGame();
}

void FileGame::compareResults() {

}


void FileGame::render() {
    if (!silentMode) GameBase::render();
}

bool FileGame::loadStepsFromFile() {
}


void FileGame::handleInput() {
    if (steps.isEmpty()) { // flag for an error?
        isRunning=false;      // leave run()
        return;
    }

    if (steps.isNextStepOnIteration(gameCycles)) {
        char ch = steps.popStep();
        processKey(ch);
    }
}

bool FileGame::handleRiddles(Player& player) {
    if (silentMode) {
        if (expectedResults.hasNoMoreRiddles()) {
            handleError("Mismatch: More riddles encountered than expected in results file.");
            return false;
        }
        bool result = expectedResults.getNextRiddleResult();
        return GameBase::handleRiddles(player, result);
    }

    return GameBase::handleRiddles(player);
}
;