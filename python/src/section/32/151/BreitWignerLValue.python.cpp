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

void wrapBreitWignerLValue( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using Component = Section::BreitWignerLValue;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "BreitWignerLValue",
    "MF32 MT151 section - resonance parameters and variance/covariance data for\n"
    "                     a given l value in the SLBW or MLBW representation (LCOMP = 0)"
  );

  // wrap the section
  component
  .def(

    python::init< double, int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "awri" ), python::arg( "l" ), python::arg( "energies" ),
    python::arg( "spins" ), python::arg( "gt" ), python::arg( "gn" ),
    python::arg( "gg" ), python::arg( "gf" ), python::arg( "de2" ),
    python::arg( "dn2" ), python::arg( "dndg" ), python::arg( "dg2" ),
    python::arg( "dndf" ), python::arg( "dgdf" ), python::arg( "df2" ),
    python::arg( "djdn" ), python::arg( "djdg" ), python::arg( "djdf" ),
    python::arg( "df2" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self        the component\n"
    "    awri        the atomic weight ratio\n"
    "    l           the orbital angular momentum value\n"
    "    energies    the resonance energies (NRS values)\n"
    "    spins       the spin values (NRS values)\n"
    "    gt          the total widths (NRS values)\n"
    "    gn          the neutron widths (NRS values)\n"
    "    gg          the gamma widths (NRS values)\n"
    "    gf          the fission widths (NRS values)\n"
    "    de2         the energy variances (NRS values)\n"
    "    dn2         the neutron width variances (NRS values)\n"
    "    dndg        the neutron and gamma width covariances (NRS values)\n"
    "    dg2         the gamma width variances (NRS values)\n"
    "    dndf        the neutron and fission width covariances (NRS values)\n"
    "    dgdf        the gamma and fission width covariances (NRS values)\n"
    "    df2         the fission width variances (NRS values)\n"
    "    djdn        the spin and neutron width covariances (NRS values)\n"
    "    djdg        the spin and gamma width covariances (NRS values)\n"
    "    djdf        the spin and fission width covariances (NRS values)\n"
    "    df2         the spin variances (NRS values)"
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

    "L",
    [] ( const Component& self ) { return self.L(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "orbital_momentum",
    [] ( const Component& self ) { return self.orbitalMomentum(); },
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "NRS",
    [] ( const Component& self ) { return self.NRS(); },
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

    "DE2",
    [] ( const Component& self ) -> DoubleRange
       { return self.DE2(); },
    "The resonance energy variances"
  )
  .def_property_readonly(

    "resonance_energy_variances",
    [] ( const Component& self ) -> DoubleRange
       { return self.resonanceEnergyVariances(); },
    "The resonance energy variances"
  )
  .def_property_readonly(

    "DN2",
    [] ( const Component& self ) -> DoubleRange
       { return self.DN2(); },
    "The neutron width variances"
  )
  .def_property_readonly(

    "neutron_width_variances",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronWidthVariances(); },
    "The neutron width variances"
  )
  .def_property_readonly(

    "DNDG",
    [] ( const Component& self ) -> DoubleRange
       { return self.DNDG(); },
    "The neutron and gamma width covariances"
  )
  .def_property_readonly(

    "neutron_and_gamma_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronAndGammaWidthCovariances(); },
    "The neutron and gamma width covariances"
  )
  .def_property_readonly(

    "DG2",
    [] ( const Component& self ) -> DoubleRange
       { return self.DG2(); },
    "The gamma width variances"
  )
  .def_property_readonly(

    "gamma_width_variances",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaWidthVariances(); },
    "The gamma width variances"
  )
  .def_property_readonly(

    "DNDF",
    [] ( const Component& self ) -> DoubleRange
       { return self.DNDF(); },
    "The neutron and fission width covariances"
  )
  .def_property_readonly(

    "neutron_and_fission_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.neutronAndFissionWidthCovariances(); },
    "The neutron and fission width covariances"
  )
  .def_property_readonly(

    "DGDF",
    [] ( const Component& self ) -> DoubleRange
       { return self.DGDF(); },
    "The gamma and fission width covariances"
  )
  .def_property_readonly(

    "gamma_and_fission_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.gammaAndFissionWidthCovariances(); },
    "The gamma and fission width covariances"
  )
  .def_property_readonly(

    "DF2",
    [] ( const Component& self ) -> DoubleRange
       { return self.DF2(); },
    "The fission width variances"
  )
  .def_property_readonly(

    "fission_width_variances",
    [] ( const Component& self ) -> DoubleRange
       { return self.fissionWidthVariances(); },
    "The fission width variances"
  )
  .def_property_readonly(

    "DJDN",
    [] ( const Component& self ) -> DoubleRange
       { return self.DJDN(); },
    "The spin and neutron width covariances"
  )
  .def_property_readonly(

    "spin_and_neutron_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinAndNeutronWidthCovariances(); },
    "The spin and neutron width covariances"
  )
  .def_property_readonly(

    "DJDG",
    [] ( const Component& self ) -> DoubleRange
       { return self.DJDG(); },
    "The spin and gamma width covariances"
  )
  .def_property_readonly(

    "spin_and_gamma_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinAndGammaWidthCovariances(); },
    "The spin and gamma width covariances"
  )
  .def_property_readonly(

    "DJDF",
    [] ( const Component& self ) -> DoubleRange
       { return self.DJDF(); },
    "The spin and fission width covariances"
  )
  .def_property_readonly(

    "spin_and_fission_width_covariances",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinAndFissionWidthCovariances(); },
    "The spin and fission width covariances"
  )
  .def_property_readonly(

    "DJ2",
    [] ( const Component& self ) -> DoubleRange
       { return self.DJ2(); },
    "The spin variances"
  )
  .def_property_readonly(

    "spin_variances",
    [] ( const Component& self ) -> DoubleRange
       { return self.spinVariances(); },
    "The spin variances"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf32
