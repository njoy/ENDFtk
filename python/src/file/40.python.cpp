// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/40.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_40( python::module&, python::module& );

void wrapFile_40( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 40 >;
  using File = njoy::ENDFtk::file::Type< 40 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF40",
    "MF40 - covariances for radionuclide production"
  );

  // wrap sections
  wrapSection_40( submodule, viewmodule );

//  // wrap views created by this file
//  // none of these are supposed to be created directly by the user
//  wrapBidirectionalAnyViewOf< Section >(
//      viewmodule,
//      "any_view< section::Type< 40 >, bidirectional >" );
//
//  // create the file
//  python::class_< File > file(
//
//    submodule,
//    "File",
//    "MF40 file - covariances for radionuclide production"
//  );
//
//  // add standard file definitions
//  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
