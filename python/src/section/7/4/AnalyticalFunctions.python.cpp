// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/4.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapAnalyticalFunctions( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 4 >;
  using Component = Section::AnalyticalFunctions;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "AnalyticalFunctions",
    "MF7 MT4 section - scattering law for the principal scatterer are\n"
    "                  analytical functions"
  );

  // wrap the section
  component
  .def(

    python::init<>(),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component"
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

  // no standard component definitions are added since AnalyticalFunctions is incomplete
}

} // namespace mf7
