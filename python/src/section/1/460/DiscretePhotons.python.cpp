// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/1/460.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf1 {
namespace mt460 {

void wrapDiscretePhotons( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 1, 460 >::DiscretePhotons;
  using DiscretePhotonMultiplicity = njoy::ENDFtk::section::Type< 1, 460 >::DiscretePhotonMultiplicity;
  using DiscretePhotonMultiplicityRange = RandomAccessAnyView< DiscretePhotonMultiplicity >;

  // wrap views created by this component
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< DiscretePhotonMultiplicity >(
      viewmodule,
      "any_view< DiscretePhotonMultiplicity, random_access >" );

  // create the component
  python::class_< Component > component(

    module,
    "DiscretePhotons",
    "MF1 MT460 component - delayed photons given as discrete photon\n"
    "                      multiplicities"
  );

  // wrap the component
  component
  .def(

    python::init< std::vector< DiscretePhotonMultiplicity >&& >(),
    python::arg( "photons" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self       the component\n"
    "    photons    the discrete photon data"
  )
  .def_property_readonly(

    "LO",
    [] ( const Component& self ) { return self.LO(); },
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "representation",
    &Component::representation,
    "The representation type for the delayed photon data"
  )
  .def_property_readonly(

    "NG",
    [] ( const Component& self ) { return self.NG(); },
    "The number of discrete photons"
  )
  .def_property_readonly(

    "number_discrete_photons",
    &Component::numberDiscretePhotons,
    "The number of discrete photons"
  )
  .def_property_readonly(

    "photons",
    [] ( const Component& self ) -> DiscretePhotonMultiplicityRange
       { return self.photons(); },
    "The discrete photon data"
  )
  .def(

    python::init< const Component& >(),
    python::arg( "component" ),
    "Copy the component\n\n"
    "Arguments:\n"
    "    self         the component\n"
    "    component    the component to be copied"
  )
  .def_property_readonly(

    "NC",
    [] ( const Component& self ) { return self.NC(); },
    "The number of lines in this component"
  )
  .def(

    "to_string",
    [] ( const Component& self, int mat, int mf, int mt ) -> std::string
       { return print( self, mat, mf, mt ); },
    python::arg( "mat" ), python::arg( "mf" ), python::arg( "mt" ),
    "Return the string representation of the component\n\n"
    "Arguments:\n"
    "    self    the component\n"
    "    mat     the MAT number to be used\n"
    "    mf      the MF number to be used\n"
    "    mt      the MT number to be used"
  );

  // no standard definitions - read constructor needs number of tables
}

} // namespace mt460
} // namespace mf1
