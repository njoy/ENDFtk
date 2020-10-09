// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapIsotropic( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 4 >::Isotropic;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "Isotropic",
    "MF4 section - the angular distributions are all isotropic"
  );

  // wrap the section
  component
  .def(

    python::init<>(),
    "Initialise the isotropic distributions\n\n"
    "Arguments:\n"
    "    self    the component"
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

    "LTT",
    [] ( const Component& self ) { return self.LTT(); },
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    [] ( const Component& self ) { return self.LAW(); },
    "The distribution law"
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

  // no standard component definitions are added since Isotropic does not
  // define all of them
}
