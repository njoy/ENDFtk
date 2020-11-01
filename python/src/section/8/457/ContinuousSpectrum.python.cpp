// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/8/457.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf8 {

void wrapContinuousSpectrum( python::module& module ) {

  // type aliases
  using Component = njoy::ENDFtk::section::Type< 8, 457 >::ContinuousSpectrum;

  // wrap views created by this section

  // create the component
  python::class_< Component > component(

    module,
    "ContinuousSpectrum",
    "MF8 MT457 section - continuous decay spectrum"
  );

  // wrap the section
  component
  .def(

    python::init< double,
                  std::vector< long >&&, std::vector< long >&&,
                  std::vector< double >&&, std::vector< double >&& >(),
    python::arg( "chain" ), python::arg( "boundaries" ),
    python::arg( "interpolants" ), python::arg( "energies" ),
    python::arg( "spectrum" ),
    "Initialise the component\n\n"
    "Arguments:\n"
    "    self            the component\n"
    "    chain           the ENDF decay chain\n"
    "    boundaries      the interpolation range boundaries\n"
    "    interpolants    the interpolation types for each range\n"
    "    energies        the energy values\n"
    "    spectrum        the spectral values"
  )
  .def_property_readonly(

    "RTYP",
    &Component::RTYP,
    "The decay chain"
  )
  .def_property_readonly(

    "decay_chain",
    &Component::decayChain,
    "The decay chain"
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

    "RP",
    [] ( const Component& self ) -> DoubleRange
       { return self.RP(); },
    "The spectral values"
  )
  .def_property_readonly(

    "spectral_values",
    [] ( const Component& self ) -> DoubleRange
       { return self.spectralValues(); },
    "The spectral values"
  );

  // add standard tab1 definitions
  addStandardTableDefinitions< Component >( component );

  // add standard component definitions
  addStandardComponentDefinitions< Component >( component );
}

} // namespace mf8
