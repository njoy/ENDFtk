// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/32.hpp"
#include "definitions.hpp"
#include "views.hpp"
#include "boost/hana.hpp"

// namespace aliases
namespace python = pybind11;

namespace hana = boost::hana;
inline namespace literals { using namespace hana::literals; }

// declarations - sections
void wrapSection_32_151( python::module&, python::module& );

void wrapFile_32( python::module& module, python::module& viewmodule ) {

  // type aliases
//  using File = njoy::ENDFtk::file::Type< 3 >;
  using MF32MT151 = std::reference_wrapper< const njoy::ENDFtk::section::Type< 32, 151 > >;

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF32",
    "MF32 - resonance parameter covariances"
  );

  // wrap sections
  wrapSection_32_151( submodule, viewmodule );

  // create the file
//  python::class_< File > file(
//
//    submodule,
//    "File",
//    "MF2 file - resonance parameters"
//  );

  // common lambda
//  auto get_section =
//  [] ( const File& self, int mt ) -> std::variant< MF2MT151, MF2MT152 > {
//
//    switch ( mt ) {
//
//      case 151 : return self.section( 151_c );
//      case 152 : return self.section( 152_c );
//      default: throw std::runtime_error(
//                    "Requested section number (" + std::to_string( mt ) +
//                    ") does not correspond to a stored section" );
//    }
//  };

//  file
//  .def(
//
//    "section",
//    get_section,
//    python::arg( "mt" ),
//    "Return the section with the requested MT number\n\n"
//    "Arguments:\n"
//    "    self    the file\n"
//    "    mt      the MT number of the section to be returned",
//    python::return_value_policy::reference_internal
//  )
//  .def(
//
//    "MT",
//    get_section,
//    python::arg( "mt" ),
//    "Return the section with the requested MT number\n\n"
//    "Arguments:\n"
//    "    self    the file\n"
//    "    mt      the MT number of the section to be returned",
//    python::return_value_policy::reference_internal
//  );
//
//  // add standard file definitions
//  addStandardFileDefinitions< File >( file );
}
