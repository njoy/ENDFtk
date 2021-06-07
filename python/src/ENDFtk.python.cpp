// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <complex>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations - records
void wrapDirectoryRecord( python::module&, python::module& );
void wrapTapeIdentification( python::module&, python::module& );

// declarations - files
void wrapFile_1( python::module&, python::module& );
void wrapFile_2( python::module&, python::module& );
void wrapFile_3( python::module&, python::module& );
void wrapFile_4( python::module&, python::module& );
void wrapFile_5( python::module&, python::module& );
void wrapFile_6( python::module&, python::module& );
void wrapFile_7( python::module&, python::module& );
void wrapFile_8( python::module&, python::module& );
void wrapFile_9( python::module&, python::module& );
void wrapFile_10( python::module&, python::module& );
void wrapFile_12( python::module&, python::module& );
void wrapFile_13( python::module&, python::module& );

// material and tape
void wrapMaterial( python::module&, python::module& );

// declarations - tree
void wrapTreeSection( python::module&, python::module& );
void wrapTreeFile( python::module&, python::module& );
void wrapTreeMaterial( python::module&, python::module& );
void wrapTreeTape( python::module&, python::module& );

/**
 *  @brief ENDFtk python bindings
 *
 *  The name given here (ENDFtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ENDFtk, module ) {

  // create the views submodule
  python::module viewmodule = module.def_submodule(

    "sequence",
    "sequence - ENDF sequences (internal use only)"
  );

  // wrap some basic recurring views
  // none of these are supposed to be created directly by the user
  wrapBasicRandomAccessAnyViewOf< double >(
      viewmodule,
      "any_view< double, random_access >" );
  wrapBasicRandomAccessAnyViewOf< long >(
      viewmodule,
      "any_view< long, random_access >" );
  wrapBasicRandomAccessAnyViewOf< int >(
      viewmodule,
      "any_view< int, random_access >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< double > >(
      viewmodule,
      "any_view< any_view< double, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< BasicRandomAccessAnyView< BasicRandomAccessAnyView< double > > >(
      viewmodule,
      "any_view< any_view< any_view< double, random_access >, random_access >, random_access >" );
  wrapBasicRandomAccessAnyViewOf< std::complex< double > >(
      viewmodule,
      "any_view< std::complex< double , random_access >" );

  // wrap records
  wrapDirectoryRecord( module, viewmodule );
  wrapTapeIdentification( module, viewmodule );

  // wrap files
  wrapFile_1( module, viewmodule );
  wrapFile_2( module, viewmodule );
  wrapFile_3( module, viewmodule );
  wrapFile_4( module, viewmodule );
  wrapFile_5( module, viewmodule );
  wrapFile_6( module, viewmodule );
  wrapFile_7( module, viewmodule );
  wrapFile_8( module, viewmodule );
  wrapFile_9( module, viewmodule );
  wrapFile_10( module, viewmodule );
  wrapFile_12( module, viewmodule );
  wrapFile_13( module, viewmodule );

  // wrap material and tape
  wrapMaterial( module, viewmodule );

  // create the submodule
  python::module submodule = module.def_submodule(

    "tree",
    "tree - ENDF tree components"
  );

  // wrap tree
  wrapTreeSection( submodule, viewmodule );
  wrapTreeFile( submodule, viewmodule );
  wrapTreeMaterial( submodule, viewmodule );
  wrapTreeTape( submodule, viewmodule );
}
