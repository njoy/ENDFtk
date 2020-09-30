#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ENDFtk.hpp"

namespace py = pybind11;
using namespace njoy::ENDFtk;

void py_section_3(py::module &m) {

  using namespace section;
  using Type_3_t = section::Type< 3 >;
  using Base = section::Base;
  using BaseWithoutMT = section::BaseWithoutMT< Base >;

  py::class_< Type_3_t >(m, "Type")
    .def( py::init< int, double, double, double, double, long,
                    std::vector<long>&&, std::vector<long>&&,
                    std::vector<double>&&, std::vector<double>&& >() )
    .def_property_readonly("MT", [](Type_3_t& type) { return type.MT(); })
    .def_property_readonly("ZA", [](Type_3_t& type) { return type.ZA(); })
    .def_property_readonly("AWR", [](Type_3_t& type) { return type.AWR(); })
    .def_property_readonly("QM", &Type_3_t::QM)
    .def_property_readonly("QI", &Type_3_t::QI)
    .def_property_readonly("LR", &Type_3_t::LR)
    .def_property_readonly("NR", &Type_3_t::NR)
    .def_property_readonly("NP", &Type_3_t::NP)
    .def_property_readonly("NC", &Type_3_t::NC)
    .def_property_readonly("interpolants", 
                           [](Type_3_t& type) {
                             return type.interpolants() | ranges::to_vector;
                           })
    .def_property_readonly("boundaries", 
                           [](Type_3_t& type) {
                             return type.boundaries() | ranges::to_vector;
                           })
    .def_property_readonly("energies", 
                           [](Type_3_t& type) {
                             return type.energies() | ranges::to_vector;
                           })
    .def_property_readonly("crossSections", 
                           [](Type_3_t& type) {
                             return type.crossSections() | ranges::to_vector;
                           })
    .def("to_string",
         [](Type_3_t& type, int MAT, int MF) {
           std::string buffer;
           auto output = std::back_inserter( buffer );
           type.print( output, MAT, MF );
           return buffer;
         });

}
