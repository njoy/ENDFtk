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

void wrapDecaySpectrum( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 457 >;
  using Component = Section::DecaySpectrum;
  using DiscreteSpectrum = Section::DiscreteSpectrum;
  using ContinuousSpectrum = Section::ContinuousSpectrum;
  using DiscreteSpectrumRange = RandomAccessAnyView< DiscreteSpectrum >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DiscreteSpectrum >(
      viewmodule,
      "any_view< DiscreteSpectrum, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "DecaySpectrum",
    "MF8 MT457 section - spectrum information for a specific decay particle type"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::array< double, 2 >, std::array< double, 2 >,
                  std::vector< DiscreteSpectrum >&& >(),
    python::arg( "type" ), python::arg( "dnorm" ),
    python::arg( "energy" ), python::arg( "dspectra" ),
    "Initialise the component for discrete spectra only (LCON=0)\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    type        the particle type for which data is given\n"
    "    dnorm       the discrete normalisation factor and its uncertainty\n"
    "    energy      the average decay energy and its uncertainty\n"
    "    dspectra    the discrete spectra"
  )
  .def(

    python::init( [] ( double type,
                       std::array< double, 2 > cnorm,
                       std::array< double, 2 > energy,
                       ContinuousSpectrum cspectrum )
                     { return Component( type, cnorm, energy,
                                         std::move( cspectrum ) ); } ),
    python::arg( "type" ), python::arg( "cnorm" ),
    python::arg( "energy" ), python::arg( "cspectrum" ),
    "Initialise the component for a continuous spectrum only (LCON=1)\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    type         the particle type for which spectral data is given\n"
    "    cnorm        the continuous normalisation factor and its uncertainty\n"
    "    energy       the average decay energy and its uncertainty\n"
    "    cspectrum    the continuous spectrum"
  )
  .def(

    python::init( [] ( double type,
                       std::array< double, 2 > dnorm,
                       std::array< double, 2 > cnorm,
                       std::array< double, 2 > energy,
                       std::vector< DiscreteSpectrum > dspectra,
                       ContinuousSpectrum cspectrum )
                     { return Component( type, dnorm, cnorm, energy,
                                         std::move( dspectra ),
                                         std::move( cspectrum ) ); } ),
    python::arg( "type" ), python::arg( "dnorm" ), python::arg( "cnorm" ),
    python::arg( "energy" ), python::arg( "dspectra" ),
    python::arg( "cspectrum" ),
    "Initialise the component for discrete and continuous spectra (LCON=2)\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    type         the particle type for which spectral data is given\n"
    "    dnorm        the spectra normalisation factor and its uncertainty\n"
    "    cnorm        the continuous normalisation factor and its uncertainty\n"
    "    energy       the average decay energy and its uncertainty\n"
    "    dspectra     the discrete spectra\n"
    "    cspectrum    the continuous spectrum"
  )
  .def_property_readonly(

    "STYP",
    &Component::STYP,
    "The radiation type STYP for which spectral data is given"
  )
  .def_property_readonly(

    "radiation_type",
    &Component::radiationType,
    "The radiation type STYP for which spectral data is given"
  )
  .def_property_readonly(

    "LCON",
    &Component::LCON,
    "The spectral type flag"
  )
  .def_property_readonly(

    "spectral_type_flag",
    &Component::spectralTypeFlag,
    "The spectral type flag"
  )
  .def_property_readonly(

    "LCOV",
    &Component::LCOV,
    "The covariance data flag"
  )
  .def_property_readonly(

    "covariance_flag",
    &Component::covarianceFlag,
    "The covariance data flag"
  )
  .def_property_readonly(

    "NER",
    &Component::NER,
    "The number of discrete decay spectra"
  )
  .def_property_readonly(

    "number_discrete_spectra",
    &Component::numberDiscreteSpectra,
    "The number of discrete decay spectra"
  )
  .def_property_readonly(

    "FD",
    &Component::FD,
    "The discrete normalisation factor and its uncertainty"
  )
  .def_property_readonly(

    "discrete_normalisation_factor",
    &Component::discreteNormalisationFactor,
    "The discrete normalisation factor and its uncertainty"
  )
  .def_property_readonly(

    "FC",
    &Component::FC,
    "The continuous normalisation factor and its uncertainty"
  )
  .def_property_readonly(

    "continuous_normalisation_factor",
    &Component::continuousNormalisationFactor,
    "The continuous normalisation factor and its uncertainty"
  )
  .def_property_readonly(

    "ERAV",
    &Component::ERAV,
    "The average decay energy and its uncertainty"
  )
  .def_property_readonly(

    "average_decay_energy",
    &Component::averageDecayEnergy,
    "The average decay energy and its uncertainty"
  )
  .def_property_readonly(

    "discrete_spectra",
    [] ( const Component& self ) -> DiscreteSpectrumRange
       { return self.discreteSpectra(); },
    "The discrete spectra, if any are defined"
  )
  .def_property_readonly(

    "continuous_spectrum",
    &Component::continuousSpectrum,
    "The continuous spectrum, if it is defined"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf8
