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

void wrapTabulatedDistribution( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::ContinuumEnergyAngle::TabulatedDistribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedDistribution",
    "MF6 section - LAW=1 - angular distributions are given as a tabulated\n"
    "                      function"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, int, int, std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "lang" ), python::arg( "energy" ), python::arg( "nd" ),
    python::arg( "na" ), python::arg( "energies" ), python::arg( "emissions" ),
    python::arg( "cosines" ),  python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the incident energy value\n"
    "    nd               the number of discrete energies\n"
    "    na               the number of angular parameters\n"
    "    energies         the energy values\n"
    "    emissions        the total emission probabilities\n"
    "    cosines          the energy values\n"
    "    probabilities    the Legendre coefficients"
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
    &Component::LANG,
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
  )
  .def_property_readonly(

    "F",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.F(); },
    "The probability values"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.probabilities(); },
    "The probability values"
  ).def(

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

  // no standard component definitions since from_string would require LANG
}

} // namespace law2
} // namespace mf6
