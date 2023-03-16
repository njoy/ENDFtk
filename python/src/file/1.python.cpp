// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/1.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrap_1_TabulatedMultiplicity( python::module&, python::module& );
void wrap_1_PolynomialMultiplicity( python::module&, python::module& );
void wrapSection_1_451( python::module&, python::module& );
void wrapSection_1_452( python::module&, python::module& );
void wrapSection_1_455( python::module&, python::module& );
void wrapSection_1_456( python::module&, python::module& );
void wrapSection_1_458( python::module&, python::module& );
void wrapSection_1_460( python::module&, python::module& );

void wrapFile_1( python::module& module, python::module& viewmodule ) {

  // type aliases
  using MF1MT451 = njoy::ENDFtk::section::Type< 1, 451 >;
  using MF1MT452 = njoy::ENDFtk::section::Type< 1, 452 >;
  using MF1MT455 = njoy::ENDFtk::section::Type< 1, 455 >;
  using MF1MT456 = njoy::ENDFtk::section::Type< 1, 456 >;
  using MF1MT458 = njoy::ENDFtk::section::Type< 1, 458 >;
  using MF1MT460 = njoy::ENDFtk::section::Type< 1, 460 >;
  using File = njoy::ENDFtk::file::Type< 1 >;
  using Section = std::variant< MF1MT451, MF1MT452, MF1MT455,
                                MF1MT456, MF1MT458, MF1MT460 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF1",
    "MF1 - general information"
  );

  // wrap sections
  wrap_1_TabulatedMultiplicity( submodule, viewmodule );
  wrap_1_PolynomialMultiplicity( submodule, viewmodule );
  wrapSection_1_451( submodule, viewmodule );
  wrapSection_1_452( submodule, viewmodule );
  wrapSection_1_455( submodule, viewmodule );
  wrapSection_1_456( submodule, viewmodule );
  wrapSection_1_458( submodule, viewmodule );
  wrapSection_1_460( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 1 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF1 file - general information"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
