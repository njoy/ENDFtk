// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/2.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapMixedElastic( python::module& module ) {

  // type aliases
  using CoherentElastic = njoy::ENDFtk::section::Type< 7, 2 >::CoherentElastic;
  using IncoherentElastic = njoy::ENDFtk::section::Type< 7, 2 >::IncoherentElastic;
  using Component = njoy::ENDFtk::section::Type< 7, 2 >::MixedElastic;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "MixedElastic",
    "MF7 MT2 section - mixed coherent and incoherent elastic scattering"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( CoherentElastic coherent,
                       IncoherentElastic incoherent )
                     { return Component( std::move( coherent ),
                                         std::move( incoherent ) ); } ),
    python::arg( "coherent" ), python::arg( "incoherent" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    coherent      the coherent elastic data\n"
    "    incoherent    the incoherent elastic data"
  )
  .def_property_readonly(

    "LTHR",
    [] ( const Component& self )
       { return self.LTHR(); },
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
  )
  .def_property_readonly(

    "elastic_scattering_type",
    &Component::elasticScatteringType,
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
  )
  .def_property_readonly(

    "coherent",
    &Component::coherent,
    "The coherent elastic scattering data"
  )
  .def_property_readonly(

    "incoherent",
    &Component::incoherent,
    "The incoherent elastic scattering data"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
