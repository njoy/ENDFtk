// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/32.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_32_151( python::module&, python::module& );

void wrapFile_32( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 32, 151 >;
  using File = njoy::ENDFtk::file::Type< 32 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF32",
    "MF32 - resonance parameter covariances"
  );

  // wrap sections
  wrapSection_32_151( submodule, viewmodule );

//  // wrap views created by this file
//  // none of these are supposed to be created directly by the user
//  wrapBidirectionalAnyViewOf< Section >(
//      viewmodule,
//      "any_view< section::Type< 32 >, bidirectional >" );
//
//  // create the file
//  python::class_< File > file(
//
//    submodule,
//    "File",
//    "MF32 file - resonance parameter covariance data"
//  );
//
//  // wrap the file
//  file
//  .def(
//
//    python::init( [] ( Section covariances )
//                     { return File( std::move( covariances ) ); } ),
//    python::arg( "covariances" ),
//    "Initialise the file with resonance parameter covariance data\n\n"
//    "Arguments:\n"
//    "    self          the file\n"
//    "    covariances   the resonance parameter covariance data (MT151)"
//  );
//
//  // add standard file definitions
//  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
