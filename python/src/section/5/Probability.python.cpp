// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/5.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapProbability( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 5 >::Probability;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "Probability",
    "MF5 section - probability for a given partial distribution"
  );

  // wrap the section
  component
  .def(

    python::init< long, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&&, double >(),
    python::arg( "lf" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "probabilities" ), python::arg( "u" ) = 0.0,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    lf               the type of the underlying distribution\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values\n"
    "    u                the energy limit constant U (default = 0.0)"
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

    "P",
    [] ( const Component& self ) -> DoubleRange
       { return self.P(); },
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

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
