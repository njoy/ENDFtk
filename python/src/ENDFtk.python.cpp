// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes
#include "views.hpp"

// namespace aliases
namespace python = pybind11;

// declarations
void wrapDirectoryRecord( python::module& );

/**
 *  @brief ENDFtk python bindings
 *
 *  The name given here (ENDFtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ENDFtk, module ) {

  // wrap some basic views
  wrapAnyViewOf< double >( module, "any_view< double, random_access >" );
  wrapAnyViewOf< long >( module, "any_view< long, random_access >" );

  // wrap records
  wrapDirectoryRecord( module );

  // module.def(
  //
  //   "add",
  //   [] ( int left, int right ) { return left + right; },
  //   python::arg( "left" ), python::arg( "right" ),
  //   "Return the sum of two integers\n\n"
  //   "This function does not throw an exception.\n\n"
  //   "Arguments:\n"
  //   "    left    the integer on the left\n"
  //   "    right   the integer on the right"
  // );

}
