// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/Tape.hpp"
#include "range/v3/utility/iterator.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeSection( python::module& module ) {

  // type aliases
  using Tape = njoy::ENDFtk::tree::Tape< std::string >;
  using Material = Tape::Material_t;
  using File = Material::File_t;
  using Section = File::Section_t;

  // wrap views created by this component

  // create the tree component
  python::class_< Section > tree(

    module,
    "Section",
    "ENDF tree section"
  );

  // wrap the tree component
  // no __init__ since we do not want to create this object in python
  tree
  .def_property_readonly(

    "MAT",
    &Section::MAT,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "material_number",
    &Section::materialNumber,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "MF",
    &Section::MF,
    "The MF number of the section"
  )
  .def_property_readonly(

    "file_number",
    &Section::fileNumber,
    "The MF number of the section"
  )
  .def_property_readonly(

    "MT",
    &Section::MT,
    "The MT number of the section"
  )
  .def_property_readonly(

    "section_number",
    &Section::sectionNumber,
    "The MT number of the section"
  )
  .def_property_readonly(

    "content",
    [] ( const Section& self ) -> std::string
       { return self.buffer(); },
    "The content of the section"
  );

//    .def("parse1", (Type_1_t (Section_t::*)() const)
//                   &Section_t::parse<1,451>)
//    .def("parse1", (Type_1_t (Section_t::*)(long&) const)
//                   &Section_t::parse<1,451>)
//    .def("parse3", (Type_3_t (Section_t::*)() const)
//                   &Section_t::parse<3>)
//    .def("parse3", (Type_3_t (Section_t::*)(long&) const)
//                   &Section_t::parse<3>)
//    .def("parse4", (Type_4_t (Section_t::*)() const)
//                   &Section_t::parse<4>)
//    .def("parse4", (Type_4_t (Section_t::*)(long&) const)
//                   &Section_t::parse<4>)
//    .def("parse5", (Type_5_t (Section_t::*)() const)
//                   &Section_t::parse<5>)
//    .def("parse5", (Type_5_t (Section_t::*)(long&) const)
//                   &Section_t::parse<5>)
//    .def("parse6", (Type_6_t (Section_t::*)() const)
//                   &Section_t::parse<6>)
//    .def("parse6", (Type_6_t (Section_t::*)(long&) const)
//                   &Section_t::parse<6>)

}
