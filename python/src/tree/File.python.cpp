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

  py::class_< File_t >(m, "File")
    .def("hasSectionNumber", &File_t::hasSectionNumber)
    .def("size", &File_t::size)
    .def("MT", (Section_t& (File_t::*)(int))
               &File_t::MT)
    .def_property_readonly("fileNumber",
                           &File_t::fileNumber)
    .def_property_readonly("sections",
                           [](File_t& file) {
                             return file | ranges::to_vector;
                           })
    .def_property_readonly("buffer",
                           [](File_t& file) {
                             return std::string(file.buffer().begin(),
                                                file.buffer().end());
                           })
    .def("parse3", (File_3_t (File_t::*)() const)
                   &File_t::parse<3>)
    .def("parse3", (File_3_t (File_t::*)(long&) const)
                   &File_t::parse<3>);

}
