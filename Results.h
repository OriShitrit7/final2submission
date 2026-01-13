#pragma once
#include <list>
#include <string>
//#include <fstream>
#include "GameDefs.h"

class Results {
public:
    enum EventType { SCREEN_CHANGE, LIFE_LOST, RIDDLE_ANSWERED, GAME_END };

    struct Event {
        size_t cycle;
        EventType type;
        PlayerID player;
        int data1;       // room number / score1
        int data2;       // score2 (for GAME_END)
        bool correct;    // for RIDDLE
    };

private:
    std::list<Event> events;

public:
    static Results loadResults(const std::string& filename);

    void saveResults(const std::string &filename) const;

    /*void addResult(size_t iteration, EventType type) {
        events.emplace_back(Event{iteration, type, PLAYER_1, 0, 0, false});
    }*/

    void addScreenChange(size_t cycle, PlayerID player, int room) {
        events.push_back({cycle, SCREEN_CHANGE, player, room, 0, false});
    }

    void addLifeLost(size_t cycle, PlayerID player) {
        events.push_back({cycle, LIFE_LOST, player, 0, 0, false});
    }

    void addRiddle(size_t cycle, PlayerID player, bool correct) {
        events.push_back({cycle, RIDDLE_ANSWERED, player, 0, 0, correct});
    }

    void addGameEnd(size_t cycle, int score1, int score2) {
        events.push_back({cycle, GAME_END, PLAYER_1, score1, score2, false});
    }

    bool hasMoreEvents() const { return !events.empty(); }

    Event peekEvent() const {
        return events.empty() ? Event{0, GAME_END, PLAYER_1, 0, 0, false} : events.front();
    }

    Event popEvent() {
        if (events.empty()) return {0, GAME_END, PLAYER_1, 0, 0, false};
        Event e = events.front();
        events.pop_front();
        return e;
    }

    bool getNextRiddleResult() {
        for (auto& e : events) {
            if (e.type == RIDDLE_ANSWERED) {
                return e.correct;
            }
        }
        return false;
    }

    static std::pair<size_t, ResultValue> popResult() {
        if (results.empty()) return { 0, Results::noResult };
        auto result = results.front();
        results.pop_front();
        return result;
    }
    static bool isFinishedBy(size_t iteration) {
        return results.empty() || results.back().first <= iteration;
    }
    static size_t getNextBombIteration() ;
};
