// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapCompactReichMoore( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactReichMoore;
  using ReichMooreScatteringRadiusUncertainties = Section::ReichMooreScatteringRadiusUncertainties;
  using OptionalScatteringRadiusUncertainties = std::optional< ReichMooreScatteringRadiusUncertainties >;
  using CompactReichMooreUncertainties = Section::CompactReichMooreUncertainties;
  using CompactCorrelationMatrix = Section::CompactCorrelationMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CompactReichMoore",
    "MF32 MT151 section - Reich-Moore resonance parameter covariances (LCOMP = 2)"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( double spi, double ap, bool lad,
                       ReichMooreScatteringRadiusUncertainties dap,
                       CompactReichMooreUncertainties parameters,
                       CompactCorrelationMatrix matrix )
                     { return Component( spi, ap, lad,
                                         std::move( dap ),
                                         std::move( parameters ),
                                         std::move( matrix ) ); } ),
    python::arg( "spi" ), python::arg( "ap" ), python::arg( "lad" ),
    python::arg( "dap" ), python::arg( "parameters" ), python::arg( "matrix" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    spi           the target spin value\n"
    "    ap            the scattering radius\n"
    "    lad           the angular distribution flag\n"
    "    dap           the scattering radius uncertainty data\n"
    "    parameters    the resonance parameters and uncertainties\n"
    "    matrix        the correlation matrix"
  )
  .def(

    python::init( [] ( double spi, double ap, bool lad,
                       CompactReichMooreUncertainties parameters,
                       CompactCorrelationMatrix matrix )
                     { return Component( spi, ap, lad, std::move( parameters ),
                                         std::move( matrix ) ); } ),
    python::arg( "spi" ), python::arg( "ap" ), python::arg( "lad" ),
    python::arg( "parameters" ), python::arg( "matrix" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    spi           the target spin value\n"
    "    ap            the scattering radius\n"
    "    lad           the angular distribution flag\n"
    "    parameters    the resonance parameters and uncertainties\n"
    "    matrix        the correlation matrix"
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

    "LAD",
    &Component::LAD,
    "The angular distribution flag"
  )
  .def_property_readonly(

    "angular_distributions_flag",
    &Component::angularDistributionsFlag,
    "The angular distribution flag"
  )
  .def_property_readonly(

    "DAP",
    [] ( const Component& self ) -> const OptionalScatteringRadiusUncertainties&
       { return self.DAP(); },
    "The scattering radius uncertainty"
  )
  .def_property_readonly(

    "scattering_radius_uncertainty",
    [] ( const Component& self ) -> const OptionalScatteringRadiusUncertainties&
       { return self.scatteringRadiusUncertainty(); },
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

    "uncertainties",
    [] ( const Component& self ) -> const CompactReichMooreUncertainties&
       { return self.uncertainties(); },
    "The resonance parameter uncertainties"
  )
  .def_property_readonly(

    "correlation_matrix",
    [] ( const Component& self ) -> const CompactCorrelationMatrix&
       { return self.correlationMatrix(); },
    "The correlation matrix"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
