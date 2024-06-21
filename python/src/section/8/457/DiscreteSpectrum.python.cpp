// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

void wrapDiscreteSpectrum( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 8, 457 >;
  using Component = Section::DiscreteSpectrum;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "DiscreteSpectrum",
    "MF8 MT457 section - discrete spectrum information"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::array< double, 2 >&, std::array< double, 2 >&,
                  double >(),
    python::arg( "chain" ), python::arg( "energy" ), python::arg( "intensity" ),
    python::arg( "type" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    chain        the ENDF decay chain\n"
    "    energy       the energy and uncertainty\n"
    "    intensity    the relative intensity and uncertainty\n"
    "    type         the transition type"
  )
  .def(

    python::init< double, const std::array< double, 2 >&,
                  const std::array< double, 2 >&, double,
                  const std::array< double, 2 >& >(),
    python::arg( "chain" ), python::arg( "energy" ), python::arg( "intensity" ),
    python::arg( "type" ), python::arg( "ris" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    chain        the ENDF decay chain\n"
    "    energy       the energy and uncertainty\n"
    "    intensity    the relative intensity and uncertainty\n"
    "    type         the transition type\n"
    "    ris          internal pair formation coefficient or positron intensity"
  )
  .def(

    python::init< double, const std::array< double, 2 >&,
                  const std::array< double, 2 >&, double,
                  const std::array< double, 2 >&,
                  const std::array< double, 2 >& >(),
    python::arg( "chain" ), python::arg( "energy" ), python::arg( "intensity" ),
    python::arg( "type" ), python::arg( "ris" ), python::arg( "ricc" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    chain        the ENDF decay chain\n"
    "    energy       the energy and uncertainty\n"
    "    intensity    the relative intensity and uncertainty\n"
    "    type         the transition type\n"
    "    ris          internal pair formation coefficient or positron intensity\n"
    "    ricc         the total internal conversion coefficient"
  )
  .def(

    python::init< double, const std::array< double, 2 >&,
                  const std::array< double, 2 >&, double,
                  const std::array< double, 2 >&,
                  const std::array< double, 2 >&,
                  const std::array< double, 2 >&,
                  const std::array< double, 2 >& >(),
    python::arg( "chain" ), python::arg( "energy" ), python::arg( "intensity" ),
    python::arg( "type" ), python::arg( "ris" ), python::arg( "ricc" ),
    python::arg( "rick" ), python::arg( "ricl" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    chain        the ENDF decay chain\n"
    "    energy       the energy and uncertainty\n"
    "    intensity    the relative intensity and uncertainty\n"
    "    type         the transition type\n"
    "    ris          internal pair formation coefficient or positron intensity\n"
    "    ricc         the total internal conversion coefficient\n"
    "    rick         the K shell internal conversion coefficient\n"
    "    ricl         the L shell internal conversion coefficient"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "The number of entries"
  )
  .def_property_readonly(

    "RTYP",
    &Component::RTYP,
    "The decay chain responsible for this spectrum"
  )
  .def_property_readonly(

    "decay_chain",
    &Component::decayChain,
    "The decay chain responsible for this spectrum"
  )
  .def_property_readonly(

    "ER",
    &Component::ER,
    "The discrete energy value and uncertainty"
  )
  .def_property_readonly(

    "discrete_energy",
    &Component::discreteEnergy,
    "The discrete energy value and uncertainty"
  )
  .def_property_readonly(

    "RI",
    &Component::RI,
    "The relative intensity and uncertainty"
  )
  .def_property_readonly(

    "relative_intensity",
    &Component::relativeIntensity,
    "The relative intensity and uncertainty"
  )
  .def_property_readonly(

    "TYPE",
    &Component::TYPE,
    "The transition type for beta and electron capture"
  )
  .def_property_readonly(

    "type",
    &Component::type,
    "The transition type for beta and electron capture"
  )
  .def_property_readonly(

    "RIS",
    &Component::RIS,
    "The RIS value and its uncertainty, the internal pair formation\n"
    "coefficient (STYP=0.0) or the positron intensity (STYP=2.0)"
  )
  .def_property_readonly(

    "internal_pair_formation_coefficient",
    &Component::internalPairFormationCoefficient,
    "The RIS value and its uncertainty, the internal pair formation\n"
    "coefficient (STYP=0.0) or the positron intensity (STYP=2.0)"
  )
  .def_property_readonly(

    "RICC",
    &Component::RICC,
    "The total internal conversion coefficient value and its uncertainty\n"
    "(STYP=0.0 only)"
  )
  .def_property_readonly(

    "total_internal_conversion_coefficient",
    &Component::totalInternalConversionCoefficient,
    "The total internal conversion coefficient value and its uncertainty\n"
    "(STYP=0.0 only)"
  )
  .def_property_readonly(

    "RICK",
    &Component::RICK,
    "The K shell internal conversion coefficient  and its uncertainty\n"
    "(STYP=0.0 only)"
  )
  .def_property_readonly(

    "internal_conversion_coefficient_k_shell",
    &Component::internalConversionCoefficientKShell,
    "The K shell internal conversion coefficient  and its uncertainty\n"
    "(STYP=0.0 only)"
  )
  .def_property_readonly(

    "RICL",
    &Component::RICL,
    "The L shell internal conversion coefficient  and its uncertainty\n"
    "(STYP=0.0 only)"
  )
  .def_property_readonly(

    "internal_conversion_coefficient_l_shell",
    &Component::internalConversionCoefficientLShell,
    "The L shell internal conversion coefficient  and its uncertainty\n"
    "(STYP=0.0 only)"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf8
