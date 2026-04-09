# Emotion-Based Study Assistant

A C++ project using OpenCV and Haar Cascade for face detection with simulated emotion-based study suggestions.

## Files

| File | Purpose |
|------|---------|
| `main.cpp` | Main program - webcam loop, keyboard controls |
| `face_detection.h / .cpp` | Face detection using Haar Cascade |
| `emotion_simulator.h / .cpp` | Random emotion simulation |
| `decision_engine.h / .cpp` | Study suggestions + Strict/Relaxed mode |
| `productivity_tracker.h / .cpp` | Score tracking, timer, log file |

## Setup

- **Windows**: Install MinGW + OpenCV
- **Mac**: `brew install opencv`
- **Linux**: `sudo apt install g++ libopencv-dev`

Copy `haarcascade_frontalface_default.xml` into this folder. See `README_SETUP.txt` for details.

## Compile & Run

```bash
g++ main.cpp face_detection.cpp emotion_simulator.cpp decision_engine.cpp productivity_tracker.cpp -o app `pkg-config --cflags --libs opencv4`
./app
```

## Controls

- `q` — Quit and show session summary
- `m` — Toggle Strict/Relaxed mode
