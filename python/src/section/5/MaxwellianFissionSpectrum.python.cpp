// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapMaxwellianFissionSpectrum( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 5 >::MaxwellianFissionSpectrum;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "MaxwellianFissionSpectrum",
    "MF5 section - the Maxwellian fission spectrum (LF=7)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "thetas" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    thetas          the theta values"
  )
  .def_property_readonly(

    "LF",
    [] ( const Component& self ) { return self.LF(); },
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "thetas",
    [] ( const Component& self ) -> DoubleRange
       { return self.thetas(); },
    "The theta values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
