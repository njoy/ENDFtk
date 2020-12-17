// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/3.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_3( python::module& );

void wrapFile_3( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 3 >;
  using File = njoy::ENDFtk::file::Type< 3 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 3 >, bidirectional >" );

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF3",
    "MF3 - reaction cross sections"
  );

  // wrap sections
  wrapSection_3( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF3 file - reaction cross sections"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
