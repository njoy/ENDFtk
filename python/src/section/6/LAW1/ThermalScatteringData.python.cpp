// system includes
#include <complex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law1 {

void wrapThermalScatteringData( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ContinuumEnergyAngle::ThermalScatteringData;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ThermalScatteringData",
    "MF6 section - LAW=1 - internal NJOY thermal scattering data"
  );

  // wrap the section
  component
  .def(

    python::init< double, int, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "n2" ), python::arg( "data" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    energy    the incident energy\n"
    "    n2        the value for n2 (nl+1 or nu+2)\n"
    "    data      the data that goes into this component"
  )
  .def(

    python::init< double, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "cosines" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    energy     the incident energy\n"
    "    cosines    the equally probable cosine values"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self )
       { return self.E(); },
    "The incident energy value"
  )
  .def_property_readonly(

    "incident_energy",
    [] ( const Component& self )
       { return self.incidentEnergy(); },
    "The incident energy value"
  )
  .def_property_readonly(

    "LANG",
    [] ( const Component& self ) { return self.LANG(); },
    "The representation type"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The representation type"
  )
  .def_property_readonly(

    "NW",
    [] ( const Component& self )
       { return self.NW(); },
    "The number of values in this component"
  )
  .def_property_readonly(

    "NEP",
    [] ( const Component& self )
       { return self.NEP(); },
    "The number of secondary energy values"
  )
  .def_property_readonly(

    "number_secondary_energies",
    [] ( const Component& self )
       { return self.numberSecondaryEnergies(); },
    "The number of secondary energy values"
  )
  .def_property_readonly(

    "EP",
    [] ( const Component& self ) -> DoubleRange
       { return self.EP(); },
    "The secondary energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The secondary energy values"
  )
  .def_property_readonly(

    "LTT",
    &Component::LTT,
    "The LTT flag (the format representation type)"
  )
  .def_property_readonly(

    "N2",
    [] ( const Component& self )
       { return self.N2(); },
    "The total emission probabilities"
  )
  .def_property_readonly(

    "data",
    [] ( const Component& self ) -> DoubleRange
       { return self.data(); },
    "The data contained in this component"
  )
  .def_property_readonly(

    "PP",
    [] ( const Component& self ) -> DoubleRange
       { return self.PP(); },
    "The second value for every energy"
  )
  .def_property_readonly(

    "MU",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.MU(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.cosines(); },
    "The cosine values"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law2
} // namespace mf6
