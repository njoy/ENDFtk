// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTabulatedDistribution( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using Component = Section::TabulatedDistribution;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TabulatedDistribution",
    "MF4 section - an angular distribution given as a tabulated function"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "cosines" ),
    python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    incident         the incident energy value\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    cosines          the cosine values\n"
    "    probabilities    the probability values"
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

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
