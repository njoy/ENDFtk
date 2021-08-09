// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/33.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_33( python::module&, python::module& );

void wrapFile_33( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 33 >;
  using File = njoy::ENDFtk::file::Type< 33 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF33",
    "MF33 - covariances of cross sections"
  );

  // wrap sections
  wrapSection_33( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 33 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF33 file - covariances of cross sections"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
