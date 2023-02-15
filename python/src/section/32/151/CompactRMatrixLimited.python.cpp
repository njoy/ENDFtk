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

void wrapCompactRMatrixLimited( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactRMatrixLimited;
  using CompactRMatrixLimitedUncertainties = Section::CompactRMatrixLimitedUncertainties;
  using CompactCorrelationMatrix = Section::CompactCorrelationMatrix;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CompactRMatrixLimited",
    "MF32 MT151 section - Reich-Moore resonance parameter covariances (LCOMP = 2)"
  );

  // wrap the section
  component
//  .def(
//
//    python::init( [] ( bool ifg,
//                       ReichMooreScatteringRadiusUncertainties dap,
//                       CompactRMatrixLimitedUncertainties parameters,
//                       CompactCorrelationMatrix matrix )
//                     { return Component( ifg,
//                                         std::move( dap ),
//                                         std::move( parameters ),
//                                         std::move( matrix ) ); } ),
//    python::arg( "ifg" ), python::arg( "dap" ),
//    python::arg( "parameters" ), python::arg( "matrix" ),
//    "Initialise the component\n\n"
//    "Arguments:\n"
//    "    self          the component\n"
//    "    ifg           flag to indicate whether or not the widths are reduced\n"
//    "    dap           the scattering radius uncertainty data\n"
//    "    parameters    the resonance parameters and uncertainties\n"
//    "    matrix        the correlation matrix"
//  )
  .def(

    python::init( [] ( bool ifg,
                       CompactRMatrixLimitedUncertainties parameters,
                       CompactCorrelationMatrix matrix )
                     { return Component( ifg, std::move( parameters ),
                                         std::move( matrix ) ); } ),
    python::arg( "ifg" ), python::arg( "parameters" ), python::arg( "matrix" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self          the component\n"
    "    ifg           flag to indicate whether or not the widths are reduced\n"
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

    "IFG",
    &Component::IFG,
    "The flag to indicate whether or not the widths are reduced"
  )
  .def_property_readonly(

    "reduced_widths",
    &Component::reducedWidths,
    "The flag to indicate whether or not the widths are reduced"
  )
  .def_property_readonly(

    "NJS",
    &Component::NJS,
    "The number of spin groups"
  )
  .def_property_readonly(

    "number_spin_groups",
    &Component::numberSpinGroups,
    "The number of spin groups"
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

    "uncertainties",
    [] ( const Component& self ) -> const CompactRMatrixLimitedUncertainties&
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
