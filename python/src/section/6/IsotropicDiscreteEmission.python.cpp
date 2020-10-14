// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapIsotropicDiscreteEmission( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::IsotropicDiscreteEmission;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "IsotropicDiscreteEmission",
    "MF6 section - LAW=3 - the angular distribution is isotropic in CM and\n"
    "                      no data is given"
  );

  // wrap the section
  component
  .def(

    python::init<>(),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component"
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

  // no standard component definitions are added since IsotropicDiscreteEmission is incomplete
}
