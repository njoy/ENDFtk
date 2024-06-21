// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapResonanceChannels( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::RMatrixLimited::ResonanceChannels;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceChannels",
    "MF2 MT151 section - resonance channel information for a spin group"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  int, int >(),
    python::arg( "spin" ), python::arg( "parity" ), python::arg( "ppi" ),
    python::arg( "l" ), python::arg( "s" ), python::arg( "b" ),
    python::arg( "apt" ), python::arg( "ape" ), python::arg( "kbk" ) = 0,
    python::arg( "kps" ) = 0,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    spin      the spin group's spin value\n"
    "    parity    the associated parity\n"
    "    l         the orbital momentum values (NCH values)\n"
    "    s         the channel spin values (NCH values)\n"
    "    b         the boundary condition values (NCH values)\n"
    "    apt       the true scattering radius values for the calculation\n"
    "              of the penetrability and the shift factor (NCH values)\n"
    "    ape       the true scattering radius values for the calculation\n"
    "              of the phase shift (NCH values)\n"
    "    kbk       the number of channels with a background R-matrix\n"
    "    kps       the phase shift option"
  )
  .def(

    python::init< double, double, std::vector< unsigned int >&&,
                  std::vector< unsigned int >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, int, int >(),
    python::arg( "spin" ), python::arg( "parity" ), python::arg( "ppi" ),
    python::arg( "l" ), python::arg( "s" ), python::arg( "b" ),
    python::arg( "ap" ), python::arg( "kbk" ) = 0, python::arg( "kps" ) = 0,
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    spin      the spin group's spin value\n"
    "    parity    the associated parity\n"
    "    l         the orbital momentum values (NCH values)\n"
    "    s         the channel spin values (NCH values)\n"
    "    b         the boundary condition values (NCH values)\n"
    "    ap        the scattering radius values (NCH values)\n"
    "    kbk       the number of channels with a background R-matrix\n"
    "    kps       the phase shift option"
  )
  .def_property_readonly(

    "AJ",
    &Component::AJ,
    "The spin J of the spin group"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The spin J of the spin group"
  )
  .def_property_readonly(

    "PJ",
    &Component::PJ,
    "The parity of the spin J"
  )
  .def_property_readonly(

    "parity",
    &Component::parity,
    "The parity of the spin J"
  )
  .def_property_readonly(

    "KBK",
    &Component::KBK,
    "The number of channels with background R-matrix values"
  )
  .def_property_readonly(

    "number_background_channels",
    &Component::numberBackgroundChannels,
    "The number of channels with background R-matrix values"
  )
  .def_property_readonly(

    "KPS",
    &Component::KPS,
    "The phase shift option"
  )
  .def_property_readonly(

    "phase_shift_option",
    &Component::phaseShiftOption,
    "The phase shift option"
  )
  .def_property_readonly(

    "NCH",
    &Component::NCH,
    "The number of channels"
  )
  .def_property_readonly(

    "number_channels",
    &Component::numberChannels,
    "The number of channels"
  )
  .def_property_readonly(

    "PPI",
    [] ( const Component& self ) -> IntRange
       { return self.PPI(); },
    "The particle pair numbers of each channel"
  )
  .def_property_readonly(

    "particle_pair_numbers",
    [] ( const Component& self ) -> IntRange
       { return self.particlePairNumbers(); },
    "The particle pair numbers of each channel"
  )
  .def_property_readonly(

    "L",
    [] ( const Component& self ) -> IntRange
       { return self.L(); },
    "The orbital momentum values for all channels"
  )
  .def_property_readonly(

    "orbital_momentum_values",
    [] ( const Component& self ) -> IntRange
       { return self.orbitalMomentumValues(); },
    "The orbital momentum values for all channels"
  )
  .def_property_readonly(

    "SCH",
    [] ( const Component& self ) -> DoubleRange
       { return self.SCH(); },
    "The channel spin values"
  )
  .def_property_readonly(

    "channel_spin_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.channelSpinValues(); },
    "The channel spin values"
  )
  .def_property_readonly(

    "BND",
    [] ( const Component& self ) -> DoubleRange
       { return self.BND(); },
    "The boundary condition values"
  )
  .def_property_readonly(

    "boundary_condition_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.boundaryConditionValues(); },
    "The boundary condition values"
  )
  .def_property_readonly(

    "APT",
    [] ( const Component& self ) -> DoubleRange
       { return self.APT(); },
    "The true channel radii (used in the calculation of the penetrability and\n"
    "shift factor)"
  )
  .def_property_readonly(

    "true_channel_radii",
    [] ( const Component& self ) -> DoubleRange
       { return self.trueChannelRadii(); },
       "The true channel radii (used in the calculation of the penetrability and\n"
       "shift factor)"
  )
  .def_property_readonly(

    "APE",
    [] ( const Component& self ) -> DoubleRange
       { return self.APE(); },
    "The effective channel radii (used in the calculation of the phase shift)"
  )
  .def_property_readonly(

    "effective_channel_radii",
    [] ( const Component& self ) -> DoubleRange
       { return self.effectiveChannelRadii(); },
    "The effective channel radii (used in the calculation of the phase shift)"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf2
