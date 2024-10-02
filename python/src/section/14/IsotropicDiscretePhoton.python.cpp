// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/14.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf14 {

void wrapIsotropicDiscretePhoton( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 14 >;
  using Component = Section::IsotropicDiscretePhoton;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "IsotropicDiscretePhoton",
    "MF14 section - the angular distribution for a specific discrete photon \n"
    "               is isotropic"
  );

  // wrap the section
  component
  .def(

    python::init< double, double >(),
    python::arg( "energy" ), python::arg( "level" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self     the component\n"
    "    energy   the photon energy\n"
    "    level    the energy of the level from which the photon originates"
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
    "The photon energy"
  )
  .def_property_readonly(

    "photon_energy",
    &Component::photonEnergy,
    "The photon energy or the binding energy"
  )
  .def_property_readonly(

    "LI",
    [] ( const Component& self ) { return self.LI(); },
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "isotropic_distributions",
    [] ( const Component& self ) { return self.isotropicDistributions(); },
    "The isotropic angular distribution flag"
  )
  .def_property_readonly(

    "LTT",
    [] ( const Component& self ) { return self.LTT(); },
    "The distribution law"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution law"
  );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf14
