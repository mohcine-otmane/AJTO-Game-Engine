#ifndef SIGNALS_H
#define SIGNALS_H

#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <SFML/Graphics.hpp>

struct Signal {
    float duration;
    sf::Clock startTime;
    bool repeating;
    int repeatCount;
    std::string tag;
    bool paused;
    std::function<void()> onEmit;
    std::function<void()> onExpire;
};

class Signals {
public:
    Signals();
    void Emit(float duration, bool repeating = false, int repeatCount = 0, const std::string& tag = "");
    void Start();
    void Stop();
    void PauseSignal(const std::string& tag);
    void ResumeSignal(const std::string& tag);
    void ClearSignals(const std::string& tag = "");
    ~Signals();

private:
    void Update();  // Internal thread loop
    std::vector<Signal> activeSignals;
    std::mutex signalMutex;  // For thread-safe access
    bool running;
    std::thread signalThread;
};

#endif
