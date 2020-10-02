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

  py::class_< Section_t >(m, "Section")
    .def_property_readonly("sectionNumber",
                           &Section_t::sectionNumber)
    .def_property_readonly("buffer",
                           [](Section_t& sec) {
                             return std::string(sec.buffer().begin(),
                                                sec.buffer().end());
                           })
    .def("parse1", (Type_1_t (Section_t::*)() const)
                   &Section_t::parse<1,451>)
    .def("parse1", (Type_1_t (Section_t::*)(long&) const)
                   &Section_t::parse<1,451>)
    .def("parse3", (Type_3_t (Section_t::*)() const)
                   &Section_t::parse<3>)
    .def("parse3", (Type_3_t (Section_t::*)(long&) const)
                   &Section_t::parse<3>)
    .def("parse4", (Type_4_t (Section_t::*)() const)
                   &Section_t::parse<4>)
    .def("parse4", (Type_4_t (Section_t::*)(long&) const)
                   &Section_t::parse<4>)
    .def("parse5", (Type_5_t (Section_t::*)() const)
                   &Section_t::parse<5>)
    .def("parse5", (Type_5_t (Section_t::*)(long&) const)
                   &Section_t::parse<5>)
    .def("parse6", (Type_6_t (Section_t::*)() const)
                   &Section_t::parse<6>)
    .def("parse6", (Type_6_t (Section_t::*)(long&) const)
                   &Section_t::parse<6>)
  ;

}
