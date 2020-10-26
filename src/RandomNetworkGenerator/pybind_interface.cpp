//
// Created by Ciaran Welsh on 26/10/2020.
//

#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include <pybind11/stl.h>

#include "RandomNetworkGenerator.h"
#include "RandomNetworkGeneratorOptions.h"
#include "evoRateLaw.h"
#include "RoleTypes.h"
#include "StoicCounter.h"

using namespace evo;

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(RandomNetworkGenerator, random_network_generator) {
    random_network_generator.doc() = R"pbdoc(
        Roadrunner Random Network Generator
        -------------------------------------
        .. currentmodule:: random_network_generator
        .. autosummary::
           :toctree: _generate

    )pbdoc";

    py::enum_<RoleType>(random_network_generator, "RoleType")
            .value("EVO_SUBSTRATE", EVO_SUBSTRATE)
            .value("EVO_PRODUCT", EVO_PRODUCT)
            .value("EVO_PARAMETER", EVO_PARAMETER)
            .value("EVO_MODIFIER", EVO_MODIFIER)
            .value("EVO_DEPENDENT_VARIABLE", EVO_DEPENDENT_VARIABLE)
            .value("EVO_INDEPENDENT_VARIABLE", EVO_INDEPENDENT_VARIABLE)
            .export_values();

    py::class_<RoleMap>(random_network_generator, "RoleMap")
            .

//    py::class_<EvoRateLaw>(m, "EvoRateLaw")
//            .def(py::init<>())

//    py::class_<RandomNetworkGeneratorOptions>(m, RandomNetworkGeneratorOptions)
//            .def(py::init())


}


























