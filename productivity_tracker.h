// productivity_tracker.h - Header file for Productivity Tracker class
// Tracks focus, distractions, study time, and logs to file

#ifndef PRODUCTIVITY_TRACKER_H
#define PRODUCTIVITY_TRACKER_H

#include <string>
#include <fstream>
#include <ctime>

class ProductivityTracker {
private:
    int focusedCount;      // Times user was Happy or Neutral
    int distractedCount;   // Times user was Sad, Angry, or Sleepy
    int totalCount;        // Total emotion readings

    time_t studyStartTime; // When studying started
    double totalStudyTime; // Total seconds spent studying
    bool isStudying;       // Whether user is currently studying (face detected)

    std::ofstream logFile; // File to save emotion logs

public:
    // Constructor - opens log file
    ProductivityTracker();

    // Destructor - closes log file
    ~ProductivityTracker();

    // Update tracker with a new emotion reading
    void update(std::string emotion);

    // Call when face is detected (start timer)
    void faceDetected();

    // Call when face is NOT detected (pause timer)
    void faceNotDetected();

    // Calculate productivity score (0 to 100)
    double getScore();

    // Get total study time in seconds
    double getStudyTime();

    // Get focused count
    int getFocused();

    // Get distracted count
    int getDistracted();

    // Print session summary to console
    void printSummary();

    // Log an emotion to log.txt
    void logEmotion(std::string emotion);
};

#endif
