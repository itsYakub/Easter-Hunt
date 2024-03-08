#pragma once

class Timer {
private:
    float m_Time;

public:
    Timer(float time);
    void Process(float deltaTime);
    void Restart(float time);
    bool Finished();
};