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

void wrapScatteringRadiusCovariances( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using ExplicitCovariance = njoy::ENDFtk::section::ExplicitCovariance;
  using Component = Section::ScatteringRadiusCovariances;
  using ExplicitCovarianceRange = RandomAccessAnyView< ExplicitCovariance >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ScatteringRadiusCovariances",
    "MF32 MT151 section - energy dependent scattering radius covariances"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< ExplicitCovariance >&& >(),
    python::arg( "data" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    data    the NI-type data blocks"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "The number of NI-type data blocks"
  )
  .def_property_readonly(

    "number_data_blocks",
    &Component::numberDataBlocks,
    "The number of NI-type data blocks"
  )
  .def_property_readonly(

    "data",
    [] ( const Component& self ) -> ExplicitCovarianceRange
       { return self.data(); },
    "The NI-type subsubsections"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
