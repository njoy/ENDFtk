// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/34.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_34( python::module&, python::module& );

void wrapFile_34( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 34 >;
  using File = njoy::ENDFtk::file::Type< 34 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF34",
    "MF34 - covariances for angular distributions"
  );

  // wrap sections
  wrapSection_34( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 34 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF34 file - covariances for angular distributions"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
