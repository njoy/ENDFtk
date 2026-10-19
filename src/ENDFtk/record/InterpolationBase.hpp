#ifndef NJOY_ENDFTK_RECORD_INTERPOLATIONBASE
#define NJOY_ENDFTK_RECORD_INTERPOLATIONBASE

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/disco/Integer.hpp"
#include "tools/disco/ENDF.hpp"
#include "tools/disco/Column.hpp"
#include "tools/disco/Record.hpp"
#include "ENDFtk/record/Base.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Real.hpp"
#include "ENDFtk/record/TailVerifying.hpp"
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  class InterpolationBase {

    /* type aliases */

    using Base = record::Base< record::Real, record::Real,
                               record::Integer< 11 >, record::Integer< 11 >,
                               record::Integer< 11 >, record::Integer< 11 > >;

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    /* fields */

    Base metadata;

    std::vector< long > boundaryIndices;
    std::vector< long > interpolationSchemeIndices;

    /* auxiliary methods */

    static void
    verifyN2( long n2, long index ) {
      if ( n2 != index ) {
        InconsistentN2 exception( n2, index);
        throw exception;
      }
    }

    template< typename Iterator >
    static void
    verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ){
      tail( MAT, MF, MT, it, end, lineNumber );
    }

    static void
    verifyVectorSizes( const std::vector< long >& boundaryIndices,
                       const std::vector< long >& interpolationSchemeIndices ) {
      const bool mismatchedRegionVectorLengths =
        ( boundaryIndices.size() != interpolationSchemeIndices.size() );

      if ( mismatchedRegionVectorLengths ) {
        Log::error( "Mismatched region pair vector lengths" );
        Log::info( "Boundary indices vector length: {}",
                   boundaryIndices.size() );
        Log::info( "Interpolation scheme vector length: {}",
                   interpolationSchemeIndices.size() );
        throw std::exception();
      }
    }

    static void
    verifyBoundaryIndicesAreSorted( const std::vector< long >& boundaryIndices ){
      auto boundaryIndexIterator = 
        std::is_sorted_until( boundaryIndices.begin(), boundaryIndices.end() );

      const bool boundariesAreSorted =
        ( boundaryIndexIterator == boundaryIndices.end() );

      if ( not boundariesAreSorted ){
        Log::error( "Interpolation boundary indices are not sorted" );
        const auto position = boundaryIndexIterator - boundaryIndices.begin();
        Log::info( "Boundary index [{}]: {}",
                   (position - 1), boundaryIndexIterator[-1] );
        Log::info( "Boundary index [{}]: {}", position, boundaryIndexIterator[0] );
        throw std::exception();
      }
    }

    template< typename Iterator >
    static std::tuple< std::vector< long >, std::vector< long > >
    readRangeDescriptions
    ( long nRanges, Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ){
      try{
        std::tuple< std::vector< long >, std::vector< long > > result;
        result = record::Zipper::unzip< record::Integer<11>, record::Integer<11> >
                 ( nRanges, it, end, lineNumber, MAT, MF, MT );
        auto& boundaryIndices = std::get< 0 >( result );
        verifyBoundaryIndicesAreSorted( boundaryIndices );
        return result;
      } catch( std::exception& e ){
        Log::info( "Error encountered reading range descriptions" );
        throw e;
      }
    }

    template< typename Iterator >
    static Base
    readMetadata( Iterator& it, const Iterator& end, long& lineNumber,
                  int MAT, int MF, int MT ){
      Base metadata( it, end );
      verifyTail( it, end, lineNumber, MAT, MF, MT );
      if ( std::get<4>( metadata.fields ) < 1 ){
        Log::error( "Illegal NR value encountered" );
        Log::info( "NR (or number of regions) must be greater than or equal to 1" );
        Log::info( "NR value: {}", std::get<4>( metadata.fields ) );
        throw std::exception();
      }
      if ( std::get<5>( metadata.fields ) < 0 ){
        IllegalN2 exception( std::get<5>( metadata.fields ) );
        throw exception;
      }
      return metadata;
    }

    /* constructor */

    InterpolationBase
    ( Base&& metadata,
      std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
      InterpolationBase( std::get<0>( metadata.fields ),
                         std::get<1>( metadata.fields ),
                         std::get<2>( metadata.fields ),
                         std::get<3>( metadata.fields ),
                         std::move( std::get<0>( regions ) ),
                         std::move( std::get<1>( regions ) ) ) {
      verifyN2( std::get<5>( metadata.fields ), this->boundaryIndices.back() );
    }

    template< typename Iterator >
    InterpolationBase
    ( Base&& metadata,
      Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) :
      InterpolationBase( std::move( metadata ),
                         readRangeDescriptions( std::get<4>( metadata.fields ),
                                                  it, end, lineNumber,
                                                  MAT, MF, MT ) ) {}

  protected:

    /* custom exception objects */

    struct IllegalN2 {
      long n2;
      IllegalN2( long value ) : n2( value ) {}
    };

    struct InconsistentN2 {
      long n2, index;
      InconsistentN2( long value, long index ) : n2( value ), index( index ) {}
    };

  public:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    InterpolationBase() :
      metadata( 0., 0., 0, 0, 0, 0 ),
      boundaryIndices(),
      interpolationSchemeIndices() {}
    #endif

    InterpolationBase
    ( double C1, double C2, long L1, long L2,
      std::vector< long >&& boundaryIndices,
      std::vector< long >&& interpolationSchemeIndices ) :
      metadata( C1, C2, L1, L2, boundaryIndices.size(), boundaryIndices.back() ),
      boundaryIndices( std::move(boundaryIndices) ),
      interpolationSchemeIndices( std::move(interpolationSchemeIndices) ) {
      verifyVectorSizes( this->boundaryIndices, this->interpolationSchemeIndices );
      verifyBoundaryIndicesAreSorted( this->boundaryIndices );
    }

    InterpolationBase
    ( double C1, double C2, long L1, long L2,
      std::tuple< std::vector< long >, std::vector< long > >&& regions ) :
      InterpolationBase( C1, C2, L1, L2,
                         std::move( std::get<0>(regions) ),
                         std::move( std::get<1>(regions) ) ) {}

    template< typename Iterator >
    InterpolationBase
    ( Iterator& it, const Iterator& end, long& lineNumber,
     int MAT, int MF, int MT ) :
     InterpolationBase( readMetadata( it, end, lineNumber, MAT, MF, MT ),
                        it, end, lineNumber, MAT, MF, MT ) {}

  #define DEFINE_GETTER( name, index )                                    \
    Base::ImmutableReturnType< index >                                    \
    name () const { return std::get< index >( this->metadata.fields ); }

    DEFINE_GETTER( C1, 0 )
    DEFINE_GETTER( C2, 1 )
    DEFINE_GETTER( L1, 2 )
    DEFINE_GETTER( L2, 3 )
  #undef DEFINE_GETTER

    long NR() const { return this->boundaryIndices.size(); }

    long numberInterpolationRegions() const { return this->NR(); }

    long N2() const { return this->boundaryIndices.back(); }

    auto INT() const {

      using namespace njoy::tools;
      return std20::views::all( this->interpolationSchemeIndices );
    }

    auto interpolants() const
    // MSVC has problems deducing the return type of this function
    -> decltype( njoy::tools::std20::views::all( this->boundaryIndices ) ) {

      return this->INT();
    }

    auto NBT() const {

      using namespace njoy::tools;
      return std20::views::all( this->boundaryIndices );
    }

    auto boundaries() const
    // MSVC has problems deducing the return type of this function
    -> decltype( njoy::tools::std20::views::all( this->boundaryIndices ) ) {

      return this->NBT();
    }

    bool operator==( const InterpolationBase& rhs ) const {
      return ( this->C1() == rhs.C1() )
       and ( this->C2() == rhs.C2() )
       and ( this->L1() == rhs.L1() )
       and ( this->L2() == rhs.L2() )
       and ( this->boundaryIndices == rhs.boundaryIndices )
       and ( this->interpolationSchemeIndices == rhs.interpolationSchemeIndices );
    }

    bool operator!=( const InterpolationBase& rhs ) const {
      return not ( *this == rhs );
    }

    long NC() const { return 1 + ( this->NR() + 2 ) / 3; }

    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF, int MT ) const {

      using namespace njoy::tools;

      {
        using Format = disco::Record< disco::ENDF, disco::ENDF,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 4 >, disco::Integer< 2 >,
                                      disco::Integer< 3 >, disco::Column< 5 > >;
        Format::write( it,
                       this->C1(), this->C2(),
                       this->L1(), this->L2(),
                       this->NR(), this->N2(),
                       MAT, MF, MT );
      }
      {
        using Format = disco::Record< disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 4 >, disco::Integer< 2 >,
                                      disco::Integer< 3 >, disco::Column< 5 > >;

        auto nFullLines = this->NR() / 3;
        auto partialLineEntries = this->NR() - nFullLines * 3;

        auto boundary = this->boundaries().begin();
        auto interpolant = this->interpolants().begin();

        while ( nFullLines-- ){
          Format::write( it,
                         boundary[0], interpolant[0],
                         boundary[1], interpolant[1],
                         boundary[2], interpolant[2],
                         MAT, MF, MT );
          boundary += 3; interpolant += 3;
        }

        if ( partialLineEntries ){
          auto blankEntries = 2 * ( 3 - partialLineEntries );
          while ( partialLineEntries-- ){
            disco::Integer<11>::write( *boundary, it );
            disco::Integer<11>::write( *interpolant, it );
            ++boundary; ++interpolant;
          }

          while ( blankEntries-- ){ disco::Column< 11 >::write( it ); }

          using Format =
            disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                           disco::Integer< 3 >, disco::Column< 5 > >;

          Format::write( it, MAT, MF, MT );
        }
      }
    }
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
