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

void wrapDiscretePhotonMultiplicity( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 1, 460 >::DiscretePhotonMultiplicity;

  // wrap views created by this component

  // create the component
  python::class_< Component > component(

    module,
    "DiscretePhotonMultiplicity",
    "MF1 MT460 component - tabulated time dependent multiplicity for a\n"
    "                      discrete photon"
  );

  // wrap the component
  component
  .def(

    python::init< double, int,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "energy" ), python::arg( "lph" ),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "time" ), python::arg( "multiplicities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self              the component\n"
    "    energy            the discrete photon energyt\n"
    "    lph               the index of the discrete photont\n"
    "    boundaries        the interpolation range boundariest\n"
    "    interpolants      the interpolation types for each ranget\n"
    "    time              the time valuest\n"
    "    multiplicities    the multiplicity valuest"
  )
  .def_property_readonly(

    "E",
    &Component::E,
    "The photon energy"
  )
  .def_property_readonly(

    "energy",
    &Component::energy,
    "The photon energy"
  )
  .def_property_readonly(

    "LPH",
    &Component::LPH,
    "The photon index (between 1 and NG)"
  )
  .def_property_readonly(

    "index",
    &Component::index,
    "The photon index (between 1 and NG)"
  )
  .def_property_readonly(

    "time",
    [] ( const Component& self ) -> DoubleRange
       { return self.time(); },
    "The time values"
  )
  .def_property_readonly(

    "multiplicities",
    [] ( const Component& self ) -> DoubleRange
       { return self.multiplicities(); },
    "The time dependent multiplicity values (in units of 1/s)"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mt458
} // namespace mf1
