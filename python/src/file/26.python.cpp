// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/26.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_26( python::module&, python::module& );

void wrapFile_26( python::module& module, python::module& viewmodule ) {

  // type aliases
  using Section = njoy::ENDFtk::section::Type< 26 >;
  using File = njoy::ENDFtk::file::Type< 26 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF26",
    "MF26 - secondary distributions for photo- and electro-atomic interactions"
  );

  // wrap sections
  wrapSection_26( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 26 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF26 file - secondary distributions for photo- and electro-atomic interactions"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
