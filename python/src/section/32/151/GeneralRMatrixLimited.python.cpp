// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapGeneralRMatrixLimited( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::GeneralRMatrixLimited;
  using ShortRangeRMatrixLimitedBlock = Section::ShortRangeRMatrixLimitedBlock;
  using ShortRangeRMatrixLimitedBlockRange = RandomAccessAnyView< ShortRangeRMatrixLimitedBlock >;

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ShortRangeRMatrixLimitedBlock >(
      viewmodule,
      "any_view< ShortRangeRMatrixLimitedBlock, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "GeneralRMatrixLimited",
    "MF32 MT151 section - R-matrix limited resonance parameters and covariances\n"
    "                     using LCOMP=1"
  );

  // wrap the section
  component
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init< double, std::vector< ShortRangeRMatrixLimitedBlock >&& >(),
    python::arg( "awri" ), python::arg( "short" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    awri      the atomic mass ratio\n"
    "    short     the short range covariance blocks"
  )
  .def_property_readonly(

    "LRU",
    [] ( const Component& self ) { return self.LRU(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "type",
    [] ( const Component& self ) { return self.type(); },
    "The resonance type (resolved or unresolved)"
  )
  .def_property_readonly(

    "LRF",
    [] ( const Component& self ) { return self.LRF(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "representation",
    [] ( const Component& self ) { return self.representation(); },
    "The resonance representation"
  )
  .def_property_readonly(

    "LFW",
    [] ( const Component& self ) { return self.LFW(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "average_fission_width_flag",
    [] ( const Component& self ) { return self.averageFissionWidthFlag(); },
    "The average fission flag"
  )
  .def_property_readonly(

    "LCOMP",
    [] ( const Component& self ) { return self.LCOMP(); },
    "The covariance representation type"
  )
  .def_property_readonly(

    "covariance_representation",
    [] ( const Component& self ) { return self.covarianceRepresentation(); },
    "The covariance representation type"
  )
  .def_property_readonly(

    "AWRI",
    [] ( const Component& self ) { return self.AWRI(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "atomic_weight_ratio",
    [] ( const Component& self ) { return self.atomicWeightRatio(); },
    "The atomic weight ratio of the current isotope"
  )
  .def_property_readonly(

    "SPI",
    [] ( const Component& self ) { return self.SPI(); },
    "The target spin"
  )
  .def_property_readonly(

    "spin",
    [] ( const Component& self ) { return self.spin(); },
    "The scattering radius"
  )
  .def_property_readonly(

    "AP",
    [] ( const Component& self ) { return self.AP(); },
    "The scattering radius"
  )
  .def_property_readonly(

    "scattering_radius",
    [] ( const Component& self ) { return self.scatteringRadius(); },
    "The scattering radius"
  )
  .def_property_readonly(

    "DAP",
    [] ( const Component& self ) { return self.DAP(); },
    "The scattering radius uncertainty"
  )
  .def_property_readonly(

    "scattering_radius_uncertainty",
    [] ( const Component& self ) { return self.scatteringRadiusUncertainty(); },
    "The scattering radius uncertainty"
  )
  .def_property_readonly(

    "ISR",
    [] ( const Component& self ) { return self.ISR(); },
    "The scattering radius uncertainty flag"
  )
  .def_property_readonly(

    "scattering_radius_uncertainty_flag",
    [] ( const Component& self ) { return self.scatteringRadiusUncertaintyFlag(); },
    "The scattering radius uncertainty flag"
  )
  .def_property_readonly(

    "NSRS",
    [] ( const Component& self ) { return self.NSRS(); },
    "The number of short range covariance blocks"
  )
  .def_property_readonly(

    "number_short_range_blocks",
    [] ( const Component& self ) { return self.numberShortRangeBlocks(); },
    "The number of short range covariance blocks"
  )
  .def_property_readonly(

    "NLRS",
    [] ( const Component& self ) { return self.NLRS(); },
    "The number of long range covariance blocks"
  )
  .def_property_readonly(

    "number_long_range_blocks",
    [] ( const Component& self ) { return self.numberLongRangeBlocks(); },
    "The number of long range covariance blocks"
  )
  .def_property_readonly(

    "short_range_blocks",
    [] ( const Component& self ) -> ShortRangeRMatrixLimitedBlockRange
       { return self.shortRangeBlocks(); },
    "The short range resonance covariance blocks"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
