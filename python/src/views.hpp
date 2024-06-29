#ifndef NJOY_ENDFTK_PYTHON_VIEWS
#define NJOY_ENDFTK_PYTHON_VIEWS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include "range/v3/view/any_view.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/range/operations.hpp"

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
using BasicBidirectionalAnyView = ranges::any_view< Element, ranges::category::bidirectional >;
template < typename Element >
using BasicRandomAccessAnyView = ranges::any_view< Element, ranges::category::random_access >;

/**
 *  @brief Type aliases for any views using a reference wrapper to a const
 *         Element
 *
 *  The resulting any_view contains std::reference_wrapper< const Element >
 *  instead of just Element to fix an issue with any_views. Views already
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
using BidirectionalAnyView = BasicBidirectionalAnyView< RefWrapper< Element > >;
template < typename Element >
using RandomAccessAnyView = BasicRandomAccessAnyView< RefWrapper< Element > >;

/**
 *  @brief Some recurring basic views
 */
using IntList = BasicBidirectionalAnyView< int >;
using DoubleRange = BasicRandomAccessAnyView< double >;
using LongRange = BasicRandomAccessAnyView< long >;
using IntRange = BasicRandomAccessAnyView< int >;
using DoubleRange2D = BasicRandomAccessAnyView< DoubleRange >;
using DoubleRange3D = BasicRandomAccessAnyView< DoubleRange2D >;
using ComplexRange = BasicRandomAccessAnyView< std::complex< double > >;

/**
 *  @brief Wrap a BasicBidirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element, typename CopyElement = Element >
void wrapBasicBidirectionalAnyViewOf( python::module& module, const std::string& name ) {

  python::class_< BasicBidirectionalAnyView< Element > >( module, name.c_str() )
  .def( "__len__",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return ranges::distance( view ); },
        "Return the length of the sequence" )
  .def( "__iter__",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        ranges::iterator_t< BasicBidirectionalAnyView< Element > >,
                        ranges::sentinel_t< BasicBidirectionalAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
        "Return an iterator for the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "front",
        [] ( BasicBidirectionalAnyView< Element >& view )
           { return ranges::front( view ); },
        "Return the front element of the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "to_list",
        [] ( BasicBidirectionalAnyView< Element >& view )
           -> std::vector< Element >
           { return ranges::to< std::vector< Element > >( view ); },
        "Convert the sequence to a list (this is a deep copy for primitive\n"
        "types (like integer and floats) and a shallow copy for custom types" )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< CopyElement >
           { return ranges::to< std::vector< CopyElement > >( view ); },
        "Copy the sequence to a list (this is a deep copy for both primitive\n"
        "types (like integer and floats) and custom types" );
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
           { return ranges::distance( view ); },
        "Return the length of the sequence" )
  .def( "__getitem__",
        [index] ( BasicRandomAccessAnyView< Element >& view, int i ) {

          return ranges::index( view, index( i, ranges::distance( view ) ) );
        },
        "Return the value in the sequence at the given index or throw an\n"
        "exception when the index is out of range",
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
        "Return a list corresponding to the sliced sequence or throw an\n"
        "exception when the slice is invalid. The resulting list is a deep\n"
        "copy for primitive types (like integer and floats) and a shallow\n"
        "copy for custom types",
        python::return_value_policy::reference_internal )
  .def( "__iter__",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return python::make_iterator<
                        python::return_value_policy::reference_internal,
                        ranges::iterator_t< BasicRandomAccessAnyView< Element > >,
                        ranges::sentinel_t< BasicRandomAccessAnyView< Element > >,
                        Element >( view.begin(), view.end() ); },
        "Return an iterator for the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "front",
        [] ( BasicRandomAccessAnyView< Element >& view )
           { return ranges::front( view ); },
        "Return the front element of the sequence",
        python::keep_alive< 0, 1 >() )
  .def( "to_list",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< Element >
           { return ranges::to< std::vector< Element > >( view ); },
        "Convert the sequence to a list (this is a deep copy for primitive\n"
        "types (like integer and floats) and a shallow copy for custom types" )
  .def( "copy",
      	[] ( BasicRandomAccessAnyView< Element >& view )
           -> std::vector< CopyElement >
           { return ranges::to< std::vector< CopyElement > >( view ); },
        "Copy the sequence to a list (this is a deep copy for both primitive\n"
        "types (like integer and floats) and custom types" );
}

/**
 *  @brief Wrap a BidirectionalAnyView templated on the Element type
 *
 *  @param[in,out] module   the python module
 *  @param[in,out] name     the unique type name
 */
template < typename Element >
void wrapBidirectionalAnyViewOf( python::module& module, const std::string& name ) {

  wrapBasicBidirectionalAnyViewOf< RefWrapper< Element >, Element >( module, name );
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
