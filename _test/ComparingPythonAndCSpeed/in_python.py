import roadrunner
import time


if __name__ == "__main__":
    start_time = time.time()

    N = 100
    for i in range(N):
        rr = roadrunner.RoadRunner()
        rr.addCompartment("C1", 1, False)
        rr.addSpecies("S1", "C1", 100.0, False, False, "", False)
        rr.addSpecies("S2", "C1", 100.0, False, False, "", False)
        rr.addParameter("k1", 1.0, False)
        rr.addParameter("k2", 1.0, False)
        rr.addReaction("R1", ["S1"], ["S2"], "k1*S1", False)
        rr.addReaction("R2", ["S2"], ["S1"], "k2*S2", True)
    print("--- %s seconds ---" % (time.time() - start_time))

    one = 3.5058648586273193
    two = 4.370147228240967
    three = 3.457716941833496
    four = 4.276576042175293
    five = 4.117121934890747
    six = 3.484490394592285
    seven = 4.383910179138184
    avg = (one + two + three + four + five + six + seven) / 7.0
    print(avg) #3.94 seconds



