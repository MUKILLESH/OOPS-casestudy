// decision_engine.cpp - Implementation of Decision Engine class
// Provides study suggestions based on detected emotion

#include "decision_engine.h"

// Constructor: Start in Relaxed mode by default
DecisionEngine::DecisionEngine() {
    strictMode = false;
}

// Return a suggestion based on emotion and current mode
std::string DecisionEngine::getSuggestion(std::string emotion) {
    if (emotion == "Happy") {
        return "Continue studying! You're doing great!";
    }
    else if (emotion == "Sad") {
        if (strictMode) {
            return "WARNING: You look sad! Take a break NOW!";
        } else {
            return "Take a short break, you'll feel better.";
        }
    }
    else if (emotion == "Angry") {
        if (strictMode) {
            return "ALERT: You look angry! Stop and calm down immediately!";
        } else {
            return "Relax and calm down, then continue.";
        }
    }
    else if (emotion == "Sleepy") {
        if (strictMode) {
            return "DANGER: You are sleepy! Take rest RIGHT NOW!";
        } else {
            return "Take some rest, sleep is important.";
        }
    }
    else { // Neutral
        return "Keep going, you're on track!";
    }
}

// Switch between Strict and Relaxed mode
void DecisionEngine::toggleMode() {
    strictMode = !strictMode;
}

// Get current mode as text
std::string DecisionEngine::getMode() {
    if (strictMode) {
        return "STRICT";
    } else {
        return "RELAXED";
    }
}

// Check if strict mode is on
bool DecisionEngine::isStrict() {
    return strictMode;
}
