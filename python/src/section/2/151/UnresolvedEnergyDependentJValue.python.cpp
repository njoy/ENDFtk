// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf2 {

void wrapUnresolvedEnergyDependentJValue( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 2, 151 >;
  using Component = Section::UnresolvedEnergyDependent::JValue;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedEnergyDependentJValue",
    "MF2 MT151 section - unresolved resonance data associated to a given J value\n"
    "                    with fully energy dependent widths (this is the most\n"
    "                    general case for unresolved resonances)"
  );

  // wrap the section
  component
  .def(

    python::init< double, int, int, int, int, int,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "spin" ), python::arg( "amun" ), python::arg( "amug" ),
    python::arg( "amuf" ), python::arg( "amux" ), python::arg( "interpolation" ),
    python::arg( "energies" ), python::arg( "d" ), python::arg( "gn" ),
    python::arg( "gg" ), python::arg( "gf" ), python::arg( "gx" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    spin             the spin\n"
    "    amun             the degrees of freedom for the neutron width\n"
    "    amug             the degrees of freedom for the gamma width\n"
    "    amuf             the degrees of freedom for the fission width\n"
    "    amux             the degrees of freedom for the competitive width\n"
    "    interpolation    the interpolation scheme for the cross sections\n"
    "    energies         the energy values (NE values)\n"
    "    d                the level spacings (NE values)\n"
    "    gn               the average neutron widths (NE values)\n"
    "    gg               the average gamma widths (NE values)\n"
    "    gf               the average fission widths (NE values)\n"
    "    gx               the average competitive widths (NE values)"
  )
  .def_property_readonly(

    "AJ",
    &Component::spin,
    "The spin value"
  )
  .def_property_readonly(

    "spin",
    &Component::spin,
    "The spin value"
  )
  .def_property_readonly(

    "AMUN",
    &Component::AMUN,
    "The degrees of freedom for the neutron width"
  )
  .def_property_readonly(

    "neutron_width_degrees_freedom",
    &Component::neutronWidthDegreesFreedom,
    "The degrees of freedom for the neutron width"
  )
  .def_property_readonly(

    "AMUG",
    &Component::AMUG,
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "gamma_width_degrees_freedom",
    &Component::gammaWidthDegreesFreedom,
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "AMUF",
    &Component::AMUF,
    "The degrees of freedom for the fission width"
  )
  .def_property_readonly(

    "fission_width_degrees_freedom",
    &Component::fissionWidthDegreesFreedom,
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "AMUX",
    &Component::AMUX,
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "competitive_width_degrees_freedom",
    &Component::competitiveWidthDegreesFreedom,
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "ES",
    [] ( const Component& self ) -> DoubleRange
       { return self.ES(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "D",
    [] ( const Component& self ) -> DoubleRange
       { return self.D(); },
    "The average level spacing values"
  )
  .def_property_readonly(

    "average_level_spacings",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageLevelSpacings(); },
    "The average level spacing values"
  )
  .def_property_readonly(

    "GN",
    [] ( const Component& self ) -> DoubleRange
       { return self.GN(); },
    "The average neutron widths"
  )
  .def_property_readonly(

    "average_neutron_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageNeutronWidths(); },
    "The average neutron widths"
  )
  .def_property_readonly(

    "GG",
    [] ( const Component& self ) -> DoubleRange
       { return self.GG(); },
    "The average gamma widths"
  )
  .def_property_readonly(

    "average_gamma_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageGammaWidths(); },
    "The average gamma widths"
  )
  .def_property_readonly(

    "GF",
    [] ( const Component& self ) -> DoubleRange
       { return self.GF(); },
    "The average fission widths"
  )
  .def_property_readonly(

    "average_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageFissionWidths(); },
    "The average fission widths"
  )
  .def_property_readonly(

    "GX",
    [] ( const Component& self ) -> DoubleRange
       { return self.GX(); },
    "The average competitive widths"
  )
  .def_property_readonly(

    "average_competitive_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageCompetitiveWidths(); },
    "The average competitive widths"
  )
  .def_property_readonly(

    "INT",
    &Component::INT,
    "The interpolation type"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
    "The number of energy points"
  )
  .def_property_readonly(

    "NR",
    [] ( const Component& self )
       { return self.NR(); },
    "The number of interpolation ranges"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Component& self )
       { return self.interpolants(); },
    "The interpolants"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Component& self )
       { return self.boundaries(); },
    "The interpolation range boundaries"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf2
