// decision_engine.h - Header file for Decision Engine class
// Maps emotions to study suggestions with Strict/Relaxed modes

#ifndef DECISION_ENGINE_H
#define DECISION_ENGINE_H

#include <string>

class DecisionEngine {
private:
    // true = Strict mode, false = Relaxed mode
    bool strictMode;

public:
    // Constructor - starts in Relaxed mode
    DecisionEngine();

    // Returns a study suggestion based on the emotion
    std::string getSuggestion(std::string emotion);

    // Toggle between Strict and Relaxed mode
    void toggleMode();

    // Returns current mode as a string
    std::string getMode();

    // Returns true if in strict mode
    bool isStrict();
};

#endif
