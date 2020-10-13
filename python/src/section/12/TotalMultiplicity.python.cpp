// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/12.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTotalMultiplicity( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 12 >::TotalMultiplicity;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TotalMultiplicity",
    "MF12 section - the total photon multiplicity"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "multiplicities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    boundaries        the interpolation range boundaries\n"
    "    interpolants      the interpolation types for each range\n"
    "    energies          the energy values\n"
    "    multiplicities    the probability values"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "Y",
    [] ( const Component& self ) -> DoubleRange
       { return self.Y(); },
    "The multiplicity values"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Component& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The multiplicity values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
