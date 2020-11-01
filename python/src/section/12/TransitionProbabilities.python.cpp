// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/12.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTransitionProbabilities( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 12 >::TransitionProbabilities;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "TransitionProbabilities",
    "MF12 section - photon production cross section are calculated from MF3\n"
    "               and the transition probabilities"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "energies" ),
    python::arg( "probabilities" ),
    "Initialise the component (for the simple case, LG = 1)\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the highest energy level\n"
    "    energies         the energy levels below the highest level\n"
    "                     (NT values)\n"
    "    probabilities    the transition probabilities (NT values)"
  )
  .def(

    python::init< double, std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "energies" ),
    python::arg( "probabilities" ), python::arg( "conditionals" ),
    "Initialise the component (for the complex case, LG = 2)\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    energy           the highest energy level\n"
    "    energies         the energy levels below the highest level\n"
    "                     (NT values)\n"
    "    probabilities    the transition probabilities (NT values)\n"
    "    conditionals     the conditional photon probabilities (NT values)"
  )
  .def_property_readonly(

    "LO",
    [] ( const Component& self ) { return self.LO(); },
    "The photon production representation type"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The photon production representation type"
  )
  .def_property_readonly(

    "ES",
    &Component::ES,
    "The energy of the highest energy level"
  )
  .def_property_readonly(

    "highest_energy_level",
    &Component::highestEnergyLevel,
    "The energy of the highest energy level"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "The number of transitions that are given"
  )
  .def_property_readonly(

    "number_transitions",
    &Component::numberTransitions,
    "The number of transitions that are given"
  )
  .def_property_readonly(

    "LG",
    &Component::LG,
    "Whether the data is simple (pairs) or complex (triplets)"
  )
  .def_property_readonly(

    "transition_type",
    &Component::transitionType,
    "Whether the data is simple (pairs) or complex (triplets)"
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

    "TP",
    [] ( const Component& self ) -> DoubleRange
       { return self.TP(); },
    "The transition probabilities"
  )
  .def_property_readonly(

    "transition_probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.transitionProbabilities(); },
    "The transition probabilities"
  )
  .def_property_readonly(

    "GP",
    [] ( const Component& self ) -> DoubleRange
       { return self.GP(); },
    "The conditional probabilities"
  )
  .def_property_readonly(

    "conditional_probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.conditionalProbabilities(); },
       "The conditional probabilities"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
