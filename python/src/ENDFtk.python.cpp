// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// other includes

// namespace aliases
namespace python = pybind11;

// declarations

/**
 *  @brief ENDFtk python bindings
 *
 *  The name given here (ENDFtk) must be the same as the name
 *  set on the PROPERTIES OUTPUT_NAME in the CMakeLists.txt file.
 */
PYBIND11_MODULE( ENDFtk, module ) {

  module.def(

    "add",
    [] ( int left, int right ) { return left + right; },
    python::arg( "left" ), python::arg( "right" ),
    "Return the sum of two integers\n\n"
    "This function does not throw an exception.\n\n"
    "Arguments:\n"
    "    left    the integer on the left\n"
    "    right   the integer on the right"
  );

}
