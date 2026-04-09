// face_detection.h - Header file for Face Detection class
// Uses OpenCV Haar Cascade to detect faces in webcam frames

#ifndef FACE_DETECTION_H
#define FACE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class FaceDetector {
private:
    // Haar Cascade classifier object
    cv::CascadeClassifier faceCascade;
    // Whether the cascade file loaded successfully
    bool loaded;

public:
    // Constructor - loads the Haar Cascade XML file
    FaceDetector(std::string cascadePath);

    // Detects faces in a given frame and returns their positions
    std::vector<cv::Rect> detectFaces(cv::Mat frame);

    // Draws rectangles around detected faces
    void drawFaces(cv::Mat &frame, std::vector<cv::Rect> faces);

    // Returns true if cascade file was loaded successfully
    bool isLoaded();
};

#endif
