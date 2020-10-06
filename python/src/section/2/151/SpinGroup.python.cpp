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
  using SpinGroup = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::SpinGroup;

  // provide a simple wrapper class to add a constructor
  class PythonSpinGroup : public SpinGroup {

  public:

    using SpinGroup::SpinGroup;

    PythonSpinGroup( const ResonanceChannels& channels,
                     const ResonanceParameters& parameters ) :
      SpinGroup( ResonanceChannels( channels ),
                 ResonanceParameters( parameters ) ) {}
  };
  using Component = PythonSpinGroup;

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
    &SpinGroup::AJ,
    "The spin J of the spin group"
  )
  .def_property_readonly(

    "spin",
    &SpinGroup::spin,
    "The spin J of the spin group"
  )
  .def_property_readonly(

    "PJ",
    &SpinGroup::PJ,
    "The parity of the spin J"
  )
  .def_property_readonly(

    "parity",
    &SpinGroup::parity,
    "The parity of the spin J"
  )
  .def_property_readonly(

    "NCH",
    &SpinGroup::NCH,
    "The number of channels"
  )
  .def_property_readonly(

    "number_channels",
    &SpinGroup::numberChannels,
    "The number of channels"
  )
  .def_property_readonly(

    "NRS",
    &SpinGroup::NRS,
    "The number of resonances"
  )
  .def_property_readonly(

    "number_resonances",
    &SpinGroup::numberResonances,
    "The number of resonances"
  )
  .def_property_readonly(

    "channels",
    &SpinGroup::channels,
    "The channel information"
  )
  .def_property_readonly(

    "parameters",
    &SpinGroup::parameters,
    "The resonance parameters for this spin group"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
