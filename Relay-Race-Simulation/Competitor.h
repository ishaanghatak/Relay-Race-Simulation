// Ishaan Ghatak
//

#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <mutex>

using namespace std;

class Competitor {
// created in main, never updated, passed to a thread, placed in map
private:
    string teamName;
    string personName;
    int raceTime_ms;
    // integer variable for the race time in ms
public:
    Competitor();
    Competitor(string tN, string pN);
    void setTeam(string tN);
    string getTeam();
    void setPerson(string pN);
    string getPerson();
    static Competitor makeNull();
    void printCompetitor();
    void generateRaceTime();
    // the function generates the race time
    int getRaceTime_ms();
    // get race time in ms as integer value
    float getRaceTime();
    // get the race time in seconds
};

// RandomTwister is used instead of rand, which is not thread safe.
class RandomTwister {
private:
    std::mt19937 rnd;// mt19937 is a standard Mersenne twister engine class
    std::mutex mu;
public:
    RandomTwister() : rnd(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {  }
    int randomPeriod(int l, int u) {
        std::lock_guard<std::mutex> guard (mu);
        std::uniform_int_distribution<int> dis(l, u); //generate a random integer between l and u
        int n = dis(rnd);
        return n;
    }
};
