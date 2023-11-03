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

void wrapIsotope( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::Isotope;
  using ResonanceRange = Section::ResonanceRange;
  using ResonanceRangeRange = RandomAccessAnyView< ResonanceRange >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ResonanceRange >(
      viewmodule,
      "any_view< MF32::ResonanceRange, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "Isotope",
    "MF32 MT151 section - an isotope with resonance energy ranges"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, bool, std::vector< ResonanceRange >&& >(),
    python::arg( "zai" ), python::arg( "abn" ), python::arg( "lfw" ),
    python::arg( "ranges" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    zai       the za of the isotope\n"
    "    abn       the abundance of the isotope\n"
    "    lfw       the lfw flag for unresolved resonances\n"
    "    ranges    the resonance ranges defined for the isotope"
  )
  .def_property_readonly(

    "ZAI",
    &Component::ZAI,
    "The ZA identifier of the isotope"
  )
  .def_property_readonly(

    "ABN",
    &Component::ABN,
    "The abundance of the isotope"
  )
  .def_property_readonly(

    "abundance",
    &Component::abundance,
    "The abundance of the isotope"
  )
  .def_property_readonly(

    "LFW",
    &Component::LFW,
    "The average fission flag"
  )
  .def_property_readonly(

    "average_fission_width_flag",
    &Component::averageFissionWidthFlag,
    "The average fission flag"
  )
  .def_property_readonly(

    "NER",
    &Component::NER,
    "The number of resonance ranges for this isotope"
  )
  .def_property_readonly(

    "number_resonance_ranges",
    &Component::numberResonanceRanges,
    "The number of resonance ranges for this isotope"
  )
  .def_property_readonly(

    "resonance_ranges",
    [] ( const Component& self ) -> ResonanceRangeRange
       { return self.resonanceRanges(); },
    "The resonance ranges for this isotope"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
