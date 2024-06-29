// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/4.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapScatteringLawConstants( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 4 >;
  using Component = Section::ScatteringLawConstants;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ScatteringLawConstants",
    "MF7 MT4 section - scattering law constants"
  );

  // wrap the section
  component
  .def(

    python::init< int, int, double, double,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< unsigned int >&&,
                  std::vector< unsigned int >&& >(),
    python::arg( "lln" ), python::arg( "ns" ), python::arg( "epsilon" ),
    python::arg( "emax" ), python::arg( "xs" ), python::arg( "awr" ),
    python::arg( "natoms" ), python::arg( "types" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    lln        the LLN flag - store S or ln(S)\n"
    "    ns         the number non-principal scatterers\n"
    "    epsilon    B(2) - the E/kT ratio\n"
    "    emax       B(4) - the maximum energy\n"
    "    xs         the total free atom cross section for each scatterer\n"
    "               (ns + 1 values)\n"
    "    awr        the atomic weight ratios for each scatterer\n"
    "               (ns + 1 values)\n"
    "    natoms     the number of atoms for each scatterer (ns + 1 values)\n"
    "    types      the function type for each secondary scatterer\n"
    "               (ns values)"
  )
  .def(

    python::init< int, double, double, double, double, unsigned int >(),
    python::arg( "lln" ), python::arg( "epsilon" ), python::arg( "emax" ),
    python::arg( "xs" ), python::arg( "awr" ), python::arg( "natoms" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    lln        the LLN flag - store S or ln(S)\n"
    "    epsilon    B(2) - the E/kT ratio\n"
    "    emax       B(4) - the maximum energy\n"
    "    xs         B(1) - the total free atom cross section\n"
    "    awr        B(3) - the atomic weight ratio in neutron mass units\n"
    "    natoms     B(6) - the number of principal scatterer atoms"
  )
  .def_property_readonly(

    "LLN",
    &Component::LLN,
    "The LLN flag (either S or ln(S) is stored)"
  )
  .def_property_readonly(

    "sab_storage_type",
    &Component::sabStorageType,
    "The LLN flag (either S or ln(S) is stored)"
  )
  .def_property_readonly(

    "NI",
    &Component::NI,
    "The size of the B array, equal to 6*(NS+1)"
  )
  .def_property_readonly(

    "number_constants",
    &Component::numberConstants,
    "The size of the B array, equal to 6*(NS+1)"
  )
  .def_property_readonly(

    "NS",
    &Component::NS,
    "The number of non-principal scattering atom types"
  )
  .def_property_readonly(

    "number_non_principal_scatterers",
    &Component::numberNonPrincipalScatterers,
    "The number of non-principal scattering atom types"
  )
  .def_property_readonly(

    "epsilon",
    &Component::epsilon,
    "The value of epsilon = E/kT, stored in B(2)"
  )
  .def_property_readonly(

    "EMAX",
    &Component::EMAX,
    "The upper energy limit of the thermal scattering law, stored in B(4)"
  )
  .def_property_readonly(

    "upper_energy_limit",
    &Component::upperEnergyLimit,
    "The upper energy limit of the thermal scattering law, stored in B(4)"
  )
  .def_property_readonly(

    "MSIGMA",
    [] ( const Component& self ) -> DoubleRange
       { return self.MSIGMA(); },
    "The total free atom cross section for each scattering atom type, stored\n"
    "in B(1), B(8) and B(14)"
  )
  .def_property_readonly(

    "total_free_cross_sections",
    [] ( const Component& self ) -> DoubleRange
       { return self.totalFreeCrossSections(); },
    "The total free atom cross section for each scattering atom type, stored\n"
    "in B(1), B(8) and B(14)"
  )
  .def_property_readonly(

    "AWR",
    [] ( const Component& self ) -> DoubleRange
       { return self.AWR(); },
    "The ratio of the atomic weight to the neutron mass for each scattering\n"
    "atom type, stored in B(3), B(9) and B(15)"
  )
  .def_property_readonly(

    "atomic_weight_ratios",
    [] ( const Component& self ) -> DoubleRange
       { return self.atomicWeightRatios(); },
    "The ratio of the atomic weight to the neutron mass for each scattering\n"
    "atom type, stored in B(3), B(9) and B(15)"
  )
  .def_property_readonly(

    "M",
    [] ( const Component& self ) -> DoubleRange
       { return self.M(); },
    "The number of atoms for each scattering atom type present in the\n"
    "molecule or unit cell, stored in B(6), B(12) and B(18)"
  )
  .def_property_readonly(

    "number_atoms",
    [] ( const Component& self ) -> DoubleRange
       { return self.numberAtoms(); },
    "The number of atoms for each scattering atom type present in the\n"
    "molecule or unit cell, stored in B(6), B(12) and B(18)"
  )
  .def_property_readonly(

    "analytical_function_types",
    [] ( const Component& self ) -> DoubleRange
       { return self.analyticalFunctionTypes(); },
    "The analytical function type for each non-principal scattering atom\n"
    "type, stored in B(7), B(13) and B(19)"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
