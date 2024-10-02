// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/13.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapPartialCrossSection( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 13 >;
  using Component = Section::PartialCrossSection;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "PartialCrossSection",
    "MF13 section - a partial photon cross section (either for the continuum\n"
    "               or a discrete photon)"
  );

  // wrap the section
  component
  .def(

    python::init< double, double, int, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "level" ),
    python::arg( "lp" ), python::arg( "lf" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "xs" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    energy            the photon or binding energy\n"
    "    level             the energy of the level from which the photon\n"
    "                      originates\n"
    "    lp                the primary photon flag (0, 1 or 2)\n"
    "    lf                the photon energy distribution law\n"
    "    boundaries        the interpolation range boundaries\n"
    "    interpolants      the interpolation types for each range\n"
    "    energies          the energy values\n"
    "    xs                the cross section values"
  )
  .def_property_readonly(

    "ES",
    &Component::ES,
    "The energy of the level from which the photon originates"
  )
  .def_property_readonly(

    "level_energy",
    &Component::levelEnergy,
    "The energy of the level from which the photon originates"
  )
  .def_property_readonly(

    "EG",
    &Component::EG,
    "The photon energy or the binding energy"
  )
  .def_property_readonly(

    "photon_or_binding_energy",
    &Component::photonOrBindingEnergy,
    "The photon energy or the binding energy"
  )
  .def_property_readonly(

    "LP",
    &Component::LP,
    "The primary photon flag value"
  )
  .def_property_readonly(

    "primary_photon_flag",
    &Component::primaryPhotonFlag,
    "The primary photon flag value"
  )
  .def_property_readonly(

    "LF",
    &Component::LF,
    "The photon energy distribution law number"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The photon energy distribution law number"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The incident energy values"
  )
  .def_property_readonly(

    "XS",
    [] ( const Component& self ) -> DoubleRange
       { return self.XS(); },
    "The cross section values"
  )
  .def_property_readonly(

    "cross_sections",
    [] ( const Component& self ) -> DoubleRange
       { return self.crossSections(); },
    "The cross section values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}
