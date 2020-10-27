


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



class ReactionsTests : public ::testing::Test {
public:
    
    evoRateLaw uni_uni;
    evoRateLaw uni_bi;
    ReactionsTests () {
        uni_uni = evoRateLaw("uni-uni", "k*A",
                            RoleMap(
                                    {{"k", EVO_PARAMETER},
                                     {"A", EVO_SUBSTRATE},
                                     {"B", EVO_PRODUCT}}
                            ));
        uni_bi = evoRateLaw("uni-bi", "k*A",
                            RoleMap(
                                    {{"k", EVO_PARAMETER},
                                     {"A", EVO_SUBSTRATE},
                                     {"B", EVO_PRODUCT},
                                     {"C", EVO_PRODUCT}}
                            ));
        
    }
};

TEST_F(ReactionsTests, Equality){
    Reaction reaction1("R4", uni_bi, {2, 1}, {3}, {});
    Reaction reaction2("R4", uni_bi, {2, 1}, {3}, {});
    ASSERT_TRUE(reaction1 == reaction2);
}

TEST_F(ReactionsTests, Find){
    Reaction reaction1("R1", uni_uni, {0}, {2}, {});

    Reactions reactions(1);
    reactions[0].substrates_ = {0};
    reactions[0].products_ = {2};
    reactions[0].modifiers_ = {};
    reactions[0].rate_law_ = uni_uni;

    bool in = false;
    if (std::find(reactions.begin(), reactions.end(), reaction1) != reactions.end())
        in = true;

    ASSERT_TRUE(in);
}

TEST_F(ReactionsTests, ReactionsContains) {

    Reaction reaction1("R1", uni_uni, {0}, {2}, {});
    Reaction reaction2("R2", uni_uni, {1}, {3}, {});
    Reaction reaction3("R3", uni_bi, {1, 3}, {2}, {});
    Reaction reaction4("R4", uni_bi, {2, 1}, {3}, {});
    Reaction reaction5("R5", uni_uni, {1}, {7}, {3});
    Reaction reaction6("R6", uni_bi, {2, 3}, {3}, {});

    // construct a Reactions object
    Reactions reactions(4);
    reactions.addReaction(reaction1);
    reactions.addReaction(reaction2);
    reactions.addReaction(reaction3);
    reactions.addReaction(reaction4);


    ASSERT_TRUE(reactions.contains(reaction1));
    ASSERT_TRUE(reactions.contains(reaction2));
    ASSERT_TRUE(reactions.contains(reaction3));
    ASSERT_TRUE(reactions.contains(reaction4));

    ASSERT_FALSE(reactions.contains(reaction5));
    ASSERT_FALSE(reactions.contains(reaction6));
}

TEST_F(ReactionsTests, CreateReactionsWithName) {

    Reaction reaction1("R1", uni_uni, {0}, {2}, {});
    Reaction reaction2("R2", uni_uni, {1}, {3}, {});
    Reaction reaction3("R3", uni_bi, {1, 3}, {2}, {});
    Reaction reaction4("R4", uni_bi, {2, 1}, {3}, {});

    // construct a Reactions object
    Reactions reactions(4);
    reactions.addReaction(reaction1);
    reactions.addReaction(reaction2);
    reactions.addReaction(reaction3);
    reactions.addReaction(reaction4);

    ASSERT_STREQ("R1", reaction1.getName().c_str());
    ASSERT_STREQ("R2", reaction2.getName().c_str());
    ASSERT_STREQ("R3", reaction3.getName().c_str());
    ASSERT_STREQ("R4", reaction4.getName().c_str());
}






































