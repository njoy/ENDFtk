// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/28.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf28 {

void wrapSubshellData( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 28 >::SubshellData;

  // wrap views of this component
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Component >(
      viewmodule,
      "any_view< SubshellData, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "SubshellData",
    "MF28 component - transition energies and probabilities for a given subshell"
  );

  // wrap the component
  component
  .def(

    python::init< unsigned int, double, unsigned int,
                  std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&,
                  std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "subshell" ), python::arg( "energy" ), python::arg( "eln" ),
    python::arg( "secondary" ) = 0., python::arg( "tertiary" ) = 0,
    python::arg( "energies" ) = 0., python::arg( "probabilities" ) = 0,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    subshell        the subshell designator\n"
    "    energy          the binding energy of the subshell\n"
    "    eln             the number of electrons in the subshell\n"
    "    secondary       the secondary subshell designators (NTR values)\n"
    "    tertiary        the tertiary subshell designators (NTR values)\n"
    "    energies        the transition energies (NTR values)\n"
    "    probabilities   the transition probabilities (NTR values)"
  )
  .def_property_readonly(

    "SUBI",
    &Component::SUBI,
    "The subshell designator"
  )
  .def_property_readonly(

    "subshell_designator",
    &Component::subshellDesignator,
    "The subshell designator"
  )
  .def_property_readonly(

    "NTR",
    &Component::NTR,
    "The number of transitions"
  )
  .def_property_readonly(

    "number_transitions",
    &Component::numberTransitions,
    "The number of transitions"
  )
  .def_property_readonly(

    "EBI",
    &Component::EBI,
    "The subshell binding energy"
  )
  .def_property_readonly(

    "subshell_binding_energy",
    &Component::subshellBindingEnergy,
    "The subshell binding energy"
  )
  .def_property_readonly(

    "ELN",
    &Component::ELN,
    "The number of electrons in the subshell"
  )
  .def_property_readonly(

    "number_subshell_electrons",
    &Component::numberSubshellElectrons,
    "The number of electrons in the subshell"
  )
  .def_property_readonly(

    "SUBJ",
    [] ( const Component& self ) -> IntRange
       { return self.SUBJ(); },
    "The secondary subshell designators (one for each transition)"
  )
  .def_property_readonly(

    "secondary_subshell_designators",
    [] ( const Component& self ) -> IntRange
       { return self.secondarySubshellDesignators(); },
    "The secondary subshell designators (one for each transition)"
  )
  .def_property_readonly(

    "SUBK",
    [] ( const Component& self ) -> IntRange
       { return self.SUBK(); },
    "The tertiary subshell designators (one for each transition)"
  )
  .def_property_readonly(

    "tertiary_subshell_designators",
    [] ( const Component& self ) -> IntRange
       { return self.tertiarySubshellDesignators(); },
    "The tertiary subshell designators (one for each transition)"
  )
  .def_property_readonly(

    "ETR",
    [] ( const Component& self ) -> DoubleRange
       { return self.ETR(); },
    "The transition energies"
  )
  .def_property_readonly(

    "transition_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.transitionEnergies(); },
    "The transition energies"
  )
  .def_property_readonly(

    "FTR",
    [] ( const Component& self ) -> DoubleRange
       { return self.FTR(); },
    "The transition probabilities"
  )
  .def_property_readonly(

    "transition_probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.transitionProbabilities(); },
    "The transition probabilities"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf28
