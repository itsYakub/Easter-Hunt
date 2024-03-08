#include "Timer.hpp"

Timer::Timer(float time) : m_Time(time) { }
void Timer::Process(float deltaTime) { m_Time -= deltaTime; }
void Timer::Restart(float time) { m_Time = time; }
bool Timer::Finished() { return m_Time <= 0.0f; }