// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapReichMooreScatteringRadiusUncertainties( python::module& module,
                                                  python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::ReichMooreScatteringRadiusUncertainties;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ReichMooreScatteringRadiusUncertainties",
    "MF32 MT151 section - scattering radius uncertainties in the Reich-Moore\n"
    "                     formalism (LCOMP = 1)"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< double >&& >(),
    python::arg( "dap" ), python::arg( "uncertainties" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    dap              the default scattering radius uncertainty\n"
    "    uncertainties    the l-dependent uncertainties"
  )
  .def_property_readonly(

    "DAP",
    &Component::DAP,
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "default_uncertainty",
    &Component::defaultUncertainty,
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "DAPL",
    [] ( const Component& self ) -> DoubleRange
       { return self.DAPL(); },
    "The l-dependent uncertainties"
  )
  .def_property_readonly(

    "uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.uncertainties(); },
    "The l-dependent uncertainties"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
