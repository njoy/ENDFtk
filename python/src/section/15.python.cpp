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

  // declarations - components
  void wrapOutgoingEnergyDistribution( python::module&, python::module& );
  void wrapTabulatedSpectrum( python::module&, python::module& );
  void wrapProbability( python::module&, python::module& );
  void wrapPartialDistribution( python::module&, python::module& );
}

void wrapSection_15( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 15 >;
  using PartialDistribution = Section::PartialDistribution;
  using PartialDistributionRange = RandomAccessAnyView< PartialDistribution >;

  // wrap components
  mf15::wrapOutgoingEnergyDistribution( module, viewmodule );
  mf15::wrapTabulatedSpectrum( module, viewmodule );
  mf15::wrapProbability( module, viewmodule );
  mf15::wrapPartialDistribution( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< PartialDistribution >(
      module,
      "any_view< MF15::PartialDistribution, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF15 section - continuous photon energy spectra"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, std::vector< PartialDistribution >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "partials" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the ZA  identifier\n"
    "    awr         the atomic mass ratio\n"
    "    partials    the partial distributions (at least 1)"
  )
  .def_property_readonly(

    "NK",
    &Section::NK,
    "The number of subsections with partial distributions"
  )
  .def_property_readonly(

    "number_partial_distributions",
    &Section::numberPartialDistributions,
    "The number of subsections with partial distributions"
  )
  .def_property_readonly(

    "partial_distributions",
    [] ( const Section& self ) -> PartialDistributionRange
       { return self.partialDistributions(); },
    "The partial distributions defined in this section"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
