// main.cpp - Main program for Emotion-Based Study Assistant
// This is the entry point of the program
// It opens the webcam, detects faces, simulates emotions,
// and displays study suggestions with productivity tracking

#include <iostream>
#include <opencv2/opencv.hpp>

// Include our custom header files
#include "face_detection.h"
#include "emotion_simulator.h"
#include "decision_engine.h"
#include "productivity_tracker.h"

int main() {
    // Print welcome message
    std::cout << "========================================" << std::endl;
    std::cout << " Emotion-Based Study Assistant          " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  q = Quit the program" << std::endl;
    std::cout << "  m = Toggle Strict/Relaxed mode" << std::endl;
    std::cout << "========================================" << std::endl;

    // --- Step 1: Create objects for each module ---

    // Face detector - loads the Haar Cascade XML file
    // Make sure this XML file is in the same folder as the program
    FaceDetector faceDetector("haarcascade_frontalface_default.xml");g++ main.cpp face_detection.cpp emotion_simulator.cpp decision_engine.cpp productivity_tracker.cpp -o app.exe -IC:\opencv\build\include -LC:\opencv\build\x64\vc16\lib -lopencv_world490


    // Check if the cascade file loaded properly
    if (!faceDetector.isLoaded()) {
        std::cout << "Cannot start without Haar Cascade file. Exiting." << std::endl;
        return -1;
    }

    // Emotion simulator - generates random emotions
    EmotionSimulator emotionSim;

    // Decision engine - gives study suggestions
    DecisionEngine decisionEng;

    // Productivity tracker - tracks focus and study time
    ProductivityTracker tracker;

    // --- Step 2: Open the webcam ---
    // 0 means the default camera on your laptop
    cv::VideoCapture camera(0);

    // Check if camera opened successfully
    if (!camera.isOpened()) {
        std::cout << "ERROR: Could not open webcam!" << std::endl;
        std::cout << "Make sure your webcam is connected and not used by another app." << std::endl;
        return -1;
    }

    std::cout << "Webcam opened successfully! Starting..." << std::endl;

    // Variables for emotion update timing
    // We only change emotion every 60 frames (~2 seconds) to avoid flickering
    int frameCount = 0;
    int emotionUpdateInterval = 60;
    std::string currentEmotion = "Neutral";
    std::string currentSuggestion = "Keep going, you're on track!";

    // --- Step 3: Main loop - runs until user presses 'q' ---
    while (true) {
        // Read a frame from the webcam
        cv::Mat frame;
        camera >> frame;

        // Check if frame is empty (camera error)
        if (frame.empty()) {
            std::cout << "ERROR: Empty frame from camera!" << std::endl;
            break;
        }

        // Flip the frame horizontally so it looks like a mirror
        cv::flip(frame, frame, 1);

        // --- Step 4: Detect faces ---
        std::vector<cv::Rect> faces = faceDetector.detectFaces(frame);

        // --- Step 5: Check if face is detected ---
        if (faces.size() > 0) {
            // Face found! Draw rectangle around it
            faceDetector.drawFaces(frame, faces);

            // Start the study timer
            tracker.faceDetected();

            // Update emotion every few frames (not every single frame)
            frameCount++;
            if (frameCount >= emotionUpdateInterval) {
                // Simulate detecting an emotion
                currentEmotion = emotionSim.detectEmotion();

                // Get study suggestion based on emotion
                currentSuggestion = decisionEng.getSuggestion(currentEmotion);

                // Update productivity tracker
                tracker.update(currentEmotion);

                // Reset frame counter
                frameCount = 0;
            }

            // --- Step 6: Display information on screen ---

            // Show emotion text (yellow color)
            cv::putText(frame, "Emotion: " + currentEmotion,
                        cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX,
                        0.7, cv::Scalar(0, 255, 255), 2);

            // Show suggestion text (green color)
            cv::putText(frame, "Tip: " + currentSuggestion,
                        cv::Point(10, 60), cv::FONT_HERSHEY_SIMPLEX,
                        0.5, cv::Scalar(0, 255, 0), 1);

        } else {
            // No face detected - show warning
            tracker.faceNotDetected();

            // Display warning message (red color)
            cv::putText(frame, "WARNING: User not present!",
                        cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX,
                        0.8, cv::Scalar(0, 0, 255), 2);

            // Reset frame counter so emotion updates immediately when face returns
            frameCount = emotionUpdateInterval;
        }

        // --- Always show these on screen ---

        // Show productivity score (white color)
        char scoreText[50];
        sprintf(scoreText, "Productivity: %.1f%%", tracker.getScore());
        cv::putText(frame, scoreText,
                    cv::Point(10, frame.rows - 60), cv::FONT_HERSHEY_SIMPLEX,
                    0.6, cv::Scalar(255, 255, 255), 2);

        // Show study time (white color)
        char timeText[50];
        sprintf(timeText, "Study Time: %.0f sec", tracker.getStudyTime());
        cv::putText(frame, timeText,
                    cv::Point(10, frame.rows - 35), cv::FONT_HERSHEY_SIMPLEX,
                    0.6, cv::Scalar(255, 255, 255), 2);

        // Show current mode (cyan color)
        cv::putText(frame, "Mode: " + decisionEng.getMode(),
                    cv::Point(10, frame.rows - 10), cv::FONT_HERSHEY_SIMPLEX,
                    0.6, cv::Scalar(255, 255, 0), 2);

        // --- Step 7: Show the frame in a window ---
        cv::imshow("Emotion Study Assistant", frame);

        // --- Step 8: Handle keyboard input ---
        // Wait 30ms for a key press
        int key = cv::waitKey(30);

        // 'q' or 'Q' = quit the program
        if (key == 'q' || key == 'Q') {
            // Stop the timer if still running
            tracker.faceNotDetected();
            break;
        }

        // 'm' or 'M' = toggle study mode
        if (key == 'm' || key == 'M') {
            decisionEng.toggleMode();
            std::cout << "Mode changed to: " << decisionEng.getMode() << std::endl;
        }
    }

    // --- Step 9: Cleanup and show summary ---

    // Print session summary to console
    tracker.printSummary();

    // Release the camera
    camera.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    std::cout << "Program ended. Check log.txt for emotion history." << std::endl;

    return 0;
}
