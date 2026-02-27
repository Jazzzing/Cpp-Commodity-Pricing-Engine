#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // Required to automatically convert std::vector to Python lists
#include "MonteCarloEngine.h"

namespace py = pybind11;

// This macro creates the Python module named 'gs_pricer'
PYBIND11_MODULE(gs_pricer, m) {
    m.doc() = "Gibson-Schwartz Monte Carlo Engine";

    // Expose the GSParameters struct
    py::class_<GSParameters>(m, "GSParameters")
        .def(py::init<>()) // Default constructor
        .def_readwrite("S0", &GSParameters::S0)
        .def_readwrite("sigma1", &GSParameters::sigma1)
        .def_readwrite("delta0", &GSParameters::delta0)
        .def_readwrite("sigma2", &GSParameters::sigma2)
        .def_readwrite("kappa", &GSParameters::kappa)
        .def_readwrite("alpha", &GSParameters::alpha)
        .def_readwrite("rho", &GSParameters::rho)
        .def_readwrite("r", &GSParameters::r);

    // Expose the MonteCarloEngine class
    py::class_<MonteCarloEngine>(m, "MonteCarloEngine")
        .def(py::init<const GSParameters&, int, int, double>(), 
             py::arg("params"), py::arg("numPaths"), py::arg("numSteps"), py::arg("T"))
        .def("runSimulation", &MonteCarloEngine::runSimulation);
}