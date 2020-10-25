#include "rr/rrRoadRunner.h"
#include <chrono>

using namespace rr;

int main(){

    //***C++11 Style:***
#include <chrono>

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int N = 100;

    for (int i=0; i<100; i++){
        RoadRunner rr;
        rr.addCompartment("C1", 1, false);
        rr.addSpecies("S1", "C1", 100.0, false, false, "", false);
        rr.addSpecies("S2", "C1", 100.0, false, false, "", false);
        rr.addParameter("k1", 1.0, false);
        rr.addParameter("k2", 1.0, false);
        rr.addReaction("R1", {"S1"}, {"S2"}, "k1*S1", false);
        rr.addReaction("R2", {"S2"}, {"S1"}, "k2*S2", true);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    int one = 3159771;
    int two = 3088329;
    int three = 2848991;
    int four = 2796669;
    int five = 2794111;
    int six = 3432897;
    int seven = 3086287;

    double avg = (one + two + three + four + five + six + seven ) / 7.0;
    std::cout << avg / (1000000.0 ) << std::endl; // 3.02958 seconds

}




















