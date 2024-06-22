// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapCompactReichMooreUncertainties( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactReichMooreUncertainties;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CompactReichMooreUncertainties",
    "MF32 MT151 section - The resonance parameters and uncertainties in the RM "
    "                     representation (LCOMP = 2)"
  );

  // wrap the section
  component
  .def(

    python::init< double, double,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "apl" ),
    python::arg( "energies" ), python::arg( "spins" ),
    python::arg( "gn" ), python::arg( "gg" ),
    python::arg( "gfa" ), python::arg( "gfb" ),
    python::arg( "der" ), python::arg( "dgn" ), python::arg( "dgg" ),
    python::arg( "dgfa" ), python::arg( "dgfb" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    awri       the atomic weight ratio\n"
    "    apl        the l dependent scattering radius\n"
    "    energies   the resonance energies (NRSA values)\n"
    "    spins      the spin values (NRSA values)\n"
    "    gn         the neutron widths (NRSA values)\n"
    "    gg         the gamma widths (NRSA values)\n"
    "    gfa        the first fission widths (NRSA values)\n"
    "    gfb        the second fission widths (NRSA values)\n"
    "    der        the energy uncertainties (NRSA values)\n"
    "    dgn        the neutron width uncertainties (NRSA values)\n"
    "    dgg        the gamma width uncertainties (NRSA values)\n"
    "    dgfa       the first fission width uncertainties (NRSA values)\n"
    "    dgfb       the second fission width uncertainties (NRSA values)"
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

    "APL",
    &Component::APL,
    "The value of the l dependent scattering radius"
  )
  .def_property_readonly(

    "l_dependent_scattering_radius",
    &Component::lDependentScatteringRadius,
    "The value of the l dependent scattering radius"
  )
  .def_property_readonly(

    "NRSA",
    &Component::NRSA,
    "The number of resonances"
  )
  .def_property_readonly(

    "number_resonances",
    &Component::numberResonances,
    "The number of resonances"
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

    "GFA",
    [] ( const Component& self ) -> DoubleRange
       { return self.GFA(); },
    "The first fission widths"
  )
  .def_property_readonly(

    "first_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstFissionWidths(); },
    "The first fission widths"
  )
  .def_property_readonly(

    "GFB",
    [] ( const Component& self ) -> DoubleRange
       { return self.GFB(); },
    "The second fission widths"
  )
  .def_property_readonly(

    "second_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondFissionWidths(); },
    "The second fission widths"
  )
  .def_property_readonly(

    "DER",
    [] ( const Component& self ) -> DoubleRange
       { return self.DER(); },
    "The resonance energy uncertainties"
  )
  .def_property_readonly(

    "resonance_energy_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergyUncertainties(); },
    "The resonance energy uncertainties"
  )
  .def_property_readonly(

    "DGN",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGN(); },
    "The neutron width uncertainties"
  )
  .def_property_readonly(

    "neutron_width_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronWidthUncertainties(); },
    "The neutron width uncertainties"
  )
  .def_property_readonly(

    "DGG",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGG(); },
    "The gamma width uncertainties"
  )
  .def_property_readonly(

    "gamma_width_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidthUncertainties(); },
    "The gamma width uncertainties"
  )
  .def_property_readonly(

    "DGFA",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGFA(); },
    "The first fission width uncertainties"
  )
  .def_property_readonly(

    "first_fission_width_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.firstFissionWidthUncertainties(); },
    "The first fission width uncertainties"
  )
  .def_property_readonly(

    "DGFB",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGFB(); },
    "The second fission width uncertainties"
  )
  .def_property_readonly(

    "second_fission_width_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.secondFissionWidthUncertainties(); },
    "The second fission width uncertainties"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
