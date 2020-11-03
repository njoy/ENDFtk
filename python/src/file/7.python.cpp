// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/7.hpp"
#include "definitions.hpp"
#include "views.hpp"
#include "boost/hana.hpp"

// namespace aliases
namespace python = pybind11;

namespace hana = boost::hana;
inline namespace literals { using namespace hana::literals; }

// declarations - sections
void wrapSection_7_2( python::module& );
void wrapSection_7_4( python::module& );

void wrapFile_7( python::module& module ) {

  // type aliases
  using File = njoy::ENDFtk::file::Type< 7 >;
  using MF7MT2 = njoy::ENDFtk::section::Type< 7, 2 >;
  using MF7MT4 = njoy::ENDFtk::section::Type< 7, 4 >;

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF7",
    "MF2 - thermal neutron scattering law data"
  );

  // wrap sections
  wrapSection_7_2( submodule );
  wrapSection_7_4( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF7 file - thermal neutron scattering law data"
  );

  file
  .def(

    "section",
    [] ( const File& self, int mt ) -> std::variant< MF7MT2, MF7MT4 > {

      switch ( mt ) {

        case 2 : return self.section( 2_c );
        case 4 : return self.section( 4_c );
        default: throw std::runtime_error(
                      "Requested section number (" + std::to_string( mt ) +
                      ") does not correspond to a stored section" );
      }
    },
    python::arg( "mt" ),
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  )
  .def(

    "MT",
    [] ( const File& self, int mt ) -> std::variant< MF7MT2, MF7MT4 > {

      switch ( mt ) {

        case 2 : return self.section( 2_c );
        case 4 : return self.section( 4_c );
        default: throw std::runtime_error(
                      "Requested section number (" + std::to_string( mt ) +
                      ") does not correspond to a stored section" );
      }
    },
    "Return the section with the requested MT number\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    mt      the MT number of the section to be returned",
    python::return_value_policy::reference_internal
  );

  // add standard file definitions
  addStandardFileDefinitions< File >( file );
}
