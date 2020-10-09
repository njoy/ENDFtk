// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/2/151.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

void wrapScatteringRadius( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 2, 151 >::ScatteringRadius;
  using DoubleRange = RandomAccessAnyView< double >;
  using LongRange = RandomAccessAnyView< long >;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ScatteringRadius",
    "MF2 MT151 section - an energy dependent scattering radius function"
  );

  // wrap the section
  component
  .def(

    python::init< std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "boundaries" ), python::arg( "interpolants" ),
    python::arg( "energies" ), python::arg( "radii" ),
    "Initialise the scattering radius\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    radii           the scattering radii (in 10^-12 cm)"
  )
  .def_property_readonly(

    "NR",
    [] ( const Component& self ) { return self.NR(); },
    "The number of interpolation ranges"
  )
  .def_property_readonly(

    "NP",
    [] ( const Component& self ) { return self.NP(); },
    "The number of points"
  )
  .def_property_readonly(

    "interpolants",
    [] ( const Component& self ) -> LongRange
       { return self.interpolants(); },
    "The interpolation type for each range"
  )
  .def_property_readonly(

    "boundaries",
    [] ( const Component& self ) -> LongRange
       { return self.boundaries(); },
    "The interpolation boundaries"
  )
  .def_property_readonly(

    "E",
    [] ( const Component& self ) -> DoubleRange
       { return self.E(); },
    "The energy values"
  )
  .def_property_readonly(

    "energies",
    [] ( const Component& self ) -> DoubleRange
       { return self.energies(); },
    "The energy values"
  )
  .def_property_readonly(

    "AP",
    [] ( const Component& self ) -> DoubleRange
       { return self.AP(); },
    "The scatterin radius values"
  )
  .def_property_readonly(

    "radii",
    [] ( const Component& self ) -> DoubleRange
       { return self.radii(); },
    "The scatterin radius values"
  );

  // add standard section definitions
  addStandardComponentDefinitions< Component >( component );
}
