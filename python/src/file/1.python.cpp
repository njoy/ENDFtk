// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/1.hpp"
#include "definitions.hpp"
#include "views.hpp"
#include "boost/hana.hpp"

// namespace aliases
namespace python = pybind11;

namespace hana = boost::hana;
inline namespace literals { using namespace hana::literals; }

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
  using File = njoy::ENDFtk::file::Type< 1 >;
  using MF1MT451 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 451 > >;
  using MF1MT452 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 452 > >;
  using MF1MT455 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 455 > >;
  using MF1MT456 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 456 > >;
  using MF1MT458 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 458 > >;
  using MF1MT460 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 1, 460 > >;

  // wrap views created by this file

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

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF1 file - general information"
  );

  // common lambda
  auto get_section =
  [] ( const File& self, int mt ) -> std::variant< MF1MT451, MF1MT452,
                                                   MF1MT455, MF1MT456,
                                                   MF1MT458, MF1MT460 > {

    switch ( mt ) {

      case 451 : return self.section( 451_c );
      case 452 : return self.section( 452_c );
      case 455 : return self.section( 455_c );
      case 456 : return self.section( 456_c );
      case 458 : return self.section( 458_c );
      case 460 : return self.section( 460_c );
      default: throw std::runtime_error(
                    "Requested section number (" + std::to_string( mt ) +
                    ") does not correspond to a stored section" );
    }
  };

  file
  .def(

    "section",
    get_section,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    get_section,
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
