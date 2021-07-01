// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

void wrapDecayModes( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 457 >;
  using Component = Section::DecayModes;
  using DecayMode = Section::DecayMode;

  // wrap views created by this section

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DecayModes",
    "MF8 MT457 section - decay modes and branching ratio information"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< DecayMode >&& >(),
    python::arg( "spin" ), python::arg( "parity" ), python::arg( "modes" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    spin      the spin of the nuclide\n"
    "    parity    the parity (used if spin is zero)\n"
    "    modes     the decay decay modes"
  )
  .def(

    python::init< double, double >(),
    python::arg( "spin" ), python::arg( "parity" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    spin      the spin of the nuclide\n"
    "    parity    the parity (used if spin is zero)"
  )
  .def_property_readonly(

    "SPI",
    &Component::SPI,
    "The target spin"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The target spin"
  )
  .def_property_readonly(

    "PAR",
    &Component::PAR,
    "The target parity"
  )
  .def_property_readonly(

    "parity",
    &Component::parity,
    "The target parity"
  )
  .def_property_readonly(

    "NDK",
    &Component::NDK,
    "The number of decay modes"
  )
  .def_property_readonly(

    "number_decay_modes",
    &Component::numberDecayModes,
    "The number of decay modes"
  )
  .def_property_readonly(

    "decay_modes",
    [] ( const Component& self ) -> std::vector< DecayMode >
       { return ranges::to< std::vector< DecayMode > >( self.decayModes() ); },
    "The decay mode information"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf8
