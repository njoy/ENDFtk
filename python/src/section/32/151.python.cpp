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

// declarations - components
void wrapLimitedBreitWignerLValue( python::module&, python::module& );
void wrapLimitedSingleLevelBreitWigner( python::module&, python::module& );
void wrapLimitedMultiLevelBreitWigner( python::module&, python::module& );
void wrapShortRangeBreitWignerBlock( python::module&, python::module& );
void wrapShortRangeReichMooreBlock( python::module&, python::module& );
void wrapShortRangeRMatrixLimitedBlock( python::module&, python::module& );
void wrapReichMooreScatteringRadiusUncertainties( python::module&, python::module& );
void wrapResonanceParameters( python::module&, python::module& );
void wrapCovarianceMatrix( python::module&, python::module& );
void wrapGeneralSingleLevelBreitWigner( python::module&, python::module& );
void wrapGeneralMultiLevelBreitWigner( python::module&, python::module& );
void wrapGeneralReichMoore( python::module&, python::module& );
void wrapGeneralRMatrixLimited( python::module&, python::module& );
void wrapCompactCorrelationMatrix( python::module&, python::module& );
void wrapCompactBreitWignerUncertainties( python::module&, python::module& );
void wrapCompactReichMooreUncertainties( python::module&, python::module& );
void wrapCompactSingleLevelBreitWigner( python::module&, python::module& );
void wrapCompactMultiLevelBreitWigner( python::module&, python::module& );
void wrapCompactReichMoore( python::module&, python::module& );
void wrapResonanceRange( python::module&, python::module& );
void wrapIsotope( python::module&, python::module& );

} // namespace mf32

void wrapSection_32_151( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Isotope = Section::Isotope;
  using ResonanceRange = Section::ResonanceRange;
  using IsotopeRange = RandomAccessAnyView< Isotope >;
  using ShortRangeBreitWignerBlock = Section::ShortRangeBreitWignerBlock;
  using LongRangeCovarianceBlock = Section::LongRangeCovarianceBlock;
  using ShortRangeBreitWignerBlockRange = RandomAccessAnyView< ShortRangeBreitWignerBlock >;
  using LongRangeCovarianceBlockRange = RandomAccessAnyView< LongRangeCovarianceBlock >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT151",
    "MT151 - resonance parameter covariances"
  );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Isotope >(
      viewmodule,
      "any_view< MF32::Isotope, random_access >" );
  wrapRandomAccessAnyViewOf< ShortRangeBreitWignerBlock >(
      viewmodule,
      "any_view< ShortRangeBreitWignerBlock, random_access >" );
  wrapRandomAccessAnyViewOf< LongRangeCovarianceBlock >(
      viewmodule,
      "any_view< LongRangeCovarianceBlock, random_access >" );

  // wrap components
  mf32::wrapLimitedBreitWignerLValue( submodule, viewmodule );
  mf32::wrapLimitedSingleLevelBreitWigner( submodule, viewmodule );
  mf32::wrapLimitedMultiLevelBreitWigner( submodule, viewmodule );
  mf32::wrapShortRangeBreitWignerBlock( submodule, viewmodule );
  mf32::wrapShortRangeReichMooreBlock( submodule, viewmodule );
  mf32::wrapShortRangeRMatrixLimitedBlock( submodule, viewmodule );
  mf32::wrapReichMooreScatteringRadiusUncertainties( submodule, viewmodule );
  mf32::wrapResonanceParameters( submodule, viewmodule );
  mf32::wrapCovarianceMatrix( submodule, viewmodule );
  mf32::wrapGeneralSingleLevelBreitWigner( submodule, viewmodule );
  mf32::wrapGeneralMultiLevelBreitWigner( submodule, viewmodule );
  mf32::wrapGeneralReichMoore( submodule, viewmodule );
  mf32::wrapGeneralRMatrixLimited( submodule, viewmodule );
  mf32::wrapCompactCorrelationMatrix( submodule, viewmodule );
  mf32::wrapCompactBreitWignerUncertainties( submodule, viewmodule );
  mf32::wrapCompactReichMooreUncertainties( submodule, viewmodule );
  mf32::wrapCompactSingleLevelBreitWigner( submodule, viewmodule );
  mf32::wrapCompactMultiLevelBreitWigner( submodule, viewmodule );
  mf32::wrapCompactReichMoore( submodule, viewmodule );
  mf32::wrapResonanceRange( submodule, viewmodule );
  mf32::wrapIsotope( submodule, viewmodule );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF32 MT151 section - resonance parameter covariances"
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
