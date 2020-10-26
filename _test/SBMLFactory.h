#include <iostream>

class SBMLModel{
public:
    virtual std::string str() = 0;
};

class SimpleMASBMLModel : public SBMLModel{
public:
    std::string str(){
        return "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
               "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
               "  <model metaid=\"x\" id=\"x\">\n"
               "    <listOfCompartments>\n"
               "      <compartment sboTerm=\"SBO:0000410\" id=\"default_compartment\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
               "    </listOfCompartments>\n"
               "    <listOfSpecies>\n"
               "      <species id=\"A\" compartment=\"default_compartment\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "      <species id=\"B\" compartment=\"default_compartment\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "      <species id=\"C\" compartment=\"default_compartment\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "      <species id=\"D\" compartment=\"default_compartment\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
               "    </listOfSpecies>\n"
               "    <listOfParameters>\n"
               "      <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
               "      <parameter id=\"S\" value=\"1\" constant=\"true\"/>\n"
               "      <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
               "      <parameter id=\"k3\" value=\"0.1\" constant=\"true\"/>\n"
               "      <parameter id=\"k4\" value=\"0.1\" constant=\"true\"/>\n"
               "    </listOfParameters>\n"
               "    <listOfReactions>\n"
               "      <reaction id=\"r1\" reversible=\"true\" fast=\"false\">\n"
               "        <listOfReactants>\n"
               "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfReactants>\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> k1 </ci>\n"
               "              <ci> S </ci>\n"
               "              <ci> A </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "      <reaction id=\"r2\" reversible=\"true\" fast=\"false\">\n"
               "        <listOfReactants>\n"
               "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfReactants>\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> k2 </ci>\n"
               "              <ci> B </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "      <reaction id=\"r3\" reversible=\"true\" fast=\"false\">\n"
               "        <listOfReactants>\n"
               "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfReactants>\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfProducts>\n"
               "        <listOfModifiers>\n"
               "          <modifierSpeciesReference species=\"B\"/>\n"
               "        </listOfModifiers>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> k3 </ci>\n"
               "              <ci> C </ci>\n"
               "              <ci> B </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "      <reaction id=\"r4\" reversible=\"true\" fast=\"false\">\n"
               "        <listOfReactants>\n"
               "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfReactants>\n"
               "        <listOfProducts>\n"
               "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
               "        </listOfProducts>\n"
               "        <kineticLaw>\n"
               "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
               "            <apply>\n"
               "              <times/>\n"
               "              <ci> k4 </ci>\n"
               "              <ci> D </ci>\n"
               "            </apply>\n"
               "          </math>\n"
               "        </kineticLaw>\n"
               "      </reaction>\n"
               "    </listOfReactions>\n"
               "  </model>\n"
               "</sbml>";
    }
};


enum SBMLModelTypes {
    SIMPLE_MASS_ACTION_MODEL
};


std::string SBMLFactory(SBMLModelTypes type){
    if (type == SIMPLE_MASS_ACTION_MODEL){
        return SimpleMASBMLModel().str();
    }

    else {
        throw std::logic_error("SBML Type not recognized.");
    }
}

























