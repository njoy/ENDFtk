// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/7.hpp"
#include "definitions.hpp"
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - sections
void wrapSection_7_2( python::module&, python::module& );
void wrapSection_7_4( python::module&, python::module& );
void wrapSection_7_451( python::module&, python::module& );

void wrapFile_7( python::module& module, python::module& viewmodule ) {

  // type aliases
  using MF7MT2 = njoy::ENDFtk::section::Type< 7, 2 >;
  using MF7MT4 = njoy::ENDFtk::section::Type< 7, 4 >;
  using MF7MT451 = njoy::ENDFtk::section::Type< 7, 451 >;
  using File = njoy::ENDFtk::file::Type< 7 >;
  using Section = std::variant< MF7MT2, MF7MT4, MF7MT451 >;
  using SectionRange = BidirectionalAnyView< Section >;

  // create the submodule
  python::module submodule = module.def_submodule(

    "MF7",
    "MF7 - thermal neutron scattering law data"
  );

  // wrap sections
  wrapSection_7_2( submodule, viewmodule );
  wrapSection_7_4( submodule, viewmodule );
  wrapSection_7_451( submodule, viewmodule );

  // wrap views created by this file
  // none of these are supposed to be created directly by the user
  wrapBidirectionalAnyViewOf< Section >(
      viewmodule,
      "any_view< section::Type< 7 >, bidirectional >" );

  // create the file
  python::class_< File > file(

    submodule,
    "File",
    "MF7 file - thermal neutron scattering law data"
  );

  // wrap the file
  file
  .def(

    python::init( [] ( MF7MT2 elastic )
                     { return File( std::move( elastic ) ); } ),
    python::arg( "elastic" ),
    "Initialise the file with elastic thermal scattering data\n\n"
    "Arguments:\n"
    "    self      the file\n"
    "    elastic   the elastic thermal scattering data (MT2)"
  )
  .def(

    python::init( [] ( MF7MT4 inelastic )
                     { return File( std::move( inelastic ) ); } ),
    python::arg( "inelastic" ),
    "Initialise the file with inelastic thermal scattering data\n\n"
    "Arguments:\n"
    "    self        the file\n"
    "    inelastic   the inelastic thermal scattering data (MT4)"
  )
  .def(

    python::init( [] ( MF7MT2 elastic, MF7MT4 inelastic )
                     { return File( std::move( elastic ),
                                    std::move( inelastic ) ); } ),
    python::arg( "elastic" ), python::arg( "inelastic" ),
    "Initialise the file with elastic and inelastic thermal scattering data\n\n"
    "Arguments:\n"
    "    self        the file\n"
    "    elastic     the elastic thermal scattering data (MT2)\n"
    "    inelastic   the inelastic thermal scattering data (MT4)"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
