import unittest
import sys

sys.path.append("/Users/ciaranwelsh/Documents/Evogen/cmake-build-release/lib")
from evogen import eRoleType, RateLaw, RNGOptions, RoadRunner, massActionRateLaws
from evogen import BasicRNG, UniqueReactionsRNG, RNGFactory, eRNG


class RateLawTests(unittest.TestCase):

    def setUp(self) -> None:
        self.role_maps = {
            "uni-uni": {
                'k': eRoleType.parameter,
                'S1': eRoleType.substrate,
                'S2': eRoleType.product
            },
            "uni-bi": {
                'k': eRoleType.parameter,
                'S1': eRoleType.substrate,
                'S2': eRoleType.product,
                'S3': eRoleType.product
            },
        }
        self.uni_uni = RateLaw("uni-uni", "k*S1", self.role_maps["uni-uni"])
        self.uni_bi = RateLaw("uni-bi", "k*S1", self.role_maps["uni-bi"])

    def tearDown(self) -> None:
        pass

    def test_getRateLawElements(self):
        actual = self.uni_uni.getRateLawElements()
        expected = {'S1', 'k'}
        self.assertEqual(expected, actual)

    def test_getName(self):
        actual = self.uni_uni.getName()
        expected = "uni-uni"
        self.assertEqual(expected, actual)

    def test_getRoles(self):
        actual = self.uni_bi.getRoles()
        self.assertEqual(self.role_maps["uni-bi"], actual)

    def test_getRateLawString(self):
        actual = self.uni_uni.getRateLawString()
        expected = "k*S1"
        self.assertEqual(expected, actual)

    def test_numParameters(self):
        actual = self.uni_bi.numParameters()
        expected = 1
        self.assertEqual(expected, actual)

    def test_numSubstrates(self):
        actual = self.uni_uni.numSubstrates()
        expected = 1
        self.assertEqual(expected, actual)

    def test_numProducts(self):
        actual = self.uni_bi.numProducts()
        expected = 2
        self.assertEqual(expected, actual)

    def test_numModifiers(self):
        actual = self.uni_uni.numModifiers()
        expected = 0
        self.assertEqual(expected, actual)

    def test___eq__(self):
        uni_uni = RateLaw("uni-uni", "k*S1", self.role_maps["uni-uni"])
        self.assertEqual(uni_uni, self.uni_uni)


class RNGOptionsTests(unittest.TestCase):

    def setUp(self) -> None:
        self.options = RNGOptions(massActionRateLaws())

    def tearDown(self) -> None:
        pass

    def test_Seed(self):
        self.options.setSeed(6)
        self.assertEqual(6, self.options.getSeed())

    def test_BoundarySpeciesLowerBound(self):
        self.options.setBoundarySpeciesLowerBound(1)
        self.assertEqual(1, self.options.getBoundarySpeciesLowerBound())

    def test_BoundarySpeciesUpperBound(self):
        self.options.setBoundarySpeciesUpperBound(3)
        self.assertEqual(3, self.options.getBoundarySpeciesUpperBound())

    def test_getNFloatingSpecies(self):
        self.options.setNFloatingSpecies(6)
        self.assertEqual(6, self.options.getNFloatingSpecies())

    def test_getNBoundarySpecies(self):
        self.options.setNBoundarySpecies(6)
        self.assertEqual(6, self.options.getNBoundarySpecies())

    def test_getNReactions(self):
        self.options.setNReactions(6)
        self.assertEqual(6, self.options.getNReactions())

    def test_getNCompartments(self):
        self.options.setNCompartments(6)
        self.assertEqual(6, self.options.getNCompartments())

    def test_FloatingSpeciesLowerBound(self):
        self.options.setFloatingSpeciesLowerBound(0.1)
        self.assertEqual(0.1, self.options.getFloatingSpeciesLowerBound())

    def test_FloatingSpeciesUpperBound(self):
        self.options.setFloatingSpeciesUpperBound(10.0)
        self.assertEqual(10.0, self.options.getFloatingSpeciesUpperBound())

    def test_ParameterLowerBound(self):
        self.options.setParameterLowerBound(0.3)
        self.assertEqual(0.3, self.options.getParameterLowerBound())

    def test_ParameterUpperBound(self):
        self.options.setParameterUpperBound(0.3)
        self.assertEqual(0.3, self.options.getParameterUpperBound())

    def test_CompartmentLowerBound(self):
        self.options.setCompartmentLowerBound(0.3)
        self.assertEqual(0.3, self.options.getCompartmentLowerBound())

    def test_CompartmentUpperBound(self):
        self.options.setCompartmentUpperBound(0.6)
        self.assertEqual(0.6, self.options.getCompartmentUpperBound())

    def test_RateLaws(self):
        mm = RateLaw("michaelis-menten", "vmax*s/(km+s)", dict(
            vmax=eRoleType.parameter,
            s=eRoleType.substrate,
            km=eRoleType.parameter,
        ))
        rate_laws = massActionRateLaws()
        rate_laws["michaelis-menten"] = mm
        keys = ['bi-bi', 'bi-uni', 'uni-bi', 'uni-uni', 'michaelis-menten']
        self.options.setRateLaws(rate_laws)
        self.assertEqual(sorted(keys), sorted(list(self.options.getRateLaws().keys())))

    def test_CoreSbml(self):
        # import tellurium as te
        # sbml = te.loada("A => B; k1*A; k1=10; A=10; B=0").getSBML()
        # print(sbml)
        sbml = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version1/core" level="3" version="1">
  <model metaid="__main" id="__main">
    <listOfCompartments>
      <compartment sboTerm="SBO:0000410" id="default_compartment" spatialDimensions="3" size="1" constant="true"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="A" compartment="default_compartment" initialConcentration="10" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="B" compartment="default_compartment" initialConcentration="0" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k1" value="10" constant="true"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="_J0" reversible="false" fast="false">
        <listOfReactants>
          <speciesReference species="A" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="B" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> A </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>"""
        self.options.setCoreSBML(sbml)
        self.assertEqual(sbml, self.options.getCoreSBML())


class RNGFactoryTests(unittest.TestCase):
    maxDiff = None

    def setUp(self) -> None:
        self.options = RNGOptions(massActionRateLaws())
        self.options.setSeed(6)

    def tearDown(self) -> None:
        pass

    def test_basic_rng(self):
        random_network_generator = RNGFactory(self.options, eRNG.basic)
        m = random_network_generator.generate()
        sbml_string = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">
  <model>
    <listOfCompartments>
      <compartment id="C0" size="1" constant="false"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>
      <species id="S0" compartment="C0" initialAmount="5.60097836983103" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="S1" compartment="C0" initialAmount="8.02826326562568" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="S2" compartment="C0" initialAmount="8.07203805479603" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k0" value="4.96596023807027" constant="false"/>
      <parameter id="k1" value="0.446282136131609" constant="false"/>
      <parameter id="k2" value="4.02342823876936" constant="false"/>
      <parameter id="k3" value="7.87774413611084" constant="false"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R0" reversible="false">
        <listOfReactants>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k0 </ci>
              <ci> S1 </ci>
              <ci> S0 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R1" reversible="false">
        <listOfReactants>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="S2" stoichiometry="1" constant="true"/>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> I0 </ci>
              <ci> S1 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R2" reversible="false">
        <listOfReactants>
          <speciesReference species="S2" stoichiometry="1" constant="true"/>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> S2 </ci>
              <ci> S1 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" reversible="false">
        <listOfReactants>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k3 </ci>
              <ci> I0 </ci>
              <ci> S0 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
"""
        self.assertEqual(sbml_string, m.getSBML())

    def test_unique_reactions_rng(self):
        random_network_generator = RNGFactory(self.options, eRNG.unique_reactions)
        m = random_network_generator.generate()
        print(m.getSBML())
        sbml_string = """<?xml version="1.0" encoding="UTF-8"?>
<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">
  <model>
    <listOfCompartments>
      <compartment id="C0" size="1" constant="false"/>
    </listOfCompartments>
    <listOfSpecies>
      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>
      <species id="S0" compartment="C0" initialAmount="5.60097836983103" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="S1" compartment="C0" initialAmount="8.02826326562568" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
      <species id="S2" compartment="C0" initialAmount="8.07203805479603" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>
    </listOfSpecies>
    <listOfParameters>
      <parameter id="k0" value="4.96596023807027" constant="false"/>
      <parameter id="k1" value="0.446282136131609" constant="false"/>
      <parameter id="k2" value="4.02342823876936" constant="false"/>
      <parameter id="k3" value="7.87774413611084" constant="false"/>
    </listOfParameters>
    <listOfReactions>
      <reaction id="R0" reversible="false">
        <listOfReactants>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k0 </ci>
              <ci> S1 </ci>
              <ci> S0 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R1" reversible="false">
        <listOfReactants>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
          <speciesReference species="S2" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k1 </ci>
              <ci> S1 </ci>
              <ci> I0 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R2" reversible="false">
        <listOfReactants>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
          <speciesReference species="S2" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k2 </ci>
              <ci> S2 </ci>
              <ci> S1 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
      <reaction id="R3" reversible="false">
        <listOfReactants>
          <speciesReference species="I0" stoichiometry="1" constant="true"/>
          <speciesReference species="S0" stoichiometry="1" constant="true"/>
        </listOfReactants>
        <listOfProducts>
          <speciesReference species="S1" stoichiometry="1" constant="true"/>
        </listOfProducts>
        <kineticLaw>
          <math xmlns="http://www.w3.org/1998/Math/MathML">
            <apply>
              <times/>
              <ci> k3 </ci>
              <ci> S0 </ci>
              <ci> I0 </ci>
            </apply>
          </math>
        </kineticLaw>
      </reaction>
    </listOfReactions>
  </model>
</sbml>
"""
        self.assertEqual(sbml_string, m.getSBML())

    def test_basic_rng_list_of(self):
        random_network_generator = RNGFactory(self.options, eRNG.basic)
        m = random_network_generator.generate(3)
        sbmls = [i.getSBML() for i in m]
        expected = [
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="5.60097836983103" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="8.02826326562568" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="8.07203805479603" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k0" value="4.96596023807027" constant="false"/>\n      <parameter id="k1" value="0.446282136131609" constant="false"/>\n      <parameter id="k2" value="4.02342823876936" constant="false"/>\n      <parameter id="k3" value="7.87774413611084" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k0 </ci>\n              <ci> S1 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k1 </ci>\n              <ci> I0 </ci>\n              <ci> S1 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k2 </ci>\n              <ci> S2 </ci>\n              <ci> S1 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k3 </ci>\n              <ci> I0 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n',
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="5.90843559545756" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="7.37170907331734" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="1.33570488837273" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k4" value="5.93746595915197" constant="false"/>\n      <parameter id="k5" value="1.7987727355235" constant="false"/>\n      <parameter id="k6" value="8.5847165888571" constant="false"/>\n      <parameter id="k7" value="4.54729072200021" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k4 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k5 </ci>\n              <ci> I0 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k6 </ci>\n              <ci> I0 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k7 </ci>\n              <ci> S2 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n',
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="9.41775031727176" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="2.20899980020738" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="9.97894064779844" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k8" value="1.75414310532654" constant="false"/>\n      <parameter id="k9" value="9.18794885529502" constant="false"/>\n      <parameter id="k10" value="3.84345418937081" constant="false"/>\n      <parameter id="k11" value="6.91988210311838" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k8 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k9 </ci>\n              <ci> I0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k10 </ci>\n              <ci> S1 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k11 </ci>\n              <ci> S0 </ci>\n              <ci> S2 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n']
        self.assertEqual(expected, sbmls)

    def test_unique_reactions_rng_list_of(self):
        random_network_generator = RNGFactory(self.options, eRNG.unique_reactions)
        m = random_network_generator.generate(3)
        sbmls = [i.getSBML() for i in m]
        expected = [
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="5.60097836983103" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="8.02826326562568" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="8.07203805479603" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k0" value="4.96596023807027" constant="false"/>\n      <parameter id="k1" value="0.446282136131609" constant="false"/>\n      <parameter id="k2" value="4.02342823876936" constant="false"/>\n      <parameter id="k3" value="7.87774413611084" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k0 </ci>\n              <ci> S1 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k1 </ci>\n              <ci> S1 </ci>\n              <ci> I0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k2 </ci>\n              <ci> S2 </ci>\n              <ci> S1 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k3 </ci>\n              <ci> S0 </ci>\n              <ci> I0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n',
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="5.90843559545756" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="7.37170907331734" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="1.33570488837273" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k4" value="2.28690980220531" constant="false"/>\n      <parameter id="k5" value="9.97915124132046" constant="false"/>\n      <parameter id="k6" value="9.11716187952205" constant="false"/>\n      <parameter id="k7" value="0.912737556922599" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k4 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k5 </ci>\n              <ci> S0 </ci>\n              <ci> I0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k6 </ci>\n              <ci> S2 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k7 </ci>\n              <ci> S0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n',
            '<?xml version="1.0" encoding="UTF-8"?>\n<sbml xmlns="http://www.sbml.org/sbml/level3/version2/core" level="3" version="2">\n  <model>\n    <listOfCompartments>\n      <compartment id="C0" size="1" constant="false"/>\n    </listOfCompartments>\n    <listOfSpecies>\n      <species id="I0" compartment="C0" initialAmount="0" hasOnlySubstanceUnits="false" boundaryCondition="true" constant="false"/>\n      <species id="S0" compartment="C0" initialAmount="1.03519122182768" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S1" compartment="C0" initialAmount="7.36012461049451" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n      <species id="S2" compartment="C0" initialAmount="1.98894184346773" hasOnlySubstanceUnits="false" boundaryCondition="false" constant="false"/>\n    </listOfSpecies>\n    <listOfParameters>\n      <parameter id="k8" value="0.308670868626717" constant="false"/>\n      <parameter id="k9" value="5.95406763599515" constant="false"/>\n      <parameter id="k10" value="0.356157366483058" constant="false"/>\n      <parameter id="k11" value="2.67491497136061" constant="false"/>\n    </listOfParameters>\n    <listOfReactions>\n      <reaction id="R0" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k8 </ci>\n              <ci> S1 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R1" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k9 </ci>\n              <ci> S2 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R2" reversible="false">\n        <listOfReactants>\n          <speciesReference species="I0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k10 </ci>\n              <ci> S1 </ci>\n              <ci> I0 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n      <reaction id="R3" reversible="false">\n        <listOfReactants>\n          <speciesReference species="S1" stoichiometry="1" constant="true"/>\n        </listOfReactants>\n        <listOfProducts>\n          <speciesReference species="S0" stoichiometry="1" constant="true"/>\n          <speciesReference species="S2" stoichiometry="1" constant="true"/>\n        </listOfProducts>\n        <kineticLaw>\n          <math xmlns="http://www.w3.org/1998/Math/MathML">\n            <apply>\n              <times/>\n              <ci> k11 </ci>\n              <ci> S1 </ci>\n            </apply>\n          </math>\n        </kineticLaw>\n      </reaction>\n    </listOfReactions>\n  </model>\n</sbml>\n']

        self.assertEqual(expected, sbmls)
