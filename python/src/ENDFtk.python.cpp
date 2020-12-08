// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <complex>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - records
void wrapDirectoryRecord( python::module& );
void wrapTapeIdentification( python::module& );

// declarations - files
void wrapFile_1( python::module& );
void wrapFile_2( python::module& );
void wrapFile_3( python::module& );
void wrapFile_4( python::module& );
void wrapFile_5( python::module& );
void wrapFile_6( python::module& );
void wrapFile_7( python::module& );
void wrapFile_8( python::module& );
void wrapFile_12( python::module& );
void wrapFile_13( python::module& );

// material and tape
void wrapMaterial( python::module& );

// declarations - tree
void wrapTreeSection( python::module& );
void wrapTreeFile( python::module& );
void wrapTreeMaterial( python::module& );
void wrapTreeTape( python::module& );

/**
 *  @brief ENDFtk python bindings
 *
 *  The name given here (ENDFtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ENDFtk, module ) {

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< double >(
      module,
      "any_view< double, random_access >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      module,
      "any_view< long, random_access >" );
  wrapBasicRandomAccessAnyViewOf< int >(
      module,
      "any_view< int, random_access >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< double > >(
      module,
      "any_view< any_view< double, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< BasicRandomAccessAnyView< double > > >(
      module,
      "any_view< any_view< any_view< double, random_access >, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< std::complex< double > >(
      module,
        "any_view< std::complex< double , random_access >" );

  // wrap records
  wrapDirectoryRecord( module );
  wrapTapeIdentification( module );

  // wrap files
  wrapFile_1( module );
  wrapFile_2( module );
  wrapFile_3( module );
  wrapFile_4( module );
  wrapFile_5( module );
  wrapFile_6( module );
  wrapFile_7( module );
  wrapFile_8( module );
  wrapFile_12( module );
  wrapFile_13( module );

  // wrap material and tape
  wrapMaterial( module );

  // create the submodule
  python::module submodule = module.def_submodule(

    "tree",
    "tree - ENDF tree components"
  );

  // wrap tree
  wrapTreeSection( submodule );
  wrapTreeFile( submodule );
  wrapTreeMaterial( submodule );
  wrapTreeTape( submodule );
}
