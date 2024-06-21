// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

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

} // namespace mf2

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
  mf2::wrapScatteringRadius( submodule, viewmodule );
  mf2::wrapSpecialCase( submodule, viewmodule );
  mf2::wrapBreitWignerLValue( submodule, viewmodule );
  mf2::wrapReichMooreLValue( submodule, viewmodule );
  mf2::wrapSingleLevelBreitWigner( submodule, viewmodule );
  mf2::wrapMultiLevelBreitWigner( submodule, viewmodule );
  mf2::wrapReichMoore( submodule, viewmodule );
  mf2::wrapParticlePairs( submodule, viewmodule );
  mf2::wrapResonanceChannels( submodule, viewmodule );
  mf2::wrapResonanceParameters( submodule, viewmodule );
  mf2::wrapNoBackgroundRMatrix( submodule, viewmodule );
  mf2::wrapSammyBackgroundRMatrix( submodule, viewmodule );
  mf2::wrapFrohnerBackgroundRMatrix( submodule, viewmodule );
  mf2::wrapTabulatedBackgroundRMatrix( submodule, viewmodule );
  mf2::wrapBackgroundChannels( submodule, viewmodule );
  mf2::wrapSpinGroup( submodule, viewmodule );
  mf2::wrapRMatrixLimited( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependentFissionWidthsJValue( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependentJValue( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyIndependentLValue( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependentFissionWidthsLValue( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependentLValue( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyIndependent( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependentFissionWidths( submodule, viewmodule );
  mf2::wrapUnresolvedEnergyDependent( submodule, viewmodule );
  mf2::wrapResonanceRange( submodule, viewmodule );
  mf2::wrapIsotope( submodule, viewmodule );

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

    python::init< int, double, std::vector< Isotope >&& >(),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "isotopes" ),
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    zaid        the ZA value of the material\n"
    "    awr         the atomic weight ratio\n"
    "    isotopes    the isotopes for the section"
  )
  .def(

    python::init< int, double, bool, std::vector< ResonanceRange >&& >(),
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

    python::init< int, double, double, double, double, double >(),
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
