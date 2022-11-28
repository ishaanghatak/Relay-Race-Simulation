// Ishaan Ghatak
//

#include "SyncAgent.h"


void StartAgent::pause()  {
    std::unique_lock<std::mutex> StartLock(lock);
    //The mutex is shared by all runners in waiting, for all 4 teams.

    StartLock_CV.wait(StartLock);
    //Calling thread must wait for the CV.
}

void StartAgent::proceed()  {
    // Prints race start sequence (also makes it clear that the program has actually started, not just blank for 40+ seconds)
    std::cout << "On your marks..." << std::endl<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Get set..." << std::endl<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "GO!!!" <<std::endl<<endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl<<endl;

    StartLock_CV.notify_all();
    // CV to notify the first runners.
}

void EZAgent::pause() {
    std::unique_lock<std::mutex> EZLock(lock);
    EZLock_CV.wait(EZLock);
}

void EZAgent::proceed() {
    EZLock_CV.notify_one();
    // Releases the runner who is waiting.
}

FinishAgent::FinishAgent(ThreadMap& t) : tMap(t) { }

//Pause is no longer necessary. Proceed is released.
void FinishAgent::pause() { }

void FinishAgent::proceed() {
    std::unique_lock<std::mutex> lk(tum);
    r.setPosition(tMap.getCompetitor());
}

Results FinishAgent::returnResults() { return r; }
