// face_detection.cpp - Implementation of Face Detection class
// Uses Haar Cascade to find faces in each video frame

#include "face_detection.h"
#include <iostream>

// Constructor: Load the Haar Cascade XML file
FaceDetector::FaceDetector(std::string cascadePath) {
    loaded = faceCascade.load(cascadePath);
    if (!loaded) {
        std::cout << "ERROR: Could not load Haar Cascade file: " << cascadePath << std::endl;
        std::cout << "Make sure 'haarcascade_frontalface_default.xml' is in the same folder." << std::endl;
    } else {
        std::cout << "Haar Cascade loaded successfully!" << std::endl;
    }
}

// Detect faces in the given frame
std::vector<cv::Rect> FaceDetector::detectFaces(cv::Mat frame) {
    std::vector<cv::Rect> faces;

    // Convert frame to grayscale (Haar Cascade works on gray images)
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // Detect faces - returns rectangles around each face found
    faceCascade.detectMultiScale(gray, faces, 1.3, 5);

    return faces;
}

// Draw green rectangles around detected faces
void FaceDetector::drawFaces(cv::Mat &frame, std::vector<cv::Rect> faces) {
    for (int i = 0; i < faces.size(); i++) {
        // Draw a green rectangle around each face
        cv::rectangle(frame, faces[i], cv::Scalar(0, 255, 0), 2);
    }
}

// Check if cascade file loaded properly
bool FaceDetector::isLoaded() {
    return loaded;
}
