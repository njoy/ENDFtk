// system includes
#include <complex>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law1 {

void wrapKalbachMann( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ContinuumEnergyAngle::KalbachMann;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "KalbachMann",
    "MF6 section - LAW=1 - angular distributions are given using Kalbach-Mann\n"
    "                      systematics"
  );

  // wrap the section
  component
  .def(

    python::init< double, long, std::vector< std::array< double, 3 > >&& >(),
    python::arg( "energy" ), python::arg( "nd" ), python::arg( "data" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    energy    the incident energy value\n"
    "    nd        the number of discrete energies\n"
    "    data      the Kalbach-Mann data (nep sets of 3 values)"
  )
  .def(

    python::init< double, long, std::vector< std::array< double, 4 > >&& >(),
    python::arg( "energy" ), python::arg( "nd" ), python::arg( "data" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    energy    the incident energy value\n"
    "    nd        the number of discrete energies\n"
    "    data      the Kalbach-Mann data (nep sets of 4 values)"
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

    "ND",
    [] ( const Component& self )
       { return self.ND(); },
    "The number of discrete energies"
  )
  .def_property_readonly(

    "number_discrete_energies",
    [] ( const Component& self )
       { return self.numberDiscreteEnergies(); },
    "The number of discrete energies"
  )
  .def_property_readonly(

    "NA",
    [] ( const Component& self )
       { return self.NA(); },
    "The number of angular parameter values"
  )
  .def_property_readonly(

    "number_angular_parameters",
    [] ( const Component& self )
       { return self.numberAngularParameters(); },
    "The number of angular parameter values"
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

    "F0",
    [] ( const Component& self ) -> DoubleRange
       { return self.F0(); },
    "The total emission probabilities"
  )
  .def_property_readonly(

    "total_emission_probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.totalEmissionProbabilities(); },
    "The total emission probabilities"
  )
  .def_property_readonly(

    "parameters",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.parameters(); },
    "The Kalbach-Mann parameters"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law2
} // namespace mf6
