


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
    evoRateLaw rateLaw1("uni-uni", "k*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT}}
                        ));
    evoRateLaw rateLaw2("uni-bi", "k*A",
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

    Reaction reaction1("R1", rateLaw1, {0}, {2}, {5});
    Reaction reaction2("R2", rateLaw1, {0}, {2}, {6});
    Reaction reaction3("R3", rateLaw2, {1}, {3}, {6});
    Reaction reaction4("R4", rateLaw1, {1}, {3}, {6});

    ASSERT_TRUE(reactions.contains(  reaction1));
    ASSERT_FALSE(reactions.contains( reaction2));
    ASSERT_TRUE(reactions.contains(  reaction3));
    ASSERT_FALSE(reactions.contains( reaction4));

}

TEST(NetworkComponent, ReactionsContains2) {

    // construct a Reactions object
    evoRateLaw rateLaw1("uni-uni", "k*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT}}
                        ));
    evoRateLaw rateLaw2("uni-bi", "k*A",
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

    std::vector s1 = {0};
    std::vector p1 = {2};
    std::vector m1 = {5};
    Reaction reaction1("R1", rateLaw1, s1, p1, m1);
    Reaction reaction2("R1", rateLaw2, s1, p1, m1);

    ASSERT_TRUE(reactions.contains(reaction1));
    ASSERT_FALSE(reactions.contains(reaction2));

}

TEST(NetworkComponent, ReactionsContains3) {

    // construct a Reactions object
    evoRateLaw uni_uni("uni-uni", "k*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT}}
                        ));

    evoRateLaw uni_bi("uni-bi", "k*A",
                        RoleMap(
                                {{"k", EVO_PARAMETER},
                                 {"A", EVO_SUBSTRATE},
                                 {"B", EVO_PRODUCT},
                                 {"C", EVO_PRODUCT}}
                        ));
    Reactions reactions;
    reactions.substrates = {
            {1}, {2}, {2}
    };
    reactions.products = {
            {2}, {1, 0}, {1}
    };
    reactions.modifiers = {{}, {}, {}};
    reactions.rate_laws = {uni_uni, uni_bi, uni_uni};

    std::vector<int> s1 = {2};
    std::vector<int> p1 = {1};
    std::vector<int> m1 = {};

    Reaction reaction1("R1", uni_uni, s1, p1, m1);

    ASSERT_TRUE(reactions.contains(reaction1));
}






































