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

void wrapGeneralSingleLevelBreitWigner( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::GeneralSingleLevelBreitWigner;
  using ShortRangeBreitWignerBlock = Section::ShortRangeBreitWignerBlock;
  using LongRangeCovarianceBlock = Section::LongRangeCovarianceBlock;
  using ShortRangeBreitWignerBlockRange = RandomAccessAnyView< ShortRangeBreitWignerBlock >;
  using LongRangeCovarianceBlockRange = RandomAccessAnyView< LongRangeCovarianceBlock >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "GeneralSingleLevelBreitWigner",
    "MF32 MT151 section - Single level Breit-Wigner resonance parameters and\n"
    "                     covariances using LCOMP=1"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, double, double, unsigned int,
                  std::vector< ShortRangeBreitWignerBlock >&&,
                  std::vector< LongRangeCovarianceBlock >&& >(),
    python::arg( "awri" ), python::arg( "spin" ), python::arg( "ap" ),
    python::arg( "dap" ), python::arg( "nls" ), python::arg( "short" ),
    python::arg( "long" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    awri      the atomic mass ratio\n"
    "    spi       the target spin value\n"
    "    ap        the scattering radius\n"
    "    dap       the scattering radius uncertainty data\n"
    "    nls       the number of l values\n"
    "    short     the short range covariance blocks\n"
    "    long      the long range covariance blocks"
  )
  .def(

    python::init< double, double, double, unsigned int,
                  std::vector< ShortRangeBreitWignerBlock >&&,
                  std::vector< LongRangeCovarianceBlock >&& >(),
    python::arg( "awri" ), python::arg( "spin" ), python::arg( "ap" ),
    python::arg( "nls" ), python::arg( "short" ), python::arg( "long" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self      the component\n"
    "    awri      the atomic mass ratio\n"
    "    spi       the target spin value\n"
    "    ap        the scattering radius\n"
    "    nls       the number of l values\n"
    "    short     the short range covariance blocks\n"
    "    long      the long range covariance blocks"
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
    [] ( const Component& self ) -> ShortRangeBreitWignerBlockRange
       { return self.shortRangeBlocks(); },
    "The short range resonance covariance blocks"
  )
  .def_property_readonly(

    "long_range_blocks",
    [] ( const Component& self ) -> LongRangeCovarianceBlockRange
       { return self.longRangeBlocks(); },
    "The long range resonance covariance blocks"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
