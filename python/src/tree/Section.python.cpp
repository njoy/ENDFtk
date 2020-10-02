// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Section.hpp"
#include "range/v3/utility/iterators.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeSection( python::module& module ) {

  // type aliases
  using BufferIterator = ranges::iterator_t< const std::string >;
  using Section_t = njoy::ENDFtk::tree::Section< BufferIterator >;

  // wrap views created by this section

  // create the tree component
  python::class_< Section > tree(

    module,
    "Section",
    "ENDF tree section"
  );

  tree
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
