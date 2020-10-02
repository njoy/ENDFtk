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

  py::class_< Tape_t >(m, "Tape")
    .def(py::init<std::string>())
    .def("hasMaterialNumber", &Tape_t::hasMaterialNumber)
    .def("size", &Tape_t::size)
    .def_property_readonly("materials",
                           [](Tape_t& tape) {
                             return tape | ranges::to_vector;
                           });

}
