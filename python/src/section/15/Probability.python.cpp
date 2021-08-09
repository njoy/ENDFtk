// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/15.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf15 {

void wrapProbability( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 15 >;
  using Component = Section::Probability;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "Probability",
    "MF15 section - probability for a given partial distribution"
  );

  // wrap the section
  component
  .def(

    python::init( [] ( std::vector< long >&& boundaries,
                       std::vector< long >&& interpolants,
                       std::vector< double >&& energies,
                       std::vector< double >&& probabilities )
                     { return Component( 1, std::move( boundaries ),
                                         std::move( interpolants ),
                                         std::move( energies ),
                                         std::move( probabilities ) ); } ),
    python::arg( "boundaries" ), python::arg( "interpolants" ), 
    python::arg( "energies" ), python::arg( "probabilities" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self             the component\n"
    "    boundaries       the interpolation range boundaries\n"
    "    interpolants     the interpolation types for each range\n"
    "    energies         the energy values\n"
    "    probabilities    the probability values"
  )
  .def_property_readonly(

    "LF",
    [] ( const Component& self ) { return self.LF(); },
    "The distribution type (the LF flag)"
  )
  .def_property_readonly(

    "LAW",
    &Component::LAW,
    "The distribution type (the LF flag)"
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

    "P",
    [] ( const Component& self ) -> DoubleRange
       { return self.P(); },
    "The probability values"
  )
  .def_property_readonly(

    "probabilities",
    [] ( const Component& self ) -> DoubleRange
       { return self.probabilities(); },
    "The probability values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf15
