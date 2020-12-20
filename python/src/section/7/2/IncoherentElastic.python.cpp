// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/2.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapIncoherentElastic( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 7, 2 >;
  using Component = Section::IncoherentElastic;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "IncoherentElastic",
    "MF7 MT2 section - incoherent elastic scattering"
  );

  // wrap the section
  component
  .def(

    python::init< double, std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "sb" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "temperatures" ),
    python::arg( "integrals" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    sb              the characteristic bound cross section\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    temperatures    the temperature values\n"
    "    integrals       the values of the Debye-Waller integral divided by\n"
    "                    the atomic mass (expressed in eV^-1)"
  )
  .def_property_readonly(

    "LTHR",
    [] ( const Component& self )
       { return self.LTHR(); },
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
  )
  .def_property_readonly(

    "elastic_scattering_type",
    &Component::elasticScatteringType,
    "The LTHR flag (coherent, incoherent or mixed elastic scattering)"
  )
  .def_property_readonly(

    "SB",
    &Component::SB,
    "The characteristic bound cross section (barns)"
  )
  .def_property_readonly(

    "bound_cross_section",
    &Component::boundCrossSection,
    "The characteristic bound cross section (barns)"
  )
  .def_property_readonly(

    "NT",
    &Component::NT,
    "The number of temperatures"
  )
  .def_property_readonly(

    "number_temperatures",
    &Component::numberTemperatures,
    "The number of temperatures"
  )
  .def_property_readonly(

    "T",
    [] ( const Component& self ) -> DoubleRange
       { return self.T(); },
    "The temperature values"
  )
  .def_property_readonly(

    "temperatures",
    [] ( const Component& self ) -> DoubleRange
       { return self.temperatures(); },
    "The temperature values"
  )
  .def_property_readonly(

    "W",
    [] ( const Component& self ) -> DoubleRange
       { return self.W(); },
    "The Debye-Waller integral divided by the atomic mass (eV^-1)"
  )
  .def_property_readonly(

    "debye_waller_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.debyeWallerValues(); },
    "The Debye-Waller integral divided by the atomic mass (eV^-1)"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
