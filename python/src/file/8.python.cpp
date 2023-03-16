// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/8.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrap_8_FissionYieldData( python::module&, python::module& );
void wrapSection_8_454( python::module&, python::module& );
void wrapSection_8_457( python::module&, python::module& );
void wrapSection_8_459( python::module&, python::module& );

void wrapFile_8( python::module& module, python::module& viewmodule ) {

  // type aliases
  using MF8MT454 = njoy::ENDFtk::section::Type< 8, 454 >;
  using MF8MT457 = njoy::ENDFtk::section::Type< 8, 457 >;
  using MF8MT459 = njoy::ENDFtk::section::Type< 8, 459 >;
  using File = njoy::ENDFtk::file::Type< 8 >;
  using Section = std::variant< MF8MT454, MF8MT457, MF8MT459 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF8",
    "MF8 - radioactive decay and fission product yield data"
  );

  // wrap sections
  wrap_8_FissionYieldData( submodule, viewmodule );
  wrapSection_8_454( submodule, viewmodule );
  wrapSection_8_457( submodule, viewmodule );
  wrapSection_8_459( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 8 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF8 file - radioactive decay and fission product yield data"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
