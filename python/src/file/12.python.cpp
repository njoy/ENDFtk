// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/12.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_12( python::module& );

void wrapFile_12( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 12 >;
  using File = njoy::ENDFtk::file::Type< 12 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF12",
    "MF12 - photon production multiplicities and transition probability arrays"
  );

  // wrap sections
  wrapSection_12( submodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 12 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF12 file - photon production multiplicities and transition probability\n"
    "            arrays"
  );

  // wrap the file
  addStandardUnenumeratedFileDefinitions< File, Section, SectionRange >( file );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
