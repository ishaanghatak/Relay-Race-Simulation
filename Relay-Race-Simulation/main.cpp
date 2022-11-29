// Ishaan Ghatak
//

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

#include "Competitor.h"
#include "ThreadMap.h"
#include "SyncAgent.h"


std::mutex mu_cout;
// Prevention of unwanted thread inter-leavings for cout

//Function uses SyncAgent for the first thread, then EZAgent for the following threads
void run(Competitor& c, ThreadMap& tm, SyncAgent& lineUp, SyncAgent& nextRunner) {
    tm.insertThreadPair(c);
    //Insert thread pair in a ThreadMap
    lineUp.pause();

    //run sleeps for appropriate amount of time generated using getRaceTime_ms() which uses the RandomTwister engine
    std::this_thread::sleep_for(std::chrono::milliseconds(c.getRaceTime_ms()));
    //Simulation

    nextRunner.proceed();
    // Baton exchange to release the waiting runner (next thread)

    std::lock_guard<std::mutex> locker(mu_cout);
    //Lock guard - cout is made a critical section; 'unlocks' through the destructor.
}

int main() {
    const int NO_TEAMS = 4;
    const int NO_MEMBERS = 4;

    srand(time(0));
    const int NO_EXCHANGES = (NO_MEMBERS - 1);
    Competitor c[NO_MEMBERS][NO_TEAMS];
    ThreadMap tm;

    std::thread Comps[NO_MEMBERS][NO_TEAMS];
    // Thread declaration

    StartAgent StartRace;
    // StartAgent to release the initial threads at the beginning of relay race.
    EZAgent ExchangeBaton[NO_EXCHANGES][NO_TEAMS];
    //EZAgent to unlock subsequent threads once the previous runner has finished their section.

    FinishAgent FinishRace(ref(tm));
    //Once each runner in each team is done, the results of the race must be stored.


    string teamName, competitorName;
    ifstream Names("nameList.txt");
    // Text file contains names of Olympic sprinters.

    // For loop - Concurrent part of code
    for (int runner=0; runner<NO_MEMBERS; runner++)
        for (int team=0; team<NO_TEAMS; team++)
        {
            switch (team) {
                case 0:
                    teamName = "Alpha";
                    break;
                case 1:
                    teamName = "Beta";
                    break;
                case 2:
                    teamName = "Gamma";
                    break;
                case 3:
                    teamName = "Delta";
                    break;
                default:
                    teamName = "Team #" + std::to_string(team) + " (unnamed)";
            }
            getline(Names, competitorName);
            c[runner][team] = Competitor(teamName, competitorName);

            c[runner][team].generateRaceTime();
            if (runner == 0)
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(StartRace), ref(ExchangeBaton[runner][team]));

                //For the fourth (the last) runner within each team.
            else if (runner == NO_EXCHANGES)
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(ExchangeBaton[runner-1][team]), ref(FinishRace));
            else
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(ExchangeBaton[runner-1][team]), ref(ExchangeBaton[runner][team])); //initialising threads, waits on its EZAgent and unlocks the next
        }
    Names.close();
    StartRace.proceed();
    //Threads are released for the start of the race.

    for (int i=0; i<NO_MEMBERS; i++)
        for (int j=0; j<NO_TEAMS; j++)
        {
            Comps[i][j].join();
        }
        // End of concurrent section.
        FinishRace.returnResults().printResults(tm);
        // Results are printed and formatted appropriately from Results.
}
