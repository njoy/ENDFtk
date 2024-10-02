// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/2.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

  // declarations - components
  void wrapCoherentElastic( python::module&, python::module& );
  void wrapIncoherentElastic( python::module&, python::module& );
  void wrapMixedElastic( python::module&, python::module& );

}

void wrapSection_7_2( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 2 >;
  using ScatteringLaw = Section::ScatteringLaw;

  // wrap views created by this section

  // create the submodule
  python::module submodule = module.def_submodule(

    "MT2",
    "MT2 - coherent and incoherent elastic scattering"
  );

  // create the section
  python::class_< Section > section(

    submodule,
    "Section",
    "MF7 MT2 section - coherent and incoherent elastic scattering"
  );

  // wrap components
  mf7::wrapCoherentElastic( submodule, viewmodule );
  mf7::wrapIncoherentElastic( submodule, viewmodule );
  mf7::wrapMixedElastic( submodule, viewmodule );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( double zaid, double awr,
                       ScatteringLaw law )
                     { return Section( zaid, awr, std::move( law ) ); } ),
    python::arg( "zaid" ), python::arg( "awr" ), python::arg( "law" ),
    "Initialise the section using isotopes\n\n"
    "Arguments:\n"
    "    self    the section\n"
    "    zaid    the ZA value of the material\n"
    "    awr     the atomic weight ratio\n"
    "    law     the thermal scattering law"
  )
  .def_property_readonly(

    "LTHR",
    &Section::LTHR,
    "The LTHR flag (coherent or incoherent elastic scattering)"
  )
  .def_property_readonly(

    "elastic_scattering_type",
    &Section::elasticScatteringType,
    "The LTHR flag (coherent or incoherent elastic scattering)"
  )
  .def_property_readonly(

    "scattering_law",
    &Section::scatteringLaw,
    "The LTHR flag (coherent or incoherent elastic scattering)"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
