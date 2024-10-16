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

void wrapShortRangeBreitWignerBlock( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::ShortRangeBreitWignerBlock;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ShortRangeBreitWignerBlock",
    "MF32 MT151 section - resonance parameters and variance/covariance block for\n"
    "                     in the SLBW or MLBW representation (LCOMP = 1)"
  );

  // wrap the section
  component
  .def(

    python::init< int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "mpar" ), python::arg( "energies" ),
    python::arg( "spins" ), python::arg( "gt" ), python::arg( "gn" ),
    python::arg( "gg" ), python::arg( "gf" ), python::arg( "values" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    mpar        the number of parameters with covariances\n"
    "    energies    the resonance energies (NRB values)\n"
    "    spins       the spin values (NRB values)\n"
    "    gt          the total widths (NRB values)\n"
    "    gn          the neutron widths (NRB values)\n"
    "    gg          the gamma widths (NRB values)\n"
    "    gf          the fission widths (NRB values)\n"
    "    values      the values of the upper diagonal covaraince matrix"
  )
  .def_property_readonly(

    "MPAR",
    [] ( const Component& self ) { return self.MPAR(); },
    "The number of resonance parameters with covariance data (for each resonance)"
  )
  .def_property_readonly(

    "number_parameters_with_covariances",
    [] ( const Component& self )
       { return self.numberParametersWithCovariances(); },
    "The number of resonance parameters with covariance data (for each resonance)"
  )
  .def_property_readonly(

    "NRB",
    [] ( const Component& self ) { return self.NRB(); },
    "The number of resonances for this l value"
  )
  .def_property_readonly(

    "number_resonances",
    [] ( const Component& self ) { return self.numberResonances(); },
    "The number of resonances for this l value"
  )
  .def_property_readonly(

    "ER",
    [] ( const Component& self ) -> DoubleRange
       { return self.ER(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "resonance_energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergies(); },
    "The resonance energies"
  )
  .def_property_readonly(

    "AJ",
    [] ( const Component& self ) -> DoubleRange
       { return self.AJ(); },
    "The spin values"
  )
  .def_property_readonly(

    "spin_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinValues(); },
    "The spin values"
  )
  .def_property_readonly(

    "GT",
    [] ( const Component& self ) -> DoubleRange
       { return self.GT(); },
    "The total widths"
  )
  .def_property_readonly(

    "total_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.totalWidths(); },
    "The total widths"
  )
  .def_property_readonly(

    "GN",
    [] ( const Component& self ) -> DoubleRange
       { return self.GN(); },
    "The neutron widths"
  )
  .def_property_readonly(

    "neutron_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronWidths(); },
    "The neutron widths"
  )
  .def_property_readonly(

    "GG",
    [] ( const Component& self ) -> DoubleRange
       { return self.GG(); },
    "The gamma widths"
  )
  .def_property_readonly(

    "gamma_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidths(); },
    "The gamma widths"
  )
  .def_property_readonly(

    "GF",
    [] ( const Component& self ) -> DoubleRange
       { return self.GF(); },
    "The fission widths"
  )
  .def_property_readonly(

    "fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.fissionWidths(); },
    "The fission widths"
  )
  .def_property_readonly(

    "NPARB",
    [] ( const Component& self )
       { return self.NPARB(); },
    "The order of the covariance matrix"
  )
  .def_property_readonly(

    "covariance_matrix_order",
    [] ( const Component& self )
       { return self.covarianceMatrixOrder(); },
    "The order of the covariance matrix"
  )
  .def_property_readonly(

    "NVS",
    [] ( const Component& self ) { return self.NVS(); },
    "The number of values in the upper triangular covariance matrix"
  )
  .def_property_readonly(

    "number_values",
    [] ( const Component& self ) { return self.numberValues(); },
    "The number of values in the upper triangular covariance matrix"
  )
  .def_property_readonly(

    "covariance_matrix",
    [] ( const Component& self ) -> DoubleRange
       { return self.covarianceMatrix(); },
    "The upper triangular covariance matrix"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
