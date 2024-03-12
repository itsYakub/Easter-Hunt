#pragma once

class Timer {
private:
    float m_InitialTime;
    float m_Time;

public:
    Timer(float time);
    void Process(float deltaTime);
    void Restart();
    void Restart(float time);
    bool Finished();

    float Get();
    float GetFraction();
};