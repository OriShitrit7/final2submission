#include <limits>
#include <fstream>
#include "Results.h"

Results Results::loadResults(const std::string& filename) {
    std::ifstream results_file(filename);
    Results results;
    size_t size;
    results_file >> size;
    while (!results_file.eof() && size-- != 0) {
        size_t iteration;
        int result;
        results_file >> iteration >> result;
        results.addResult(iteration, static_cast<ResultValue>(result));
    }
    return results;
}

void Results::saveResults(const std::string& filename) const {
    std::ofstream file(filename);
    file << events.size() << '\n';

    for (const auto& e : events) {
        switch (e.type) {
            case SCREEN_CHANGE:
                // cycle SCREEN player room
                file << e.cycle << " SCREEN " << e.player << ' ' << e.data1 << '\n';
                break;
            case LIFE_LOST:
                // cycle LIFE player
                file << e.cycle << " LIFE " << e.player << '\n';
                break;
            case RIDDLE_ANSWERED:
                // cycle RIDDLE player correct
                file << e.cycle << " RIDDLE " << e.player << ' ' << e.correct << '\n';
                break;
            case GAME_END:
                // cycle END score1 score2
                file << e.cycle << " END " << e.data1 << ' ' << e.data2 << '\n';
                break;
        }
    }
    file.close();
}

/*void Results::saveResults(const std::string& filename) {
    std::ofstream results_file(filename);
    results_file << results.size();
    for (const auto& result : results) {
        results_file << '\n' << result.first << ' ' << result.second;
    }
    results_file.close();
}*/

size_t Results::getNextBombIteration() {
    if (!results.empty() && results.front().second == hitBomb)
        return results.front().first;

    return std::numeric_limits<size_t>::max(); // a big number we will never reach
}

;
