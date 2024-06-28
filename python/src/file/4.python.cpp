// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/4.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_4( python::module&, python::module& );

void wrapFile_4( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 4 >;
  using File = njoy::ENDFtk::file::Type< 4 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF4",
    "MF4 - angular distributions of secondary particles"
  );

  // wrap sections
  wrapSection_4( submodule, viewmodule );

//  // wrap views created by this file
//  // none of these are supposed to be created directly by the user
//  wrapBidirectionalAnyViewOf< Section >(
//      viewmodule,
//      "any_view< section::Type< 4 >, bidirectional >" );
//
//  // create the file
//  python::class_< File > file(
//
//    submodule,
//    "File",
//    "MF4 file - angular distributions of secondary particles"
//  );
//
//  // add standard file definitions
//  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
