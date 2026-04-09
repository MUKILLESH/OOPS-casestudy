// emotion_simulator.h - Header file for Emotion Simulator class
// Simulates emotion detection using random values

#ifndef EMOTION_SIMULATOR_H
#define EMOTION_SIMULATOR_H

#include <string>

class EmotionSimulator {
private:
    // Stores the current detected emotion
    std::string currentEmotion;

    // Array of possible emotions
    std::string emotions[5];

public:
    // Constructor - sets up the list of emotions
    EmotionSimulator();

    // Generates a random emotion (simulates real detection)
    std::string detectEmotion();

    // Returns the last detected emotion
    std::string getCurrentEmotion();
};

#endif
