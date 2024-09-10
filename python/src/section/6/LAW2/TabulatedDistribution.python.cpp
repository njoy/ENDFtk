// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/6.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf6 {
namespace law2 {

void wrapTabulatedDistribution( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using Component = Section::DiscreteTwoBodyScattering::TabulatedDistribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedDistribution",
    "MF6 section - LAW=2 - an angular distribution given as a tabulated function"
  );

  // wrap the section
  component
  .def(

    python::init< double, int,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "lang" ),
    python::arg( "cosines" ), python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the incident energy value\n"
    "    lang             the interpolation type for the distribution\n"
    "    energies         the cosine values\n"
    "    probabilities    the probability values"
  )
  .def_property_readonly(

    "LANG",
    &Component::LANG,
    "The interpolation type for this distribution (12 or 14)"
  )
  .def_property_readonly(

    "NL",
    &Component::NL,
    "The number of cosine values"
  )
  .def_property_readonly(

    "number_cosine_values",
    &Component::numberCosineValues,
    "The number of cosine values"
  )
  .def_property_readonly(

    "NW",
    &Component::NW,
    "The number of values (cosine and probabilities)"
  )
  .def_property_readonly(

    "E",
    &Component::E,
    "The incident energy for which the angular distribution is given"
  )
  .def_property_readonly(

    "incident_energy",
    &Component::incidentEnergy,
    "The incident energy for which the angular distribution is given"
  )
  .def_property_readonly(

    "MU",
    [] ( const Component& self ) -> DoubleRange
       { return self.MU(); },
    "The cosine values"
  )
  .def_property_readonly(

    "cosines",
    [] ( const Component& self ) -> DoubleRange
       { return self.cosines(); },
    "The cosine values"
  )
  .def_property_readonly(

    "F",
    [] ( const Component& self ) -> DoubleRange
       { return self.F(); },
    "The distribution probabilities"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.probabilities(); },
    "The distribution probabilities"
  );

  // add standard component definitions
  addStandardInterpolationTableDefinitions< Component >( component );
  addStandardComponentDefinitions< Component >( component );
}

} // namespace law2
} // namespace mf6
