// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapSpinGroup( python::module& module ) {

  // type aliases
  using ResonanceChannels = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceChannels;
  using ResonanceParameters = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceParameters;
  using BackgroundChannels = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::BackgroundChannels;
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "SpinGroup",
    "MF2 MT151 section - R-matrix limited spin group with resonance parameters"
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
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( ResonanceChannels channels,
                       ResonanceParameters parameters,
                       BackgroundChannels background )
                     { return Component( std::move( channels ),
                                         std::move( parameters ),
                                         std::move( background ) ); } ),
    python::arg( "channels" ), python::arg( "parameters" ),
    python::arg( "background" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    channels      the resonance channel information\n"
    "    parameters    the associated resonance parameters\n"
    "    background    the background R-matrices"
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

    "NRS",
    &Component::NRS,
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
  )
  .def_property_readonly(

    "background",
    &Component::background,
    "The background R-matrix values for the spin group channels"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
