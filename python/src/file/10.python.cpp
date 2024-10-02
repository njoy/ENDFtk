// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/10.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_10( python::module&, python::module& );

void wrapFile_10( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 10 >;
  using File = njoy::ENDFtk::file::Type< 10 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF10",
    "MF10 - production cross sections for radioactive nuclides"
  );

  // wrap sections
  wrapSection_10( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 10 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF10 file - production cross sections for radioactive nuclides"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
