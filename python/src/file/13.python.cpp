// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/13.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_13( python::module& );

void wrapFile_13( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 13 >;
  using File = njoy::ENDFtk::file::Type< 13 >;
  using SectionRange = BiDirectionalAnyView< Section >;

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBiDirectionalAnyViewOf< Section >(
      module,
      "any_view< section::Type< 13 >, bidirectional >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF13",
    "MF13 - photon production cross sections"
  );

  // wrap sections
  wrapSection_13( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF13 file - photon production cross sections"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
