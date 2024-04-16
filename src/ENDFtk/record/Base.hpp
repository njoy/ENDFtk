#ifndef NJOY_ENDFTK_RECORD_BASE
#define NJOY_ENDFTK_RECORD_BASE

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/disco/Record.hpp"
#include "ENDFtk/record/helper.hpp"
#include "ENDFtk/record/Character.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Real.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template< typename... Fields >
  struct Base {
    /* verify invariants */
    static_assert( sizeof...(Fields) > 0,
                   "A record must contain at least 1 field" );

    static_assert
    ( helper::sum< Fields::width... >() == 66,
      "The field widths do not sum to 66 as required by the ENDF format" );

    /* convenience typedefs */
    using FieldTuple = std::tuple< typename Fields::Type... >;
    using Format = njoy::tools::disco::Record< typename Fields::Parser...,
                                               njoy::tools::disco::RetainCarriage >;

    template< int Index >
    using ShouldRecurse =
      std::conditional_t< (Index != 0), std::true_type, std::false_type >;

    template< typename T >
    using ArgumentType =
      std::conditional_t< std::is_trivially_copyable< T >::value,
                          T, std::add_rvalue_reference_t< T > >;

    template< std::size_t index >
    using ElementType = std::tuple_element_t< index, FieldTuple >;

    template< std::size_t index >
    using MutableReturnType = std::add_lvalue_reference_t< ElementType< index > >;

    template< std::size_t index >
    using ImmutableReturnType =
      std::conditional_t
      < std::is_trivially_copyable< ElementType< index > >::value,
        ElementType< index >,
        std::add_lvalue_reference_t< std::add_const_t< ElementType< index > > > >;

    /* constants */
    static constexpr std::size_t nFields = sizeof...(Fields);

    /* fields */
    FieldTuple fields;

    /* helper methods */
    template< int, int... Indices, typename Iterator >
    static FieldTuple
    readFields( Iterator& it, const Iterator& end, std::false_type ){
      FieldTuple result;
      Format::read( it, end, std::get< Indices >( result )... );
      return result;
    }

    template< int Index, int... Indices, typename Iterator >
    static FieldTuple
    readFields( Iterator& it, const Iterator& end, std::true_type ){
      return readFields< Index - 1, Index, Indices... >
             ( it, end, ShouldRecurse< Index >() );
    }

    /* ctor */
    template< typename Iterator >
    Base( Iterator& it, const Iterator& end )
      try :
        fields( readFields< nFields - 1 >( it, end, std::true_type() ) )
    {
    } catch( std::exception& e ){
      Log::info( "Encountered error when reading Base of Record" );
      Log::info( "what(): {}", e.what() );
      throw e;
    }

    Base( ArgumentType< typename Fields::Type > ... types ) :
      fields( std::make_tuple< typename Fields::Type... >
              ( std::forward
                < ArgumentType< typename Fields::Type > >( types )... ) ){}

    /* helper methods */
    template< int Index = nFields >
    bool
    equality( const Base&, std::false_type ) const { return true; }

    template< int Index = nFields >
    bool
    equality( const Base& rhs, std::true_type ) const {
      constexpr auto index = nFields - Index;
      return
        ( std::get< index >( rhs.fields ) == std::get< index >( this->fields ) )
        and this->equality< Index - 1 >( rhs, ShouldRecurse< Index - 1 >() );
    }

    /* methods */
    bool
    operator==( const Base& rhs ) const {
      return this->equality( rhs, std::true_type() );
    }

    bool
    operator!=( const Base& rhs ) const {
      return not ( *this == rhs );
    }
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
