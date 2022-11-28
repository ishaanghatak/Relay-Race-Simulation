// Ishaan Ghatak
//

#pragma once

#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include "Results.h"
#include "ThreadMap.h"

//Class SyncAgent: abstract base class
class SyncAgent {
public:
    SyncAgent() {};
    //Constructor

    // Virtual methods declarations. Overridden by derived classes.
    virtual void pause() = 0;
    virtual void proceed() = 0;
};

//Concrete class derived from SyncAgent
class StartAgent : public SyncAgent {
public:
    StartAgent() {};
    void pause() override;
    void proceed() override;
private:
    std::mutex lock;
    //Mutex lock data member

    std::condition_variable StartLock_CV;
    // Start lock condition variable data member

};

//Concrete class derived from SyncAgent
class EZAgent : public SyncAgent {
public:
    EZAgent() {};
    // Constructor

    void pause();
    void proceed ();
private:
    std::mutex lock;
    //Mutex lock data member

    std::condition_variable EZLock_CV;
        // Start lock condition variable data member

};

class FinishAgent : public SyncAgent {
private:
    Results r;
    std::mutex tum;
    ThreadMap& tMap;
public:
    FinishAgent (ThreadMap& t);
    void proceed();
    void pause();
    Results returnResults();
};
