// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/file/8.hpp"
#include "definitions.hpp"
#include "tools/views/views-python.hpp"

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

  // wrap the file
  file
  .def(

    python::init( [] ( MF8MT457 decay )
                     { return File( std::move( decay ) ); } ),
    python::arg( "decay" ),
    "Initialise the file with radioactive decay data\n\n"
    "Arguments:\n"
    "    self    the file\n"
    "    decay   the decay data (MT457)"
  )
  .def(

    python::init( [] ( MF8MT454 direct )
                     { return File( std::move( direct ) ); } ),
    python::arg( "direct" ),
    "Initialise the file with direct fission yield data\n\n"
    "Arguments:\n"
    "    self     the file\n"
    "    direct   the direct fission yield data (MT454)"
  )
  .def(

    python::init( [] ( MF8MT459 cumulative )
                     { return File( std::move( cumulative ) ); } ),
    python::arg( "cumulative" ),
    "Initialise the file with cumulative fission yield data\n\n"
    "Arguments:\n"
    "    self         the file\n"
    "    cumulative   the cumulative fission yield data (MT459)"
  )
  .def(

    python::init( [] ( MF8MT454 direct, MF8MT459 cumulative )
                     { return File( std::move( direct ),
                                    std::move( cumulative ) ); } ),
    python::arg( "direct" ), python::arg( "cumulative" ),
    "Initialise the file with direct and cumulative fission yield data\n\n"
    "Arguments:\n"
    "    self         the file\n"
    "    direct       the direct fission yield data (MT454)\n"
    "    cumulative   the cumulative fission yield data (MT459)"
  );

  // add standard file definitions
  addStandardFileDefinitions< File, Section, SectionRange >( file );
}
