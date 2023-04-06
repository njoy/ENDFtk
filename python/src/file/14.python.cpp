// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/14.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_14( python::module&, python::module& );

void wrapFile_14( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 14 >;
  using File = njoy::ENDFtk::file::Type< 14 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF14",
    "MF14 - angular distributions of photons"
  );

  // wrap sections
  wrapSection_14( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 14 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF14 file - angular distributions of secondary photons"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
