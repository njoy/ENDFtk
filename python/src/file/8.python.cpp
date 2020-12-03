// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/8.hpp"
#include "definitions.hpp"
#include "views.hpp"
#include "boost/hana.hpp"

// namespace aliases
namespace python = pybind11;

namespace hana = boost::hana;
inline namespace literals { using namespace hana::literals; }

// declarations - sections
void wrapSection_8_457( python::module& );

void wrapFile_8( python::module& module ) {

  // type aliases
  using File = njoy::ENDFtk::file::Type< 8 >;
  using MF8MT457 = njoy::ENDFtk::section::Type< 8, 457 >;

  // wrap views created by this file

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF8",
    "MF8 - radioactive decay and fission product yield data"
  );

  // wrap sections
  wrapSection_8_457( submodule );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF8 file - radioactive decay and fission product yield data"
  );

  // common lambda
  auto get_section =
  [] ( const File& self, int mt ) -> std::variant< MF8MT457 > {

    switch ( mt ) {

      case 457 : return self.section( 457_c );
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
