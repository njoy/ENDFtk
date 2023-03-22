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
namespace lcomp1 {

void wrapResonanceParameters( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::ShortRangeRMatrixLimitedBlock::ResonanceParameters;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters",
    "MF32 MT151 section - resonance parameters for the R-matrix limited\n"
    "                     representation (LCOMP = 1)"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< double >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "energies" ), python::arg( "parameters" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    energies      the resonance energies (NRS values)\n"
    "    parameters    the resonance parameters (NRS times NCH values)"
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

    "NRB",
    &Component::NRB,
    "The number of resonances"
  )
  .def_property_readonly(

    "number_resonances",
    &Component::numberResonances,
    "The number of resonances"
  )
  .def_property_readonly(

    "NX",
    &Component::NX,
    "The number of lines for all parameters"
  )
  .def_property_readonly(

    "number_lines",
    &Component::numberLines,
    "The number of lines for all parameters"
  )
  .def_property_readonly(

    "ER",
    [] ( const Component& self ) -> DoubleRange
       { return self.ER(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "resonance_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergies(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "GAM",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.GAM(); },
    "The resonance parameters"
  )
  .def_property_readonly(

    "resonance_parameters",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.resonanceParameters(); },
    "The resonance parameters"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace lcomp1
} // namespace mf32
