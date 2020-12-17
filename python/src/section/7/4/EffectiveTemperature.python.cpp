// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/7/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf7 {

void wrapEffectiveTemperature( python::module& module, python::module& ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 7, 4 >::EffectiveTemperature;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "EffectiveTemperature",
    "MF7 MT4 section - effective temperatures for the short collision-time\n"
    "                  approximation"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&,
                  std::vector< long >&&,
                  std::vector< double >&&,
                  std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "tmod" ), python::arg( "teff" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    tmoderator      the moderator temperature values\n"
    "    teffective      the effective temperature values"
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

    "TMOD",
    [] ( const Component& self ) -> DoubleRange
       { return self.TMOD(); },
    "The moderator temperature values"
  )
  .def_property_readonly(

    "moderator_temperatures",
    [] ( const Component& self ) -> DoubleRange
       { return self.moderatorTemperatures(); },
    "The moderator temperature values"
  )
  .def_property_readonly(

    "TEFF",
    [] ( const Component& self ) -> DoubleRange
       { return self.TEFF(); },
    "The effective temperature values"
  )
  .def_property_readonly(

    "effective_temperatures",
    [] ( const Component& self ) -> DoubleRange
       { return self.effectiveTemperatures(); },
    "The effective temperature values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf7
