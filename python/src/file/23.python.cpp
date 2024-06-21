// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/23.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_23( python::module&, python::module& );

void wrapFile_23( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 23 >;
  using File = njoy::ENDFtk::file::Type< 23 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF23",
    "MF23 - smooth photon interaction cross sections"
  );

  // wrap sections
  wrapSection_23( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 23 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF23 file - smooth photon interaction cross sections"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
