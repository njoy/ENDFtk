// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/section/28.hpp"
#include "definitions.hpp"
#include "views.hpp"

namespace mf28 {

  // declarations - components
  void wrapSubshellData( python::module&, python::module& );
}

// namespace aliases
namespace python = pybind11;

void wrapSection_28( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 28 >;
  using SubshellData = njoy::ENDFtk::section::Type< 28 >::SubshellData;
  using SubshellDataRange = RandomAccessAnyView< SubshellData >;

  // wrap components
  mf28::wrapSubshellData( module, viewmodule );

  // wrap views created by this section

  // create the section
  python::class_< Section > section(

    module,
    "Section",
    "MF28 section - atomic relaxation data"
  );

  // wrap the section
  section
  .def(

    python::init< int, double, double, std::vector< SubshellData >&& >(),
    python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ),
    python::arg( "subshells" ),
    "Initialise the section\n\n"
    "Arguments:\n"
    "    self        the section\n"
    "    mt          the MT number\n"
    "    zaid        the material ZAID value\n"
    "    awr         the atomic weight ratio\n"
    "    subshells   the subshell data"
  )
  .def_property_readonly(

    "NSS",
    &Section::NSS,
    "The number of subshells"
  )
  .def_property_readonly(

    "number_subshells",
    &Section::numberSubshells,
    "The number of subshells"
  )
  .def_property_readonly(

    "subshells",
    [] ( const Section& self ) -> SubshellDataRange
       { return self.subshells(); },
    "The subshell data"
  );

  // add standard section definitions
  addStandardSectionDefinitions< Section >( section );
}
