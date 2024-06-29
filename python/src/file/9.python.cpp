// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/9.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_9( python::module&, python::module& );

void wrapFile_9( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 9 >;
  using File = njoy::ENDFtk::file::Type< 9 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF9",
    "MF9 - multiplicities for radioactive nuclide production"
  );

  // wrap sections
  wrapSection_9( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 9 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF9 file - multiplicities for radioactive nuclide production"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
