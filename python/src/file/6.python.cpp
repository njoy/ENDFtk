// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/6.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_6( python::module& );

void wrapFile_6( python::module& module ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 6 >;
  using File = njoy::ENDFtk::file::Type< 6 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      module,
      "any_view< section::Type< 6 >, bidirectional >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF6",
    "MF6 - product energy-angle distributions"
  );

  // wrap sections
  wrapSection_6( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF6 file - product energy-angle distributions"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
