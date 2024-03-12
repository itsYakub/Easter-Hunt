#include "Timer.hpp"

Timer::Timer(float time) : m_InitialTime(time), m_Time(time) { }
void Timer::Process(float deltaTime) { m_Time -= deltaTime; }
void Timer::Restart() { m_Time = m_InitialTime; }
void Timer::Restart(float time) { m_InitialTime = time; m_Time = time; }
bool Timer::Finished() { return m_Time <= 0.0f; }
float Timer::Get() { return m_Time; }
float Timer::GetFraction() { return 1.0f - (m_InitialTime / m_Time); }
