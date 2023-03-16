// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/2.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_2_151( python::module&, python::module& );
void wrapSection_2_152( python::module&, python::module& );

void wrapFile_2( python::module& module, python::module& viewmodule ) {

  // type aliases
  using MF2MT151 = njoy::ENDFtk::section::Type< 2, 151 >;
  using MF2MT152 = njoy::ENDFtk::section::Type< 2, 152 >;
  using File = njoy::ENDFtk::file::Type< 2 >;
  using Section = std::variant< MF2MT151, MF2MT152 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF2",
    "MF2 - resonance parameters"
  );

  // wrap sections
  wrapSection_2_151( submodule, viewmodule );
  wrapSection_2_152( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 2 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF2 file - resonance parameters"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
