#pragma once
#include <iosfwd>
#include <list>

class Steps {
    std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
    static Steps loadSteps(const std::string& filename);
    void saveSteps(const std::string& filename) const;
    void addStep(size_t iteration, char step) {
        steps.emplace_back( iteration, step );
    }

    bool isNextStepOnIteration(size_t iteration) const {
        return !steps.empty() && steps.front().first == iteration;
    }

    char popStep() {
        char step = steps.front().second;
        steps.pop_front();
        return step;
    }

    bool isEmpty() const {return steps.empty();}

};