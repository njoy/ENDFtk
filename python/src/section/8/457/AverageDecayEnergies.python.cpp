// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

void wrapAverageDecayEnergies( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 457 >;
  using Component = Section::AverageDecayEnergies;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "AverageDecayEnergies",
    "MF8 MT457 section - half life information and average decay energies for\n"
    "                    radiation types"
  );

  // wrap the section
  component
  .def(

    python::init< std::array< double, 2 >,
                  std::vector< std::array< double, 2 > >&& >(),
    python::arg( "halflife" ),  python::arg( "energies" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    halflife    the half life and its associated uncertainty\n"
    "    energies    the decay energies and uncertainties for the various\n"
    "                radiation types (either 3 or 17 pairs)"
  )
  .def(

    python::init<>(),
    "Initialise the component for a stable nuclide\n\n"
    "Arguments:\n"
    "    self            the component"
  )
  .def_property_readonly(

    "T",
    &Component::T,
    "The half life and its uncertainty"
  )
  .def_property_readonly(

    "half_life",
    &Component::halfLife,
    "The half life and its uncertainty"
  )
  .def_property_readonly(

    "NCE",
    &Component::NCE,
    "The number of decay energies"
  )
  .def_property_readonly(

    "number_decay_energies",
    &Component::numberDecayEnergies,
    "The number of decay energies"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.E(); },
    "The decay energies and their uncertainties"
  )
  .def_property_readonly(

    "decay_energies",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.decayEnergies(); },
    "The decay energies and their uncertainties"
  )
  .def_property_readonly(

    "ELP",
    [] ( const Component& self ) -> DoubleRange
       { return self.ELP(); },
    "The decay energy and uncertainty for light particle decay"
  )
  .def_property_readonly(

    "light_particle_decay_energy",
    [] ( const Component& self ) -> DoubleRange
       { return self.lightParticleDecayEnergy(); },
    "The decay energy and uncertainty for light particle decay"
  )
  .def_property_readonly(

    "EEM",
    [] ( const Component& self ) -> DoubleRange
       { return self.EEM(); },
    "The decay energy and uncertainty electromagnetic radiation"
  )
  .def_property_readonly(

    "electromagnetic_decay_energy",
    [] ( const Component& self ) -> DoubleRange
       { return self.electromagneticDecayEnergy(); },
    "The decay energy and uncertainty electromagnetic radiation"
  )
  .def_property_readonly(

    "EHP",
    [] ( const Component& self ) -> DoubleRange
       { return self.EHP(); },
    "The decay energy and uncertainty for heavy particle decay"
  )
  .def_property_readonly(

    "heavy_particle_decay_energy",
    [] ( const Component& self ) -> DoubleRange
       { return self.heavyParticleDecayEnergy(); },
    "The decay energy and uncertainty for heavy particle decay"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf8
