#include "pybind11/pybind11.h"
#include "pybind11/stl.h" // for auto STL conversions
#include "pybind11/operators.h" // for py::self conversions
#include "pybind11/cast.h"
#include "rr/rrRoadRunner.h"

#include "evoRateLaw.h"
#include "NetworkComponent.h"
#include "RNG.h"
#include "RNGOptions.h"
#include "RoleTypes.h"
#include "StoicCounter.h"


namespace py = pybind11;
using namespace rr;
using namespace evo;

unsigned long long asPtr(RoadRunner &r) {
    return reinterpret_cast<unsigned long long>(&r);
}
/**
 * I may need to extend this but I'm reluctant.
 * I want a way to port a roadrunner instance generated by this
 * program to the official roadrunner release in Python.
 */

/*
 * static_cast<void (Pet::*)(int)>(&Pet::set)
 *
 */

// look at: https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html
template<typename T>
void declare_matrix(py::module &m, const std::string &typestr) {
    using Class = ls::Matrix<T>;
    const std::string &pyclass_name = typestr;
    py::class_<Class>(m, pyclass_name.c_str(), py::buffer_protocol(), py::dynamic_attr())
            .def(py::init<unsigned int, unsigned int>())
            .def("getValues", &Class::getValues)
            .def("numRows", &Class::numRows)
            .def("numCols", &Class::numCols)
            .def("getRowNames", static_cast< std::vector<std::string> &(ls::Matrix<T>::*)()>(&Class::getRowNames))
            .def("getColNames", static_cast< std::vector<std::string> &(ls::Matrix<T>::*)()>(&Class::getColNames))
            .def("__getitem__", [](const ls::Matrix<T> &matrix, unsigned int row) {
                return matrix[row];
            }, py::is_operator())
            .def("__getitem__", [](const ls::Matrix<T> &matrix, unsigned int row, unsigned int col) {
                return matrix[row, col];
            }, py::is_operator());
}


PYBIND11_MODULE(evogen, m) {
    declare_matrix<double>(m, "DoubleMatrix");
    declare_matrix<int>(m, "IntMatrix");
    declare_matrix<ls::Complex>(m, "ComplexMatrix");

    py::class_<RoadRunner>(m, "RoadRunner")
            .def(py::init<unsigned int, unsigned int>(),
                 py::arg("level") = 3, py::arg("version") = 2)
            .def(py::init<const RoadRunner &>(), py::arg("rr"))
            .def("_asPtr", &asPtr)
            .def("getSBML", &RoadRunner::getSBML, py::arg("level") = 0, py::arg("version") = 0)
            .def("getInstanceID", &RoadRunner::getInstanceID)
            .def("getInstanceCount", &RoadRunner::getInstanceCount)
            .def("getInfo", &RoadRunner::getInfo)
            .def("getModelName", &RoadRunner::getModelName)
            .def("getIndependentFloatingSpeciesIds", &RoadRunner::getIndependentFloatingSpeciesIds)
            .def("getDependentFloatingSpeciesIds", &RoadRunner::getDependentFloatingSpeciesIds)
            .def("getFloatingSpeciesConcentrationIds", &RoadRunner::getFloatingSpeciesConcentrationIds)
            .def("getFloatingSpeciesInitialConcentrationIds", &RoadRunner::getFloatingSpeciesInitialConcentrationIds)
            .def("setValue", &RoadRunner::setValue, py::arg("id"), py::arg("value"))
            .def("getFloatingSpeciesAmountsNamedArray", &RoadRunner::getFloatingSpeciesAmountsNamedArray)
            .def("getFloatingSpeciesConcentrationsNamedArray", &RoadRunner::getFloatingSpeciesConcentrationsNamedArray)
            .def("getBoundarySpeciesAmountsNamedArray", &RoadRunner::getBoundarySpeciesAmountsNamedArray)
            .def("getBoundarySpeciesConcentrationsNamedArray", &RoadRunner::getBoundarySpeciesConcentrationsNamedArray)
            .def("getRatesOfChange", &RoadRunner::getRatesOfChange)
            .def("getRatesOfChangeNamedArray", &RoadRunner::getRatesOfChangeNamedArray)
            .def("getIndependentRatesOfChange", &RoadRunner::getIndependentRatesOfChange)
            .def("getIndependentRatesOfChangeNamedArray", &RoadRunner::getIndependentRatesOfChangeNamedArray)
            .def("getDependentRatesOfChange", &RoadRunner::getDependentRatesOfChange)
            .def("getDependentRatesOfChangeNamedArray", &RoadRunner::getDependentRatesOfChangeNamedArray)
            .def("getFullJacobian", &RoadRunner::getFullJacobian)
            .def("getFullReorderedJacobian", &RoadRunner::getFullReorderedJacobian)
            .def("getReducedJacobian", &RoadRunner::getReducedJacobian)
            .def("getFullEigenValues", &RoadRunner::getFullEigenValues)
            .def("getReducedEigenValues", &RoadRunner::getReducedEigenValues)
            .def("getLinkMatrix", &RoadRunner::getLinkMatrix)
            .def("getNrMatrix", &RoadRunner::getNrMatrix)
            .def("getKMatrix", &RoadRunner::getKMatrix)
            .def("getReducedStoichiometryMatrix", &RoadRunner::getReducedStoichiometryMatrix)
            .def("getFullStoichiometryMatrix", &RoadRunner::getFullStoichiometryMatrix)
            .def("getExtendedStoichiometryMatrix", &RoadRunner::getExtendedStoichiometryMatrix)
            .def("getL0Matrix", &RoadRunner::getL0Matrix)
            .def("getConservationMatrix", &RoadRunner::getConservationMatrix)
            .def("getUnscaledConcentrationControlCoefficientMatrix",
                 &RoadRunner::getUnscaledConcentrationControlCoefficientMatrix)
            .def("getScaledConcentrationControlCoefficientMatrix",
                 &RoadRunner::getScaledConcentrationControlCoefficientMatrix)
            .def("getUnscaledFluxControlCoefficientMatrix", &RoadRunner::getUnscaledFluxControlCoefficientMatrix)
            .def("getScaledFluxControlCoefficientMatrix", &RoadRunner::getScaledFluxControlCoefficientMatrix)
            .def("getEigenValueIds", &RoadRunner::getEigenValueIds)
            .def("getUnscaledParameterElasticity", &RoadRunner::getUnscaledParameterElasticity, py::arg("reactionName"),
                 py::arg("parameterName"))
            .def("getFrequencyResponse", &RoadRunner::getFrequencyResponse, py::arg("startFrequency"),
                 py::arg("numberOfDecades"), py::arg("numberOfPoints"), py::arg("parameterName"),
                 py::arg("variableName"), py::arg("useDB"), py::arg("useHz"))
            .def("setConservedMoietyAnalysis", &RoadRunner::setConservedMoietyAnalysis)
            .def("getConservedMoietyAnalysis", &RoadRunner::getConservedMoietyAnalysis)
            .def("addSpecies", &RoadRunner::addSpecies, py::arg("speciesId"), py::arg("compartmentId"),
                 py::arg("initAmount"), py::arg("hasOnlySubstanceUnits"), py::arg( "boundaryCondition"), py::arg("substanceUnits"), py::arg("forceRegenerate") = true)
            .def("removeSpecies", &RoadRunner::removeSpecies, py::arg("sid"), py::arg("forceRegenerate"))
            .def("setBoundary", &RoadRunner::setBoundary, py::arg ( "sid"), py::arg("boundaryCondition"), py::arg("forceRegenerate") = true)
            .def("setHasOnlySubstanceUnits", &RoadRunner::setHasOnlySubstanceUnits,py::arg("sid"), py::arg( "hasOnlySubstanceUnits"), py::arg("forceRegenerate") = true)
            .def("setInitAmount", &RoadRunner::setInitAmount, py::arg( "sid"), py::arg( "initAmount"), py::arg("forceRegenerate") = true)
            .def("setInitConcentration", &RoadRunner::setInitConcentration, py::arg("sid"),py::arg("initConcentration"), py::arg("forceRegenerate") = true)
            .def("setConstant", &RoadRunner::setConstant, py::arg("sid"), py::arg("constant"), py::arg("forceRegenerate") = true)
            .def("addReaction", py::overload_cast<const std::string&, bool>(&RoadRunner::addReaction), py::arg("sbmlRep"), py::arg("forceRegenerate") = true)
            .def("addReaction", py::overload_cast<const std::string&, StringVector, StringVector, const std::string&, bool>(&RoadRunner::addReaction),
                    py::arg("rid"), py::arg("reactants"), py::arg("products"), py::arg("kinetic"), py::arg("forceRegenerate") = true)
            .def("removeReaction", &RoadRunner::removeReaction, py::arg("rid"), py::arg("deleteUnusedParameters") = false, py::arg("forceRegenerate") = true)
            .def("setKineticLaw", &RoadRunner::setKineticLaw, py::arg("rid"), py::arg("kineticLaw"), py::arg("forceRegenerate") = true)
            .def("getKineticLaw", &RoadRunner::getKineticLaw, py::arg("rid"))
            .def("addParameter", &RoadRunner::addParameter, py::arg("pid"), py::arg("value"), py::arg("forceRegenerate") = true)
            .def("removeParameter", &RoadRunner::removeParameter, py::arg("pid"), py::arg("forceRegenerate") = true)
            .def("addCompartment", &RoadRunner::addCompartment, py::arg("cid"), py::arg("initVolume"), py::arg("forceRegenerate") = true)
            .def("removeCompartment", &RoadRunner::removeCompartment, py::arg("cid"), py::arg("forceRegenerate") = true)
            .def("addAssignmentRule", &RoadRunner::addAssignmentRule, py::arg("vid"), py::arg("formula"), py::arg("forceRegenerate") = true)
            .def("addRateRule", &RoadRunner::addRateRule, py::arg("vid"), py::arg("formula"), py::arg("forceRegenerate") = true)
            .def("removeRules", &RoadRunner::removeRules, py::arg("vid"), py::arg("useInitialValue") = false, py::arg("forceRegenerate") = true)
            .def("addInitialAssignment", &RoadRunner::addInitialAssignment, py::arg("vid"), py::arg("formula"), py::arg("forceRegenerate") = true)
            .def("removeInitialAssignment", &RoadRunner::removeInitialAssignment, py::arg("vid"), py::arg("forceRegenerate") = true)
            .def("validateCurrentSBML", &RoadRunner::validateCurrentSBML)
            .def("getNumberOfCompartments", &RoadRunner::getNumberOfCompartments)
            .def("getNumberOfBoundarySpecies", &RoadRunner::getNumberOfBoundarySpecies)
            .def("getNumberOfFloatingSpecies", &RoadRunner::getNumberOfFloatingSpecies)
            .def("getNumberOfGlobalParameters", &RoadRunner::getNumberOfGlobalParameters)
            .def("getNumberOfDependentSpecies", &RoadRunner::getNumberOfDependentSpecies)
            .def("getNumberOfIndependentSpecies", &RoadRunner::getNumberOfIndependentSpecies)
            .def("getNumberOfReactions", &RoadRunner::getNumberOfReactions);


    py::enum_<eRoleType>(m, "eRoleType")
            .value("substrate", eRoleType::EVO_SUBSTRATE)
            .value("product", eRoleType::EVO_PRODUCT)
            .value("modifier", eRoleType::EVO_MODIFIER)
            .value("parameter", eRoleType::EVO_PARAMETER);


    py::class_<evoRateLaw>(m, "RateLaw")
            .def(py::init<std::string, const std::string &, RoleMap>())
            .def("getRateLawElements", &evoRateLaw::getRateLawElements)
            .def("getName", &evoRateLaw::getName)
            .def("getRoles", &evoRateLaw::getRoles)
            .def("getRateLawString", &evoRateLaw::getRateLawString)
            .def("numParameters", &evoRateLaw::numParameters)
            .def("numSubstrates", &evoRateLaw::numSubstrates)
            .def("numProducts", &evoRateLaw::numProducts)
            .def("numModifiers", &evoRateLaw::numModifiers)
            .def("__eq__",
                 [](const evoRateLaw &a, const evoRateLaw &b) {
                     return a == b;
                 })
            .def("__ne__",
                 [](const evoRateLaw &a, const evoRateLaw &b) {
                     return a != b;
                 })
            .def("__repr__",
                 [](const evoRateLaw &rateLaw) {
                     return "<RateLaw: " + rateLaw.getName() + "=" + rateLaw.getRateLawString() + ">";
                 });

    py::class_<RNGOptions>(m, "RNGOptions")
            .def(py::init<RateLaws>())
            .def("getCoreSBML", &RNGOptions::getCoreSBML)
            .def("setCoreSBML", &RNGOptions::setCoreSBML)
            .def("getSeed", &RNGOptions::getSeed)
            .def("setSeed", &RNGOptions::setSeed)
            .def("getBoundarySpeciesLowerBound", &RNGOptions::getBoundarySpeciesLowerBound)
            .def("setBoundarySpeciesLowerBound", &RNGOptions::setBoundarySpeciesLowerBound)
            .def("getBoundarySpeciesUpperBound", &RNGOptions::getBoundarySpeciesUpperBound)
            .def("setBoundarySpeciesUpperBound", &RNGOptions::setBoundarySpeciesUpperBound)
            .def("getNFloatingSpecies", &RNGOptions::getNFloatingSpecies)
            .def("setNFloatingSpecies", &RNGOptions::setNFloatingSpecies)
            .def("getNBoundarySpecies", &RNGOptions::getNBoundarySpecies)
            .def("setNBoundarySpecies", &RNGOptions::setNBoundarySpecies)
            .def("getNReactions", &RNGOptions::getNReactions)
            .def("setNReactions", &RNGOptions::setNReactions)
            .def("getNCompartments", &RNGOptions::getNCompartments)
            .def("setNCompartments", &RNGOptions::setNCompartments)
            .def("getFloatingSpeciesLowerBound", &RNGOptions::getFloatingSpeciesLowerBound)
            .def("setFloatingSpeciesLowerBound", &RNGOptions::setFloatingSpeciesLowerBound)
            .def("getFloatingSpeciesUpperBound", &RNGOptions::getFloatingSpeciesUpperBound)
            .def("setFloatingSpeciesUpperBound", &RNGOptions::setFloatingSpeciesUpperBound)
            .def("getParameterLowerBound", &RNGOptions::getParameterLowerBound)
            .def("setParameterLowerBound", &RNGOptions::setParameterLowerBound)
            .def("getParameterUpperBound", &RNGOptions::getParameterUpperBound)
            .def("setParameterUpperBound", &RNGOptions::setParameterUpperBound)
            .def("getCompartmentLowerBound", &RNGOptions::getCompartmentLowerBound)
            .def("setCompartmentLowerBound", &RNGOptions::setCompartmentLowerBound)
            .def("getCompartmentUpperBound", &RNGOptions::getCompartmentUpperBound)
            .def("setCompartmentUpperBound", &RNGOptions::setCompartmentUpperBound)
            .def("getRateLaws", &RNGOptions::getRateLaws)
            .def("setRateLaws", &RNGOptions::setRateLaws);

    py::class_<RNGAbstract>(m, "RNGAbstract");

    py::class_<BasicRNG, RNGAbstract>(m, "BasicRNG")
            .def(py::init<const RNGOptions &>())
            .def("generate", py::overload_cast<>(&BasicRNG::generate))
            .def("generateMPI", py::overload_cast<int>(&BasicRNG::generate))
            .def("generate", py::overload_cast<int>(&BasicRNG::generate))
            .def_static("deleteRRModel", &BasicRNG::deleteRRModel, py::arg("rr"));

    py::class_<UniqueReactionsRNG, RNGAbstract>(m, "UniqueReactionsRNG")
            .def(py::init<const RNGOptions &>())
            .def("generate", py::overload_cast<>(&UniqueReactionsRNG::generate))
            .def("generateMPI", py::overload_cast<int>(&UniqueReactionsRNG::generate))
            .def("generate", py::overload_cast<int>(&UniqueReactionsRNG::generate))
            .def_static("deleteRRModel", &UniqueReactionsRNG::deleteRRModel, py::arg("rr"));

    py::enum_<eRNG>(m, "eRNG")
            .value("basic", eRNG::BASIC)
            .value("unique_reactions", eRNG::UNIQUE_REACTIONS);

    m.def("massActionRateLaws", &massActionRateLaws);

    m.def("RNGFactory", &RNGFactory,
          py::arg("options") = RNGOptions(massActionRateLaws()),
          py::arg("which") = eRNG::BASIC);

}















