// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapResonanceParameters( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::RMatrixLimited::ResonanceParameters;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters",
    "MF2 MT151 section - resonance parameters for a spin group"
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

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
