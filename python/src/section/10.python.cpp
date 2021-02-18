// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/10.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

namespace mf10 {

  // declarations - components
  void wrapProductionCrossSection( python::module&, python::module& );
}

void wrapSection_10( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 10 >;
  using ProductionCrossSection = Section::ProductionCrossSection;
  using ProductionCrossSectionRange = RandomAccessAnyView< ProductionCrossSection >;

  // wrap components
  mf10::wrapProductionCrossSection( module, viewmodule );

  // wrap views created by this section
  // none of these are supposed to be created directly by the user
  wrapRandomAccessAnyViewOf< ProductionCrossSection >(
      viewmodule,
      "any_view< ProductionCrossSection, random_access >" );

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF10 section - cross sections for radioactive nuclide production"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, long,
                  std::vector< ProductionCrossSection >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "lis" ), python::arg( "xs" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self   the section\n"
    "    mt     the MT number\n"
    "    zaid   the ZA  identifier\n"
    "    awr    the atomic mass ratio\n"
    "    lis    the target's excited level\n"
    "    xs     the production cross sections for every state"
  )
  .def_property_readonly(

    "LIS",
    &Section::LIS,
    "The excited level number"
  )
  .def_property_readonly(

    "excited_level",
    &Section::excitedLevel,
    "The excited level number"
  )
  .def_property_readonly(

    "products",
    [] ( const Section& self ) -> ProductionCrossSectionRange
       { return self.products(); },
    "The reaction product data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
