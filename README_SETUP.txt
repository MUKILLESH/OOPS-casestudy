================================================================
  EMOTION-BASED STUDY ASSISTANT - SETUP GUIDE
================================================================

This project uses C++ and OpenCV to detect your face via webcam
and simulate emotion-based study suggestions.

================================================================
WHAT YOU NEED TO INSTALL
================================================================

--- WINDOWS ---

1. Install MinGW (C++ compiler):
   - Download from: https://sourceforge.net/projects/mingw/
   - During install, check "mingw32-gcc-g++"
   - Add C:\MinGW\bin to your System PATH

2. Install OpenCV:
   - Download from: https://opencv.org/releases/
   - Extract to C:\opencv
   - Add C:\opencv\build\x64\vc16\bin to System PATH
   - For compiling, use:
     g++ main.cpp face_detection.cpp emotion_simulator.cpp decision_engine.cpp productivity_tracker.cpp -o app.exe -IC:\opencv\build\include -LC:\opencv\build\x64\vc16\lib -lopencv_world490

   NOTE: Replace "490" with your OpenCV version number (e.g., 480, 470)

--- MAC ---

1. Install Homebrew (if not installed):
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

2. Install OpenCV:
   brew install opencv

3. Compile:
   g++ main.cpp face_detection.cpp emotion_simulator.cpp decision_engine.cpp productivity_tracker.cpp -o app `pkg-config --cflags --libs opencv4`

--- LINUX (Ubuntu/Debian) ---

1. Install g++ and OpenCV:
   sudo apt update
   sudo apt install g++ libopencv-dev

2. Compile:
   g++ main.cpp face_detection.cpp emotion_simulator.cpp decision_engine.cpp productivity_tracker.cpp -o app `pkg-config --cflags --libs opencv4`

================================================================
HAAR CASCADE FILE (VERY IMPORTANT!)
================================================================

You need the file: haarcascade_frontalface_default.xml

This file comes with OpenCV. Find it at:

- Windows: C:\opencv\build\etc\haarcascades\haarcascade_frontalface_default.xml
- Mac:     /usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml
           or /opt/homebrew/share/opencv4/haarcascades/haarcascade_frontalface_default.xml
- Linux:   /usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml

COPY this file into the SAME FOLDER as your .cpp files!

================================================================
HOW TO COMPILE AND RUN
================================================================

1. Open Terminal/Command Prompt
2. Navigate to the project folder:
   cd path/to/emotion_study_assistant
3. Compile (use the command for your OS from above)
4. Run:
   - Windows: app.exe
   - Mac/Linux: ./app

================================================================
HOW TO USE
================================================================

- The program opens your webcam automatically
- It detects your face and draws a green rectangle
- A random emotion is shown every ~2 seconds
- Study suggestions appear based on the emotion
- Productivity score and study time are shown at the bottom

KEYBOARD CONTROLS:
  q = Quit (shows session summary in terminal)
  m = Toggle between Strict and Relaxed mode

================================================================
OUTPUT FILES
================================================================

- log.txt: Created automatically, contains all emotion readings
           with timestamps from your study session

================================================================
TROUBLESHOOTING
================================================================

Problem: "Could not open webcam"
Fix: Make sure no other app (Zoom, Teams, etc.) is using your camera

Problem: "Could not load Haar Cascade file"
Fix: Copy haarcascade_frontalface_default.xml to the project folder

Problem: "opencv2/opencv.hpp not found"
Fix: Make sure OpenCV is installed and pkg-config can find it
     Try: pkg-config --cflags opencv4

Problem: Program runs but no face detected
Fix: Make sure you have good lighting and face the camera directly

================================================================
PROJECT FILES
================================================================

main.cpp                  - Main program (entry point)
face_detection.h/.cpp     - Face detection using Haar Cascade
emotion_simulator.h/.cpp  - Random emotion generator
decision_engine.h/.cpp    - Study suggestions + Strict/Relaxed mode
productivity_tracker.h/.cpp - Score, timer, logging

Total: 9 source files (4 .h headers + 4 .cpp + 1 main.cpp)

================================================================
