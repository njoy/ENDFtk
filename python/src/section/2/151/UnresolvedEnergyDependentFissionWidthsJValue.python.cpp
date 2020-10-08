// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapUnresolvedEnergyDependentFissionWidthsJValue( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::UnresolvedEnergyDependentFissionWidths::JValue;
  using DoubleRange = RandomAccessAnyView< double >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "UnresolvedEnergyDependentFissionWidthsJValue",
    "MF2 MT151 section - Unresolved resonance data associated to a given\n"
    "                    J value when only the fission width is energy dependent"
  );

  // wrap the section
  component
  .def(

    python::init< int, double, double, int, int,
                  double, double, std::vector< double >&& >(),
    python::arg( "l" ), python::arg( "spin" ),
    python::arg( "d" ), python::arg( "amun" ), python::arg( "amuf" ),
    python::arg( "gn" ), python::arg( "gg" ), python::arg( "gf" ),
    "Initialise the unresolved energy dependent fission width j value data\n\n"
    "Arguments:\n"
    "    self    the unresolved energy dependent fission width j value object\n"
    "    l       the orbital angular momentum value\n"
    "    spin    the spin\n"
    "    d       the level spacing\n"
    "    amun    the degrees of freedom for the neutron width\n"
    "    amuf    the degrees of freedom for the fission width\n"
    "    gn      the average neutron width\n"
    "    gg      the average gamma width\n"
    "    gf      the average fission widths"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "jvalue" ),
    "Initialise the unresolved energy dependent fission widths j value with\n"
    "another j value\n\n"
    "Arguments:\n"
    "    self      the unresolved energy dependent fission widths j value object\n"
    "    lvalue    the j value to be copied"
  )
  .def_property_readonly(

    "L",
    &Component::L,
    "The value of the orbital momentum l"
  )
  .def_property_readonly(

    "orbital_momentum",
    &Component::orbitalMomentum,
    "The value of the orbital momentum l"
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
    [] ( const Component& self )
       { return self.AMUG(); },
    "The degrees of freedom for the gamma width"
  )
  .def_property_readonly(

    "gamma_width_degrees_freedom",
    [] ( const Component& self )
       { return self.gammaWidthDegreesFreedom(); },
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
    [] ( const Component& self )
       { return self.AMUX(); },
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "competitive_width_degrees_freedom",
    [] ( const Component& self )
       { return self.competitiveWidthDegreesFreedom(); },
    "The degrees of freedom for the competitive width"
  )
  .def_property_readonly(

    "D",
    &Component::D,
    "The average level spacing"
  )
  .def_property_readonly(

    "average_level_spacing",
    &Component::averageLevelSpacing,
    "The average level spacing"
  )
  .def_property_readonly(

    "GN",
    &Component::GN,
    "The average neutron width"
  )
  .def_property_readonly(

    "average_neutron_width",
    &Component::averageNeutronWidth,
    "The average neutron width"
  )
  .def_property_readonly(

    "GG",
    &Component::GG,
    "The average gamma width"
  )
  .def_property_readonly(

    "average_gamma_width",
    &Component::averageGammaWidth,
    "The average gamma width"
  )
  .def_property_readonly(

    "GF",
    [] ( const Component& self ) -> DoubleRange
       { return self.GF(); },
    "The average fission widths (energy dependent)"
  )
  .def_property_readonly(

    "average_fission_widths",
    [] ( const Component& self ) -> DoubleRange
       { return self.averageFissionWidths(); },
    "The average fission widths (energy dependent)"
  )
  .def_property_readonly(

    "GX",
    [] ( const Component& self )
       { return self.GX(); },
    "The average competitive width"
  )
  .def_property_readonly(

    "average_competitive_width",
    [] ( const Component& self )
       { return self.averageCompetitiveWidth(); },
    "The average competitive width"
  )
  .def_property_readonly(

    "NE",
    &Component::NE,
    "The number of average fission width points"
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

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
