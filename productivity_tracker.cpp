// productivity_tracker.cpp - Implementation of Productivity Tracker class
// Handles scoring, timing, logging, and session summary

#include "productivity_tracker.h"
#include <iostream>

// Constructor: Initialize all values and open log file
ProductivityTracker::ProductivityTracker() {
    focusedCount = 0;
    distractedCount = 0;
    totalCount = 0;
    totalStudyTime = 0;
    isStudying = false;
    studyStartTime = 0;

    // Open log file in append mode
    logFile.open("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "=== New Session Started ===" << std::endl;
        std::cout << "Log file opened successfully." << std::endl;
    } else {
        std::cout << "Warning: Could not open log.txt" << std::endl;
    }
}

// Destructor: Close the log file
ProductivityTracker::~ProductivityTracker() {
    if (logFile.is_open()) {
        logFile << "=== Session Ended ===" << std::endl;
        logFile.close();
    }
}

// Update the tracker with a new emotion
void ProductivityTracker::update(std::string emotion) {
    totalCount++;

    // Happy and Neutral = focused
    if (emotion == "Happy" || emotion == "Neutral") {
        focusedCount++;
    }
    // Sad, Angry, Sleepy = distracted
    else {
        distractedCount++;
    }

    // Print BEEP alert for negative emotions
    if (emotion == "Sleepy" || emotion == "Angry") {
        std::cout << "BEEP! Alert: You are " << emotion << "!" << std::endl;
    }

    // Log the emotion to file
    logEmotion(emotion);
}

// Start the study timer when face is detected
void ProductivityTracker::faceDetected() {
    if (!isStudying) {
        studyStartTime = time(0);  // Record current time
        isStudying = true;
    }
}

// Pause the study timer when face is not detected
void ProductivityTracker::faceNotDetected() {
    if (isStudying) {
        // Add elapsed time to total
        time_t now = time(0);
        totalStudyTime += difftime(now, studyStartTime);
        isStudying = false;
    }
}

// Calculate productivity score as percentage
double ProductivityTracker::getScore() {
    if (totalCount == 0) {
        return 0.0;
    }
    return ((double)focusedCount / totalCount) * 100.0;
}

// Get total study time in seconds
double ProductivityTracker::getStudyTime() {
    double currentTotal = totalStudyTime;
    // If currently studying, add time since last start
    if (isStudying) {
        time_t now = time(0);
        currentTotal += difftime(now, studyStartTime);
    }
    return currentTotal;
}

// Get focused count
int ProductivityTracker::getFocused() {
    return focusedCount;
}

// Get distracted count
int ProductivityTracker::getDistracted() {
    return distractedCount;
}

// Print final session summary to console
void ProductivityTracker::printSummary() {
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "       SESSION SUMMARY                  " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Focused count (Happy/Neutral): " << focusedCount << std::endl;
    std::cout << "Distracted count (Sad/Angry/Sleepy): " << distractedCount << std::endl;
    std::cout << "Total readings: " << totalCount << std::endl;
    std::cout << "Productivity Score: " << getScore() << "%" << std::endl;
    std::cout << "Total Study Time: " << getStudyTime() << " seconds" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Write emotion entry to log.txt with timestamp
void ProductivityTracker::logEmotion(std::string emotion) {
    if (logFile.is_open()) {
        // Get current time as string
        time_t now = time(0);
        char* timeStr = ctime(&now);
        // Remove newline from ctime output
        std::string timeString(timeStr);
        timeString.pop_back();

        logFile << "[" << timeString << "] Emotion: " << emotion << std::endl;
    }
}
