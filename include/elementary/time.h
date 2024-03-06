#pragma once

#include <chrono>

class AppWindow;

class Time {
public:
    static float TimeScale;

    static float GetTime();
    static float GetDeltaTime();
    static float GetTimeReal();
    static float GetDeltaTimeReal();
    static unsigned int GetFrame();
private:
    static std::chrono::high_resolution_clock::duration _time_since_start;
    static std::chrono::high_resolution_clock::duration _time_since_start_real;
    static std::chrono::high_resolution_clock::time_point _previous_frame;
    static float _time;
    static float _delta_time;
    static float _time_real;
    static float _delta_time_real;
    static unsigned int _frame_count; 

    static void _InitTime();
    static void _UpdateTime();

    friend class AppWindow;
};