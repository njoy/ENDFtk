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
void wrapIsotope( python::module& );
void wrapScatteringRadius( python::module& );
void wrapSpecialCase( python::module& );
void wrapBreitWignerLValue( python::module& );
void wrapReichMooreLValue( python::module& );
void wrapSingleLevelBreitWigner( python::module& );
void wrapMultiLevelBreitWigner( python::module& );
void wrapReichMoore( python::module& );

void wrapSection_2_151( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Isotope = njoy::ENDFtk::section::Type< 2, 151 >::Isotope;
  using ResonanceRange = njoy::ENDFtk::section::Type< 2, 151 >::ResonanceRange;
  using IsotopeRange = RandomAccessAnyView< Isotope >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< Isotope >(
      module,
      "any_view< Isotope, random_access >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT151",
    "MF151 - resonance parameters"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF2 MT151 section - resonance parameters"
  );

  // wrap components
  wrapIsotope( submodule );
  wrapScatteringRadius( submodule );
  wrapSpecialCase( submodule );
  wrapBreitWignerLValue( submodule );
  wrapReichMooreLValue( submodule );
  wrapSingleLevelBreitWigner( submodule );
  wrapMultiLevelBreitWigner( submodule );
  wrapReichMoore( submodule );

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
