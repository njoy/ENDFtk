// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
void wrapScatteringRadius( python::module&, python::module& );
void wrapSpecialCase( python::module&, python::module& );
void wrapBreitWignerLValue( python::module&, python::module& );
void wrapReichMooreLValue( python::module&, python::module& );
void wrapSingleLevelBreitWigner( python::module&, python::module& );
void wrapMultiLevelBreitWigner( python::module&, python::module& );
void wrapReichMoore( python::module&, python::module& );
void wrapParticlePairs( python::module&, python::module& );
void wrapResonanceChannels( python::module&, python::module& );
void wrapResonanceParameters( python::module&, python::module& );
void wrapNoBackgroundRMatrix( python::module&, python::module& );
void wrapSammyBackgroundRMatrix( python::module&, python::module& );
void wrapFrohnerBackgroundRMatrix( python::module&, python::module& );
void wrapTabulatedBackgroundRMatrix( python::module&, python::module& );
void wrapBackgroundChannels( python::module&, python::module& );
void wrapSpinGroup( python::module&, python::module& );
void wrapRMatrixLimited( python::module&, python::module& );
void wrapUnresolvedEnergyDependentFissionWidthsJValue( python::module&, python::module& );
void wrapUnresolvedEnergyDependentJValue( python::module&, python::module& );
void wrapUnresolvedEnergyIndependentLValue( python::module&, python::module& );
void wrapUnresolvedEnergyDependentFissionWidthsLValue( python::module&, python::module& );
void wrapUnresolvedEnergyDependentLValue( python::module&, python::module& );
void wrapUnresolvedEnergyIndependent( python::module&, python::module& );
void wrapUnresolvedEnergyDependentFissionWidths( python::module&, python::module& );
void wrapUnresolvedEnergyDependent( python::module&, python::module& );
void wrapResonanceRange( python::module&, python::module& );
void wrapIsotope( python::module&, python::module& );

void wrapSection_2_151( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Isotope = Section::Isotope;
  using ResonanceRange = Section::ResonanceRange;
  using IsotopeRange = RandomAccessAnyView< Isotope >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT151",
    "MT151 - resonance parameters"
  );

  // wrap components
  wrapScatteringRadius( submodule, viewmodule );
  wrapSpecialCase( submodule, viewmodule );
  wrapBreitWignerLValue( submodule, viewmodule );
  wrapReichMooreLValue( submodule, viewmodule );
  wrapSingleLevelBreitWigner( submodule, viewmodule );
  wrapMultiLevelBreitWigner( submodule, viewmodule );
  wrapReichMoore( submodule, viewmodule );
  wrapParticlePairs( submodule, viewmodule );
  wrapResonanceChannels( submodule, viewmodule );
  wrapResonanceParameters( submodule, viewmodule );
  wrapNoBackgroundRMatrix( submodule, viewmodule );
  wrapSammyBackgroundRMatrix( submodule, viewmodule );
  wrapFrohnerBackgroundRMatrix( submodule, viewmodule );
  wrapTabulatedBackgroundRMatrix( submodule, viewmodule );
  wrapBackgroundChannels( submodule, viewmodule );
  wrapSpinGroup( submodule, viewmodule );
  wrapRMatrixLimited( submodule, viewmodule );
  wrapUnresolvedEnergyDependentFissionWidthsJValue( submodule, viewmodule );
  wrapUnresolvedEnergyDependentJValue( submodule, viewmodule );
  wrapUnresolvedEnergyIndependentLValue( submodule, viewmodule );
  wrapUnresolvedEnergyDependentFissionWidthsLValue( submodule, viewmodule );
  wrapUnresolvedEnergyDependentLValue( submodule, viewmodule );
  wrapUnresolvedEnergyIndependent( submodule, viewmodule );
  wrapUnresolvedEnergyDependentFissionWidths( submodule, viewmodule );
  wrapUnresolvedEnergyDependent( submodule, viewmodule );
  wrapResonanceRange( submodule, viewmodule );
  wrapIsotope( submodule, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Isotope >(
      viewmodule,
      "any_view< Isotope, random_access >" );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF2 MT151 section - resonance parameters"
  );

  // wrap the section
  section
  .def(

    python::init< double, double, std::vector< Isotope >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "isotopes" ),
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    zaid        the ZA value of the material\n"
    "    awr         the atomic weight ratio\n"
    "    isotopes    the isotopes for the section"
  )
  .def(

    python::init< double, double, bool, std::vector< ResonanceRange >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lfw" ),
    python::arg( "ranges" ),
    "Initialise the section using a single isotope\n\n"
    "Arguments:\n"
    "    self      the section\n"
    "    zaid      the ZA value of the material\n"
    "    awr       the atomic weight ratio\n"
    "    lfw       the lfw flag for unresolved resonances\n"
    "    ranges    the resonance ranges defined for the isotope"
  )
  .def(

    python::init< double, double, double, double, double, double >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "el" ),
    python::arg( "eh" ), python::arg( "spin" ), python::arg( "ap" ),
    "Initialise the section for the special case (only scattering radius is\n"
    "given)\n\n"
    "Arguments:\n"
    "    self    the section\n"
    "    zaid    the ZA value of the material\n"
    "    awr     the atomic weight ratio\n"
    "    el      the lower limit of the resonance range\n"
    "    eh      the upper limit of the resonance range\n"
    "    spin    the spin of the target nucleus\n"
    "    ap      the scattering radius (in units of 10^-12 cm)"
  )
  .def_property_readonly(

    "NIS",
    &Section::NIS,
    "The number of isotopes"
  )
  .def_property_readonly(

    "number_isotopes",
    &Section::numberIsotopes,
    "The number of isotopes"
  )
  .def_property_readonly(

    "isotopes",
    [] ( const Section& self ) -> IsotopeRange
       { return self.isotopes(); },
    "The isotopes defined in the section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
