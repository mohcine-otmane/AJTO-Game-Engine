/*--- A signal is an information emitted after an event or an action happens  ---*/
/*--- Example: The death of the player would be communicated as  SignalSystem.Emit("PlayerDead") ---*/
#ifndef SIGNALS_H
#define SIGNALS_H

#include <vector>
#include <string>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Signal {
    std::string tag;
    bool emitted;
    bool repeating;  // New flag to indicate whether this signal repeats or not

    Signal(const std::string &t, bool repeat) : tag(t), emitted(true), repeating(repeat) {}
};

class Signals {
public:
    Signals() {}

    void Emit(const std::string &tag, bool repeating = false) {
        // Check if the signal already exists
        if (emittedTags.find(tag) == emittedTags.end()) {
            VecSignals.emplace_back(tag, repeating);
            emittedTags.insert(tag);  // Track the signal tag to avoid duplicates
            std::cout << "Signal emitted: " << tag << std::endl;
        } else if (repeating) {
            // If the signal repeats, update its state
            for (auto &signal : VecSignals) {
                if (signal.tag == tag) {
                    signal.emitted = true;
                }
            }
        }
    }

    bool HasEmitted(const std::string &tag) {
        for (auto &signal : VecSignals) {
            if (signal.tag == tag && signal.emitted) {
                if (!signal.repeating) {
                    signal.emitted = false;  // Automatically reset if not repeating
                    emittedTags.erase(tag);  // Remove from the emitted set
                }
                return true;
            }
        }
        return false;
    }

    void Reset(const std::string &tag) {
        emittedTags.erase(tag);
        for (auto &signal : VecSignals) {
            if (signal.tag == tag) {
                signal.emitted = false;  // Manually reset the signal
            }
        }
    }

    ~Signals() {}

private:
    std::vector<Signal> VecSignals;
    std::unordered_set<std::string> emittedTags;  // Keeps track of already emitted signals
};

#endif

