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

void wrapResonanceParameters( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactRMatrixLimitedUncertainties::ResonanceParameters;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ResonanceParameters",
    "MF32 MT151 section - resonance parameter uncertainties for a spin group"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< double >&&,
                  std::vector< std::vector< double > >&&,
                  std::vector< double >&&,
                  std::vector< std::vector< double > >&& >(),
    python::arg( "energies" ), python::arg( "parameters" ),
    python::arg( "denergies" ), python::arg( "dparameters" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    energies      the resonance energies (NRS values)\n"
    "    parameters    the resonance parameters (NRS times NCH values)\n"
    "    denergies     the resonance energy uncertainties (NRS values)\n"
    "    dparameters   the resonance parameter uncertainties (NRS times NCH values)"
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

    "DER",
    [] ( const Component& self ) -> DoubleRange
       { return self.DER(); },
    "The resonance energy uncertainties"
  )
  .def_property_readonly(

    "resonance_energy_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergyUncertainties(); },
    "The resonance energy uncertainties"
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
  )
  .def_property_readonly(

    "DGAM",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.DGAM(); },
    "The resonance parameter uncertainties"
  )
  .def_property_readonly(

    "resonance_parameter_uncertainties",
    [] ( const Component& self ) -> DoubleRange2D
       { return self.resonanceParameterUncertainties(); },
    "The resonance parameters uncertainties"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace lcomp2
} // namespace mf32
