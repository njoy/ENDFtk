// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {
namespace lcomp2 {

void wrapSpinGroup( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using ResonanceChannels = Section::CompactRMatrixLimitedUncertainties::ResonanceChannels;
  using ResonanceParameters = Section::CompactRMatrixLimitedUncertainties::ResonanceParameters;
  using Component = Section::CompactRMatrixLimitedUncertainties::SpinGroup;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SpinGroup",
    "MF2 MT151 section - R-matrix limited spin group with resonance parameter uncertainties"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( ResonanceChannels channels,
                       ResonanceParameters parameters )
                     { return Component( std::move( channels ),
                                         std::move( parameters ) ); } ),
    python::arg( "channels" ), python::arg( "parameters" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    channels      the resonance channel information\n"
    "    parameters    the associated resonance parameters"
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

    "NRSA",
    &Component::NRSA,
    "The number of resonances"
  )
  .def_property_readonly(

    "number_resonances",
    &Component::numberResonances,
    "The number of resonances"
  )
  .def_property_readonly(

    "channels",
    &Component::channels,
    "The channel information"
  )
  .def_property_readonly(

    "parameters",
    &Component::parameters,
    "The resonance parameters for this spin group"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace lcomp2
} // namespace mf2
