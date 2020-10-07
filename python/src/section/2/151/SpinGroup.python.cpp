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

    python::init< const ResonanceChannels&, const ResonanceParameters& >(),
    python::arg( "channels" ), python::arg( "parameters" ),
    "Initialise the resonance channel for a spin group\n\n"
    "Arguments:\n"
    "    self          the spin group object\n"
    "    channels      the resonance channel information\n"
    "    parameters    the associated resonance parameters"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "group" ),
    "Initialise the spin group with another spin group\n\n"
    "Arguments:\n"
    "    self     the spin group object\n"
    "    group    the group to be copied"
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
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
