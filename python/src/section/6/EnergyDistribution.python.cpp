// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapEnergyDistribution( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 6 >::LaboratoryAngleEnergy::EnergyDistribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "EnergyDistribution",
    "MF6 section - LAW=7 - the secondary energy distribution associated to a\n"
    "                      given cosine value"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "cosine" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    cosine           the cosine value of the secondary energy distribution\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values"
  )
  .def_property_readonly(

    "NRP",
    &Component::NRP,
    "The number of interpolation regions for the secondary energy"
  )
  .def_property_readonly(

    "NEP",
    &Component::NEP,
    "The number of secondary energy values"
  )
  .def_property_readonly(

    "MU",
    &Component::MU,
    "The cosine value for this secondary energy distribition"
  )
  .def_property_readonly(

    "cosine",
    &Component::cosine,
    "The cosine value for this secondary energy distribition"
  )
  .def_property_readonly(

    "EP",
    [] ( const Component& self ) -> DoubleRange
       { return self.EP(); },
    "The outgoing energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The outgoing energy values"
  )
  .def_property_readonly(

    "F",
    [] ( const Component& self ) -> DoubleRange
       { return self.F(); },
    "The probability values"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.probabilities(); },
    "The probability values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
