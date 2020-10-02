#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ENDFtk.hpp"

namespace py = pybind11;
using namespace njoy::ENDFtk;

void py_syntaxTree(py::module &m) {

  using namespace syntaxTree;
  using BufferIterator = ranges::iterator_t< const std::string >;
  using Tape_t = Tape< std::string >;
  using Material_t = Material< BufferIterator >;
  using File_t = File< BufferIterator >;
  using Section_t = Section< BufferIterator >;
  using Type_1_t = section::Type< 1, 451 >;
  using Type_3_t = section::Type< 3 >;
  using Type_4_t = section::Type< 4 >;
  using Type_5_t = section::Type< 5 >;
  using Type_6_t = section::Type< 6 >;
  using File_3_t = file::Type< 3 >;

  py::class_< Material_t >(m, "Material")
    .def("hasFileNumber", &Material_t::hasFileNumber)
    .def("size", &Material_t::size)
    .def("MF", (File_t& (Material_t::*)(int))
               &Material_t::MF)
    .def_property_readonly("materialNumber",
                           &Material_t::materialNumber)
    .def_property_readonly("files",
                           [](Material_t& matl) {
                             return matl | ranges::to_vector;
                           });

}
