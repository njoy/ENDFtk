#ifndef NJOY_ENDFTK_LISTRECORD
#define NJOY_ENDFTK_LISTRECORD

// system includes

// other includes
#include "Log.hpp"
#include "range/v3/view/all.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  class ListRecord {
  protected:
    using Base = record::Base< record::Real, record::Real,
                               record::Integer< 11 >, record::Integer< 11 >,
                               record::Integer< 11 >, record::Integer< 11 > >;

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    Base metadata;
    std::vector< double > data;

    template< typename Iterator >
    static void
    verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ){
      tail( MAT, MF, MT, it, end, lineNumber );
    }

  #include "ENDFtk/ListRecord/src/readMetadata.hpp"

  public:

    /* type aliases */
    using DoubleRange =
    decltype( ranges::view::all( std::declval< const std::vector< double > >() ) );

    ListRecord( double C1, double C2, long L1, long L2, long N2,
                std::vector< double >&& list ) :
      metadata( C1, C2, L1, L2, list.size(), N2 ), data( std::move(list) ){}

    template< typename Iterator >
    ListRecord( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT )
      try: metadata( readMetadata( it, end, lineNumber, MAT, MF, MT ) ),
           data( record::Sequence::read< record::Real >
                  ( std::get<4>( this->metadata.fields ),
                    it, end, lineNumber, MAT, MF, MT ) ){
      } catch ( std::exception& e ){
        Log::info( "Error encountered while parsing List record" );
        throw e;
      } catch ( int nPosition ){
        Log::info( "Error in position {}" );
        throw std::exception();
      }

  #define DEFINE_GETTER( name, index )                                    \
    Base::MutableReturnType< index >                                      \
    name (){ return std::get< index >( this->metadata.fields ); }         \
                                                                          \
    Base::ImmutableReturnType< index >                                    \
    name () const { return std::get< index >( this->metadata.fields ); }

    DEFINE_GETTER( C1, 0 )
    DEFINE_GETTER( C2, 1 )
    DEFINE_GETTER( L1, 2 )
    DEFINE_GETTER( L2, 3 )
    DEFINE_GETTER( N2, 5 )

  #undef DEFINE_GETTER

    long NPL() const { return this->data.size(); }

    DoubleRange list() const { return ranges::view::all( this->data ); }

    DoubleRange B() const { return this->list(); }

    bool operator==( const ListRecord& rhs ) const {
      return ( this->C1() == rhs.C1() )
        and ( this->C2() == rhs.C2() )
        and ( this->L1() == rhs.L1() )
        and ( this->L2() == rhs.L2() )
        and ( this->N2() == rhs.N2() )
        and ( this->data  == rhs.data );
    }

    bool operator!= ( const ListRecord& rhs ) const {
      return not ( *this == rhs );
    }

    long NC() const { return 1 + ( this->NPL() + 5 ) / 6; }

    #include "ENDFtk/ListRecord/src/print.hpp"
  };

  using LIST = ListRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
