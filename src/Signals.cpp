
#include "Signals.hpp"

Signals::Signals() : running(false) {}

void Signals::Emit(float duration, bool repeating, int repeatCount, const std::string& tag) {
    std::lock_guard<std::mutex> lock(signalMutex);
    Signal newSignal;
    newSignal.duration = duration;
    newSignal.repeating = repeating;
    newSignal.repeatCount = repeatCount;
    newSignal.tag = tag;
    newSignal.paused = false;
    activeSignals.push_back(newSignal);
}

void Signals::Start() {
    if (!running) {
        running = true;
        signalThread = std::thread(&Signals::Update, this);
    }
}

void Signals::Stop() {
    running = false;
    if (signalThread.joinable()) {
        signalThread.join();
    }
}

void Signals::Update() {
    while (running) {
        std::lock_guard<std::mutex> lock(signalMutex);  // Ensure thread-safe access
        for (auto it = activeSignals.begin(); it != activeSignals.end();) {
            if (!it->paused && it->startTime.getElapsedTime().asSeconds() >= it->duration) {
                if (it->onExpire) {
                    it->onExpire();  // Call expiration callback if it exists
                }

                if (it->repeating && (it->repeatCount == 0 || --it->repeatCount > 0)) {
                    it->startTime.restart();  // Restart if repeating
                    ++it;
                } else {
                    it = activeSignals.erase(it);  // Remove expired signal
                }
            } else {
                ++it;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep to reduce CPU usage
    }
}

void Signals::PauseSignal(const std::string& tag) {
    std::lock_guard<std::mutex> lock(signalMutex);
    for (auto& signal : activeSignals) {
        if (signal.tag == tag) {
            signal.paused = true;
        }
    }
}

void Signals::ResumeSignal(const std::string& tag) {
    std::lock_guard<std::mutex> lock(signalMutex);
    for (auto& signal : activeSignals) {
        if (signal.tag == tag) {
            signal.paused = false;
        }
    }
}

void Signals::ClearSignals(const std::string& tag) {
    std::lock_guard<std::mutex> lock(signalMutex);
    if (tag.empty()) {
        activeSignals.clear();
    } else {
        activeSignals.erase(
            std::remove_if(activeSignals.begin(), activeSignals.end(),
                           [&tag](const Signal& signal) { return signal.tag == tag; }),
            activeSignals.end());
    }
}

Signals::~Signals() {
    Stop();
}
