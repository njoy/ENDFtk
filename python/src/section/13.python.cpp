// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/13.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - components
void wrapTotalCrossSection( python::module&, python::module& );
void wrapPartialCrossSection( python::module&, python::module& );

void wrapSection_13( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 13 >;
  using PartialCrossSection = Section::PartialCrossSection;
  using TotalCrossSection = Section::TotalCrossSection;
  using PartialCrossSectionRange = RandomAccessAnyView< PartialCrossSection >;

  // wrap components
  wrapTotalCrossSection( module, viewmodule );
  wrapPartialCrossSection( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< PartialCrossSection >(
      viewmodule,
      "any_view< PartialCrossSection, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF13 section - photon production cross sections"
  );

  // wrap the section
  section
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( int mt, int zaid, double awr,
                       PartialCrossSection partial )
                     { return Section( mt, zaid, awr,
                                       std::move( partial ) ); } ),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "partial" ),
    "Initialise the component (only one partial given, no total required)\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    mt         the MT number for the section\n"
    "    zaid       the material ZAID value\n"
    "    awr        the atomic weight ratio\n"
    "    partial    the partial cross section"
  )
  .def(

    //! @todo pybind11 lambda move custom type workaround
    python::init( [] ( int mt, int zaid, double awr,
                       TotalCrossSection total,
                       std::vector< PartialCrossSection >&& partials )
                     { return Section( mt, zaid, awr,
                                       std::move( total ),
                                       std::move( partials ) ); } ),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "total" ), python::arg( "partials" ),
    "Initialise the component (one total and multiple partials)\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number for the section\n"
    "    zaid        the material ZAID value\n"
    "    awr         the atomic weight ratio\n"
    "    total       the total cross section\n"
    "    partials    the partial cross sections"
  )
  .def_property_readonly(

    "NK",
    &Section::NK,
    "The number of photons (discrete and continuum) with partial cross sections"
  )
  .def_property_readonly(

    "number_photons",
    &Section::numberPhotons,
    "The number of photons (discrete and continuum) with partial cross sections"
  )
  .def_property_readonly(

    "total_cross_section",
    &Section::totalCrossSection,
    "The total cross section (optional)"
  )
  .def_property_readonly(

    "photon_partial_cross_sections",
    [] ( const Section& self ) -> PartialCrossSectionRange
       { return self.photonPartialCrossSections(); },
    "The partial cross sections"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
