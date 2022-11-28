// Ishaan Ghatak
//

#include "ThreadMap.h"


ThreadMap::ThreadMap() {};

//Thread pair: creates a thread ID and competitor to store in the map through insert member function.
void ThreadMap::insertThreadPair(Competitor c) {
    threadComp.insert(std::pair<std::thread::id, Competitor>(std::this_thread::get_id(), c));
}

Competitor ThreadMap::getCompetitor() {
	std::map <std::thread::id, Competitor>::iterator it = threadComp.find(std::this_thread::get_id());
	if (it == threadComp.end())
		return Competitor::makeNull();
	else
		return it->second;
}

void ThreadMap::printMapContents() {
	std::cout << "MAP CONTENTS:" << std::endl;

	//For loop: goes through each ThreadMap index
	for(auto it = threadComp.begin(); it != threadComp.end(); it++) {
            std::cout << "Thread ID: " << it->first << endl << "Competitor: " << it->second.getPerson() << endl << "Team: " << it->second.getTeam() << endl << "Time: " << it->second.getRaceTime() << endl << endl; //the thread id is stored first then the Competitor c object is stored in the second so member function can be accessed as such
    }
	cout << "END MAP CONTENTS" << endl;
}

void ThreadMap::printTeamTimes(string first, string second, string third, string fourth) {
    float team_times[4] = {0};
    float time;
    string team;
    for(auto it = threadComp.begin(); it != threadComp.end(); it++) {
        time = it->second.getRaceTime();
        team = it->second.getTeam();
        if (team == first)
            team_times[0] += time;
        else if (team == second)
            team_times[1] += time;
        else if (team == third)
            team_times[2] += time;
        else if (team == fourth)
            team_times[3] += time;
    }

    //Format output data appropriately.
    std::cout << "Total Team Times" <<endl<<endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl<<endl;
    std::cout << "Team " << first << ": " << team_times[0] << " s" << endl;
    std::cout << "Team " << second << ": " << team_times[1] << " s" << endl;
    std::cout << "Team " << third << ": " << team_times[2] << " s" << endl;
    std::cout << "Team " << fourth << ": " << team_times[3] << " s" << endl<<endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
}

void ThreadMap::printTimes(string team) {
    std::cout << "Team " << team << ":" << endl<<endl;
    for(auto it = threadComp.begin(); it != threadComp.end(); it++) {
        if (it->second.getTeam() == team)
        {
            std::cout << it->second.getPerson() << ": " << it->second.getRaceTime() << " s" <<endl;
        }
    }
}

//Format individual times printed.
void ThreadMap::printIndividualTimes(string first, string second, string third, string fourth) {
    std::cout << "Individual Times" << endl<<endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl<<endl;
    printTimes(first);
    std::cout << endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(second);
    std::cout << endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(third);
    std::cout << endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(fourth);
    std::cout << endl << endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
}

int ThreadMap::ThreadMapSize() { return threadComp.size(); }
