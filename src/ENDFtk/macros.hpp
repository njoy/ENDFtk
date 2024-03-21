#ifndef NJOY_ENDFTK_PYBIND11_MACROS
#define NJOY_ENDFTK_PYBIND11_MACROS

// include files
#ifdef PYBIND11
#include <pybind11/detail/common.h>
#endif

// define PYTHON_EXPORT macro but only when PYBIND11 is defined
#if !defined(PYTHON_EXPORT)
#  ifdef PYBIND11
#    define ENDFTK_PYTHON_EXPORT PYBIND11_EXPORT
#  else
#    define ENDFTK_PYTHON_EXPORT
#  endif
#endif

#endif
