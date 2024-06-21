// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

  // declarations - components
  void wrapAverageDecayEnergies( python::module&, python::module& );
  void wrapDecayMode( python::module&, python::module& );
  void wrapDecayModes( python::module&, python::module& );
  void wrapDiscreteSpectrum( python::module&, python::module& );
  void wrapContinuousSpectrum( python::module&, python::module& );
  void wrapDecaySpectrum( python::module&, python::module& );

}

void wrapSection_8_457( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 457 >;
  using AverageDecayEnergies = Section::AverageDecayEnergies;
  using DecayModes = Section::DecayModes;
  using DecaySpectrum = Section::DecaySpectrum;
  using DecaySpectrumRange = RandomAccessAnyView< DecaySpectrum >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT457",
    "MT457 - radioactive decay data"
  );

  // wrap components
  mf8::wrapAverageDecayEnergies( submodule, viewmodule );
  mf8::wrapDecayMode( submodule, viewmodule );
  mf8::wrapDecayModes( submodule, viewmodule );
  mf8::wrapDiscreteSpectrum( submodule, viewmodule );
  mf8::wrapContinuousSpectrum( submodule, viewmodule );
  mf8::wrapDecaySpectrum( submodule, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DecaySpectrum >(
      viewmodule,
      "any_view< DecaySpectrum, random_access >" );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF8 MT457 section - radioactive decay data"
  );

  // wrap the section
  section
  .def(

    python::init< double, double, int, int, double, double >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lis" ),
    python::arg( "liso" ), python::arg( "spin" ), python::arg( "parity" ),
    "Initialise the section for a stable isotope\n\n"
    "Arguments:\n"
    "    self      the section\n"
    "    zaid      the material ZAID value\n"
    "    awr       the atomic weight ratio\n"
    "    lis       the excited level number\n"
    "    liso      the isomeric state number\n"
    "    spin      the nuclide spin\n"
    "    parity    the nuclide parity"
  )
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr, int lis, int liso,
                       AverageDecayEnergies energies,
                       DecayModes modes,
                       std::vector< DecaySpectrum > spectra )
                     { return Section( zaid, awr, lis, liso,
                                       std::move( energies ),
                                       std::move( modes ),
                                       std::move( spectra ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lis" ),
    python::arg( "liso" ), python::arg( "energies" ), python::arg( "modes" ),
    python::arg( "spectra" ),
    "Initialise the section for a radioactive isotope\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    zaid        the material ZAID value\n"
    "    awr         the atomic weight ratio\n"
    "    lis         the excited level number\n"
    "    liso        the isomeric state number\n"
    "    energies    the average decay energies\n"
    "    modes       the decay modes\n"
    "    spectra     the decay spectra"
  )
  .def_property_readonly(

    "LIS",
    &Section::LIS,
    "The excited state number"
  )
  .def_property_readonly(

    "excited_state",
    &Section::excitedState,
    "The excited state number"
  )
  .def_property_readonly(

    "LISO",
    &Section::LISO,
    "The isomeric state number"
  )
  .def_property_readonly(

    "isomeric_state",
    &Section::isomericState,
    "The isomeric state number"
  )
  .def_property_readonly(

    "NST",
    &Section::NST,
    "The stability flag"
  )
  .def_property_readonly(

    "is_stable",
    &Section::isStable,
    "The stability flag"
  )
  .def_property_readonly(

    "NSP",
    &Section::NSP,
    "The number of decay spectra"
  )
  .def_property_readonly(

    "number_decay_spectra",
    &Section::numberDecaySpectra,
    "The number of decay spectra"
  )
  .def_property_readonly(

    "T",
    &Section::T,
    "The half life and its uncertainty"
  )
  .def_property_readonly(

    "half_life",
    &Section::halfLife,
    "The half life and its uncertainty"
  )
  .def_property_readonly(

    "SPI",
    &Section::SPI,
    "The target spin"
  )
  .def_property_readonly(

    "spin",
    &Section::spin,
    "The target spin"
  )
  .def_property_readonly(

    "PAR",
    &Section::PAR,
    "The target parity"
  )
  .def_property_readonly(

    "parity",
    &Section::parity,
    "The target parity"
  )
  .def_property_readonly(

    "average_decay_energies",
    &Section::averageDecayEnergies,
    "The half life and decay energy information"
  )
  .def_property_readonly(

    "decay_modes",
    &Section::decayModes,
    "The spin, parity and decay mode information"
  )
  .def_property_readonly(

    "decay_spectra",
    [] ( const Section& self ) -> DecaySpectrumRange
       { return self.decaySpectra(); },
    "The particle spectra"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
