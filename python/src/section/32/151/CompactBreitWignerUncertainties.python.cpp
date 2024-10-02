// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/32/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf32 {

void wrapCompactBreitWignerUncertainties( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::CompactBreitWignerUncertainties;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "CompactBreitWignerUncertainties",
    "MF32 MT151 section - The resonance parameters and uncertainties in the SLBW or MLBW "
    "                     representation (LCOMP = 2)"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, bool,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "qx" ), python::arg( "lrx" ),
    python::arg( "energies" ), python::arg( "spins" ), python::arg( "gt" ),
    python::arg( "gn" ), python::arg( "gg" ), python::arg( "gf" ),
    python::arg( "der" ), python::arg( "dgn" ), python::arg( "dgg" ),
    python::arg( "dgf" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    awri       the atomic weight ratio\n"
    "    qx         the competitive Q value\n"
    "    lrx        the competitive width flag\n"
    "    energies   the resonance energies (NRSA values)\n"
    "    spins      the spin values (NRSA values)\n"
    "    gt         the total widths (NRSA values)\n"
    "    gn         the neutron widths (NRSA values)\n"
    "    gg         the gamma widths (NRSA values)\n"
    "    gf         the fission widths (NRSA values)\n"
    "    der        the energy uncertainties (NRSA values)\n"
    "    dgn        the neutron width uncertainties (NRSA values)\n"
    "    dgg        the gamma width uncertainties (NRSA values)\n"
    "    dgf        the fission width uncertainties (NRSA values)"
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

    "QX",
    &Component::QX,
    "The Q value of the competitive reaction"
  )
  .def_property_readonly(

    "competitive_qvalue",
    &Component::competitiveQValue,
    "The Q value of the competitive reaction"
  )
  .def_property_readonly(

    "LRX",
    &Component::LRX,
    "The competitive width flag"
  )
  .def_property_readonly(

    "competitive_width_flag",
    &Component::competitiveWidthFlag,
    "The competitive width flag"
  )
  .def_property_readonly(

    "NRSA",
    [] ( const Component& self ) { return self.NRSA(); },
    "The number of resonances"
  )
  .def_property_readonly(

    "number_resonances",
    [] ( const Component& self ) { return self.numberResonances(); },
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

    "DGF",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGF(); },
    "The fission width uncertainties"
  )
  .def_property_readonly(

    "fission_width_uncertainties",
    [] ( const Component& self ) -> DoubleRange
       { return self.fissionWidthUncertainties(); },
    "The fission width uncertainties"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
