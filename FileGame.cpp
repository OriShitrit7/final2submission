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

FileGame::FileGame(bool silent) : GameBase(), silentMode(silent) {
    setGame();

    steps = Steps::loadSteps("adv-world.steps");
    expectedResults = Results::loadResults("adv - world.results");

    loadGameFiles();
    initGame();
}



void FileGame::handleInput() {

    if (steps.isEmpty()) { // flag for an error?
        setRunning(false);      // leave run()
        return;
    }

    if (steps.isNextStepOnIteration(getGameCycles())) {
        char ch = steps.popStep();
        processKey(ch);
    }
}

FileGame::FileGame(bool silent) {

}
}
