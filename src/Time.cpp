#include "elementary/time.h"

float Time::TimeScale = 1.0f;

float Time::GetTime() {
    return _time;
}

float Time::GetDeltaTime() {
    return _delta_time;
}

float Time::GetTimeReal() {
    return _time_real;
}

float Time::GetDeltaTimeReal() {
    return _delta_time_real;
}

unsigned int Time::GetFrame() {
    return _frame_count;
}

std::chrono::high_resolution_clock::duration Time::_time_since_start = std::chrono::high_resolution_clock::duration::zero();
std::chrono::high_resolution_clock::duration Time::_time_since_start_real = std::chrono::high_resolution_clock::duration::zero();
std::chrono::high_resolution_clock::time_point Time::_previous_frame = std::chrono::high_resolution_clock::now();
float Time::_time = 0.0f;
float Time::_delta_time = 0.0f;
float Time::_time_real = 0.0f;
float Time::_delta_time_real = 0.0f;
unsigned int Time::_frame_count = 0;

void Time::_InitTime() {
    _time_since_start = std::chrono::high_resolution_clock::duration::zero();
    _time_since_start_real = std::chrono::high_resolution_clock::duration::zero();
    _previous_frame = std::chrono::high_resolution_clock::now();
    _time = 0.0f;
    _delta_time = 0.0f;
    _time_real = 0.0f;
    _delta_time_real = 0.0f;
    _frame_count = 0;
}

void Time::_UpdateTime() {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::duration delta = now - _previous_frame;

    _time_since_start_real += delta;
    _time_real = std::chrono::duration_cast<std::chrono::microseconds>(_time_since_start_real).count() * 0.000001f;
    _delta_time_real  = std::chrono::duration_cast<std::chrono::microseconds>(delta).count() * 0.000001f;
    delta *= TimeScale;
    _time_since_start += delta;

    _time = std::chrono::duration_cast<std::chrono::microseconds>(_time_since_start).count() * 0.000001f;
    _delta_time = std::chrono::duration_cast<std::chrono::microseconds>(delta).count() * 0.000001f;
    _frame_count++;

    _previous_frame = now;
}