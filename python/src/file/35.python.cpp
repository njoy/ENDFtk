// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/35.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_35( python::module&, python::module& );

void wrapFile_35( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 35 >;
  using File = njoy::ENDFtk::file::Type< 35 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF35",
    "MF35 - covariances for energy distributions"
  );

  // wrap sections
  wrapSection_35( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 35 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF35 file - covariances for angular distributions"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
