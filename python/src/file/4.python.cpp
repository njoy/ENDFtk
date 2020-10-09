// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/4.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_4( python::module& );

void wrapFile_4( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using File = njoy::ENDFtk::file::Type< 4 >;
  using SectionRange = BiDirectionalAnyView< Section >;

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBiDirectionalAnyViewOf< Section >(
      module,
      "any_view< section::Type< 4 >, bidirectional >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF4",
    "MF4 - angular distributions of secondary particles"
  );

  // wrap sections
  wrapSection_4( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF4 file - angular distributions of secondary particles"
  );

  // wrap the file
  file
  .def(

    python::init< std::vector< Section >&& >(),
    python::arg( "sections" ),
    "Initialise the file\n\n"
    "Arguments:\n"
    "    self       the file\n"
    "    sections   the sections to be put into the file"
  )
  .def(

    "section",
    ( Section& ( File::* )( int ) ) &File::section,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    ( Section& ( File::* )( int ) ) &File::MT,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def_property_readonly(

    "sections",
    [] ( const File& self ) -> SectionRange
       { return self.sections(); },
    "The sections defined in the file"
  );

  // add standard section definitions
  addStandardFileDefinitions< File >( file );
}
