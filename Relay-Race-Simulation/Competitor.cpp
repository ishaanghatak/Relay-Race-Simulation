// Ishaan Ghatak
//

#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <mutex>

#include "Competitor.h"

using namespace std;

Competitor::Competitor() {}
Competitor::Competitor(string tN, string pN) : teamName(tN), personName(pN) {}

void Competitor::setTeam(string tN) { teamName = tN; }
string Competitor::getTeam() { return teamName; }

void Competitor::setPerson(string pN) { personName = pN; }
string Competitor::getPerson() { return personName; }

Competitor Competitor::makeNull() {
    return *(new Competitor(" ", " "));
}

void Competitor::printCompetitor() {
    std::cout << "Team = " << teamName << " Athlete = " << personName << std::endl<<endl;
}

void Competitor::generateRaceTime()
{
    RandomTwister rt; //
    raceTime_ms = rt.randomPeriod(9580, 11150);
    // Thread safe random time generation set between Usain Bolt's world record (9.58 s) and women's 100 m qualifying time (11.15 s)
    // in milliseconds
}

int Competitor::getRaceTime_ms()
{
    return raceTime_ms;
}

// Divide int value in milliseconds by a thousand to get the race time in seconds as a float value.
float Competitor::getRaceTime()
{
    return raceTime_ms/1000.0;
}
