#include <pybind11/pybind11.h>
#include "rr/rrRoadRunner.h"

namespace py = pybind11;
using namespace rr;

PYBIND11_MODULE(example, m) {
    py::class_<RoadRunner>(m, "RoadRunner")
            .def(py::init([]() { return new RoadRunner(); }))
            .def("addSpecies", &RoadRunner::addSpecies)
            .def("addParameter", &RoadRunner::addParameter)
            .def("addCompartment", &RoadRunner::addCompartment);
//            .def("addReaction", &RoadRunner::addReaction);
}

