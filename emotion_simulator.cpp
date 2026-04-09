// emotion_simulator.cpp - Implementation of Emotion Simulator class
// Uses rand() to simulate emotion detection

#include "emotion_simulator.h"
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

// Constructor: Initialize the list of 5 emotions
EmotionSimulator::EmotionSimulator() {
    emotions[0] = "Happy";
    emotions[1] = "Sad";
    emotions[2] = "Angry";
    emotions[3] = "Neutral";
    emotions[4] = "Sleepy";

    currentEmotion = "Neutral";

    // Seed random number generator so we get different results each time
    srand(time(0));
}

// Pick a random emotion from the list
std::string EmotionSimulator::detectEmotion() {
    // Generate random index between 0 and 4
    int index = rand() % 5;
    currentEmotion = emotions[index];
    return currentEmotion;
}

// Return the last detected emotion
std::string EmotionSimulator::getCurrentEmotion() {
    return currentEmotion;
}
