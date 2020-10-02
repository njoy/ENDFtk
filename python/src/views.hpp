#ifndef NJOY_ENDFTK_PYTHON_VIEWS
#define NJOY_ENDFTK_PYTHON_VIEWS

// system includes

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "range/v3/view/any_view.hpp"
#include "range/v3/distance.hpp"
#include "range/v3/index.hpp"
#include "range/v3/at.hpp"
#include "range/v3/utility/iterator.hpp"
#include "range/v3/to_container.hpp"

namespace py = pybind11;

template < typename Element >
using InputAnyView = ranges::any_view< Element, ranges::category::input >;
template < typename Element >
using ForwardAnyView = ranges::any_view< Element, ranges::category::forward >;
template < typename Element >
using BiDirectionalAnyView = ranges::any_view< Element, ranges::category::bidirectional >;
template < typename Element >
using RandomAccessAnyView = ranges::any_view< Element, ranges::category::random_access >;

/**
 *  @brief Wrap a BiDirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapBiDirectionalAnyViewOf( py::module& module, const std::string& name ) {

  py::class_< BiDirectionalAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BiDirectionalAnyView< Element >& view )
           { return ranges::distance( view ); } )
  .def( "__iter__",
        [] ( BiDirectionalAnyView< Element >& view )
           { return py::make_iterator<
                        py::return_value_policy::reference_internal,
                        ranges::iterator_t< BiDirectionalAnyView< Element > >,
                        ranges::sentinel_t< BiDirectionalAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
  	    py::keep_alive< 0, 1 >() )
  .def( "list",
        [] ( BiDirectionalAnyView< Element >& view ) -> std::vector< Element >
           { return view; } );
}

/**
 *  @brief Wrap a RandomAccessAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapRandomAccessAnyViewOf( py::module& module, const std::string& name ) {

  py::class_< RandomAccessAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( RandomAccessAnyView< Element >& view )
           { return ranges::distance( view ); } )
  .def( "__getitem__",
        [] ( RandomAccessAnyView< Element >& view, int i )
           { return ranges::index( view, i ); },
   	    py::return_value_policy::reference_internal )
  .def( "__iter__",
        [] ( RandomAccessAnyView< Element >& view )
           { return py::make_iterator<
                        py::return_value_policy::reference_internal,
                        ranges::iterator_t< RandomAccessAnyView< Element > >,
                        ranges::sentinel_t< RandomAccessAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
  	    py::keep_alive< 0, 1 >() )
  .def( "list",
      	[] ( RandomAccessAnyView< Element >& view ) -> std::vector< Element >
           { return view; } );
}

#endif
