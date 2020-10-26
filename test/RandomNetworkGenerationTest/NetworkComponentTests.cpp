


#include "gtest/gtest.h"
#include "NetworkComponent.h"


using namespace evo;


TEST(NetworkComponent, CompartmentContains) {
    Compartments compartments;
    compartments.ids = {"C1", "C2"};
    compartments.values = {1.5, 3.6};
    ASSERT_TRUE(compartments.contains("C1"));
}

TEST(NetworkComponent, FloatingSpeciesContains) {
    FloatingSpecies floatingSpecies;
    floatingSpecies.ids = {"S1", "S2"};
    floatingSpecies.compartment_index = {0, 1};
    ASSERT_TRUE(floatingSpecies.contains("S1", 0));
    ASSERT_FALSE(floatingSpecies.contains("S1", 1));
}

TEST(NetworkComponent, BoundarySpeciesContains) {
    FloatingSpecies floatingSpecies;
    floatingSpecies.ids = {"S1", "S2"};
    floatingSpecies.compartment_index = {0, 1};
    ASSERT_TRUE(floatingSpecies.contains("S1", 0));
    ASSERT_FALSE(floatingSpecies.contains("S1", 1));
}

TEST(NetworkComponent, ReactionsContains) {

    // construct a Reactions object
    evoRateLaw rateLaw1("uni-uni", "K*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT}}
                        ));
    evoRateLaw rateLaw2("uni-bi", "K*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT},
                                 {"C", EVO_PRODUCT}}
                        ));
    Reactions reactions;
    reactions.substrates = {{0},
                            {1}};
    reactions.products = {{2},
                          {3}};
    reactions.modifiers = {{5},
                           {6}};
    reactions.rate_laws = {rateLaw1, rateLaw2};

    ASSERT_TRUE(reactions.contains({0}, {2}, {5}, rateLaw1));
    ASSERT_FALSE(reactions.contains({0}, {2}, {6}, rateLaw1));
    ASSERT_TRUE(reactions.contains({1}, {3}, {6}, rateLaw2));
    ASSERT_FALSE(reactions.contains({1}, {3}, {6}, rateLaw1));

}




































