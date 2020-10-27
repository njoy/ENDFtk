#ifndef NJOY_ENDFTK_PYTHON_VIEWS
#define NJOY_ENDFTK_PYTHON_VIEWS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "range/v3/view/any_view.hpp"
#include "range/v3/distance.hpp"
#include "range/v3/index.hpp"
#include "range/v3/at.hpp"
#include "range/v3/utility/iterator.hpp"
#include "range/v3/to_container.hpp"

namespace python = pybind11;

/**
 *  @brief Type aliases for basic any views
 *
 *  The Element template represents the type of the any_view element.
 */
template < typename Element >
using BasicInputAnyView = ranges::any_view< Element, ranges::category::input >;
template < typename Element >
using BasicForwardAnyView = ranges::any_view< Element, ranges::category::forward >;
template < typename Element >
using BasicBiDirectionalAnyView = ranges::any_view< Element, ranges::category::bidirectional >;
template < typename Element >
using BasicRandomAccessAnyView = ranges::any_view< Element, ranges::category::random_access >;

/**
 *  @brief Type aliases for any views using a reference wrapper to a const
 *         Element
 *
 *  The resulting any_view contains std::reference_wrapper< const Element >
 *  instead of just element to fix an issue with any_views. Views already
 *  containing reference wrappers (e.g. variants of reference wrappers) should
 *  continue to use the Basic... versions of the any views.
 */
template < typename Element >
using RefWrapper = std::reference_wrapper< const Element >;
template < typename Element >
using InputAnyView = BasicInputAnyView< RefWrapper< Element > >;
template < typename Element >
using ForwardAnyView = BasicForwardAnyView< RefWrapper< Element > >;
template < typename Element >
using BiDirectionalAnyView = BasicBiDirectionalAnyView< RefWrapper< Element > >;
template < typename Element >
using RandomAccessAnyView = BasicRandomAccessAnyView< RefWrapper< Element > >;

/**
 *  @brief Some recurring basic views
 */
using DoubleRange = BasicRandomAccessAnyView< double >;
using LongRange = BasicRandomAccessAnyView< long >;
using IntRange = BasicRandomAccessAnyView< int >;
using DoubleRange2D = BasicRandomAccessAnyView< DoubleRange >;
using ComplexRange = BasicRandomAccessAnyView< std::complex< double > >;

/**
 *  @brief Wrap a BasicBiDirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element, typename CopyElement = Element >
void wrapBasicBiDirectionalAnyViewOf( python::module& module, const std::string& name ) {

  python::class_< BasicBiDirectionalAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BasicBiDirectionalAnyView< Element >& view )
           { return ranges::distance( view ); } )
  .def( "__iter__",
        [] ( BasicBiDirectionalAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        ranges::iterator_t< BasicBiDirectionalAnyView< Element > >,
                        ranges::sentinel_t< BasicBiDirectionalAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
  	    python::keep_alive< 0, 1 >() )
  .def( "to_list",
        [] ( BasicBiDirectionalAnyView< Element >& view )
           -> std::vector< Element >
           { return view; } )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< CopyElement >
           { return view; } );
}

/**
 *  @brief Wrap a BasicRandomAccessAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element, typename CopyElement = Element >
void wrapBasicRandomAccessAnyViewOf( python::module& module, const std::string& name ) {

  auto index = [] ( auto i, auto length ) {

      if ( i < 0 ) {

          i += length;
      }
      if ( i < 0 || i >= length ) {

          throw python::index_error();
      }
      return i;
  };

  python::class_< BasicRandomAccessAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return ranges::distance( view ); } )
  .def( "__getitem__",
        [index] ( BasicRandomAccessAnyView< Element >& view, int i ) {

          return ranges::index( view, index( i, ranges::distance( view ) ) );
        },
   	    python::return_value_policy::reference_internal )
  .def( "__getitem__",
        [] ( BasicRandomAccessAnyView< Element >& view,
             const python::slice& slice ) {

          python::size_t start, stop, step, length;
          if ( !slice.compute( ranges::distance( view ),
                               &start, &stop, &step, &length ) ) {

            throw python::error_already_set();
          }
          std::vector< Element > list;
          for ( unsigned int i = 0; i < length; ++i ) {

             list.emplace_back( ranges::index( view, start ) );
             start += step;
          }
          return list;
        },
   	    python::return_value_policy::reference_internal )
  .def( "__iter__",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        ranges::iterator_t< BasicRandomAccessAnyView< Element > >,
                        ranges::sentinel_t< BasicRandomAccessAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
  	    python::keep_alive< 0, 1 >() )
  .def( "to_list",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< Element >
           { return view; } )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< CopyElement >
           { return view; } );
}

/**
 *  @brief Wrap a BiDirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapBiDirectionalAnyViewOf( python::module& module, const std::string& name ) {

  wrapBasicBiDirectionalAnyViewOf< RefWrapper< Element >, Element >( module, name );
}

/**
 *  @brief Wrap a RandomAccessAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapRandomAccessAnyViewOf( python::module& module, const std::string& name ) {

  wrapBasicRandomAccessAnyViewOf< RefWrapper< Element >, Element >( module, name );
}

#endif
