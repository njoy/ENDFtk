// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {

void wrapDefinedElsewhere( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::DefinedElsewhere;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DefinedElsewhere",
    "MF6 section - LAW<0 - the distributions are defined elsewhere and no\n"
    "                      data is given"
  );

  // wrap the section
  component
  .def(

    python::init< int >(),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    law     the law number to be used (-4, -5, -14, -15 only)"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution type (the LAW flag)"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "component" ),
    "Copy the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    component    the component to be copied"
  )
  .def_property_readonly(

    "NC",
    [] ( const Component& self ) { return self.NC(); },
    "The number of lines in this component"
  )
  .def(

    "to_string",
    [] ( const Component& self, int mat, int mf, int mt ) -> std::string
       { return print( self, mat, mf, mt ); },
    python::arg( "mat" ), python::arg( "mf" ), python::arg( "mt" ),
    "Return the string representation of the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used\n"
    "    mt      the MT number to be used"
  );

  // no standard component definitions are added since DefinedElsewhere is incomplete
}

} // namespace mf6
