#ifndef NJOY_ENDFTK_TABULATIONRECORD
#define NJOY_ENDFTK_TABULATIONRECORD

// system includes
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief ENDF TAB1 record
   *
   *  The tabulation record is a multi-line ENDF record containing 2 doubles
   *  and 4 integers on the first line, followed by a interpolation data and a
   *  list of x,y values on the following lines.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class TabulationRecord : protected record::InterpolationBase {

    /* fields */

    std::vector< double > xValues;
    std::vector< double > yValues;

    /* helper methods */

    static void
    verifyVectorSizes( const std::vector< double >& xValues,
                       const std::vector< double >& yValues ) {
      const bool mismatchedEvaluationVectorLengths =
        ( xValues.size() != yValues.size() );

      if ( mismatchedEvaluationVectorLengths ) {
        Log::error( "Mismatched evaluation pair vector lengths" );
        Log::info( "X-values vector length: {}", xValues.size() );
        Log::info( "Y-values vector length: {}", yValues.size() );
        throw std::exception();
      }
    }

    static void
    verifyXValuesAreSorted( const std::vector< double >& xValues ){
      auto xValuesIterator = std::is_sorted_until( xValues.begin(), xValues.end() );
      const bool xValuesAreSorted = ( xValuesIterator == xValues.end() );

      if ( not xValuesAreSorted ){
        Log::error( "X-values are not sorted" );
        const auto position = xValuesIterator - xValues.begin();
        Log::info( "X-value [{}]: {}", (position - 1), xValuesIterator[-1] );
        Log::info( "X-value [{}]: {}", position, xValuesIterator[0] );
        throw std::exception();
      }
    }

    static void
    verifyNP( unsigned int index, unsigned int NP ) {
      const bool inconsistentNP =
        ( index != NP );

      if ( inconsistentNP ) {
        Log::error( "Inconsistent NP value between interpolation table and "
                    "data table" );
        Log::info( "Last index interpolation table: {}", index );
        Log::info( "Number of points in data table: {}", NP );
        throw std::exception();
      }
    }

    template< typename Iterator >
    static std::tuple< std::vector< double >, std::vector< double > >
    readPairs
    ( long nPairs, Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT ){
      std::tuple< std::vector< double >, std::vector< double > > result;
      try{

        result = record::Zipper::unzip
                 < record::Real, record::Real >
                 ( nPairs, it, end, lineNumber, MAT, MF, MT );
        auto& xValues = std::get< 0 >( result );
        verifyXValuesAreSorted( xValues );
        return result;
      } catch ( std::exception& e ){
        Log::info( "Error while reading TAB1 ordered pairs" );
        throw e; 
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    TabulationRecord
    ( InterpolationBase&& interpolation,
      std::tuple< std::vector< double >, std::vector< double > >&& points ) :
      InterpolationBase( std::move( interpolation ) ),
      xValues( std::move( std::get<0>( points ) ) ),
      yValues( std::move( std::get<1>( points ) ) ) {}

    /**
     *  @brief Private constructor
     */
    template< typename Iterator >
    TabulationRecord
    ( InterpolationBase&& interpolation,
      Iterator& it, const Iterator& end, long& lineNumber,
      int MAT, int MF, int MT  ) :
      TabulationRecord( std::move( interpolation ),
                        readPairs( interpolation.N2(), it, end,
                                   lineNumber, MAT, MF, MT ) ) {}

  public:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
      /**
       *  @brief Default constructor - only enabled for pybind11
       */
      TabulationRecord() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] C1             the double in column 1 on line 1
     *  @param[in] C2             the double in column 2 on line 1
     *  @param[in] L1             the integer in column 3 on line 1
     *  @param[in] L2             the integer in column 4 on line 1
     *  @param[in] boundaries     the interpolation range boundaries
     *  @param[in] interpolants   the interpolation types for each range
     *  @param[in] x              the x values
     *  @param[in] y              the y values
     */
    TabulationRecord ( double C1, double C2, long L1, long L2,
                        std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< double >&& x,
                        std::vector< double >&& y )
      try : InterpolationBase( C1, C2, L1, L2, std::move( boundaries ),
                               std::move( interpolants ) ),
                               xValues( std::move( x ) ),
                               yValues( std::move( y ) ) {

        verifyXValuesAreSorted( this->xValues );
        verifyVectorSizes( this->xValues, this->yValues );
        verifyNP( this->boundaries().back(), this->xValues.size() );
      }
      catch ( std::exception& e ) {
        Log::info( "Error encountered while constructing TAB1 record" );
        throw e;
      }

    /**
     *  @brief Constructor
     *
     *  @param[in] C1         the double in column 1 on line 1
     *  @param[in] C2         the double in column 2 on line 1
     *  @param[in] L1         the integer in column 3 on line 1
     *  @param[in] L2         the integer in column 4 on line 1
     *  @param[in] regions    the interpolation regions
     *  @param[in] points     the x,y points
     */
    TabulationRecord ( double C1, double C2, long L1, long L2,
                       std::tuple< std::vector< long >,
                                   std::vector< long > >&& regions,
                       std::tuple< std::vector< double >,
                                   std::vector< double > >&& points ) :
      TabulationRecord( C1, C2, L1, L2,
                        std::move( std::get<0>(regions) ),
                        std::move( std::get<1>(regions) ),
                        std::move( std::get<0>(points) ),
                        std::move( std::get<1>(points) ) ){}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     *  @param[in] MF           the expected MF number
     *  @param[in] MT           the expected MT number
     */
    template< typename Iterator >
    TabulationRecord( Iterator& it, const Iterator& end, long& lineNumber,
                          int MAT, int MF, int MT )
      try: TabulationRecord( InterpolationBase( it, end, lineNumber, MAT, MF, MT ),
                             it, end, lineNumber, MAT, MF, MT ) {}
      catch ( IllegalN2& e ) {
        Log::error( "Illegal NP value encountered" );
        Log::info( "NP (or number of pairs) must be greater than or equal to 1" );
        Log::info( "NP value: {}", e.n2 );
        Log::info( "Error encountered while parsing TAB1 record" );
        throw std::exception();
      }
      catch ( InconsistentN2& e ) {
        Log::error( "Inconsistent value for NP" );
        Log::info( "Expected {} as the largest index but found {}", e.n2, e.index );
        Log::info( "Error encountered while parsing TAB1 record" );
        throw std::exception();
      }
      catch ( int nPosition ){
        Log::info( "Error in position {}", nPosition );
        Log::info( "Error encountered while parsing TAB1 record" );
        throw std::exception();
      }
      catch ( std::exception& e ) {
        Log::info( "Error encountered while parsing TAB1 record" );
        throw e;
      }

    /* methods */

    using InterpolationBase::C1;
    using InterpolationBase::C2;
    using InterpolationBase::L1;
    using InterpolationBase::L2;

    /**
     *  @brief Return the number of points in the table
     */
    long NP() const { return this->xValues.size(); }

    /**
     *  @brief Return the number of points in the table
     */
    long numberPoints() const { return this->NP(); }

    using InterpolationBase::NR;
    using InterpolationBase::numberInterpolationRegions;

    /**
     *  @brief Return the x values in the table
     */
    auto x() const {

      using namespace njoy::tools;
      return std20::views::all( this->xValues );
    }

    /**
     *  @brief Return the y values in the table
     */
    auto y() const {

      using namespace njoy::tools;
      return std20::views::all( this->yValues );
    }

    using InterpolationBase::INT;
    using InterpolationBase::NBT;
    using InterpolationBase::interpolants;
    using InterpolationBase::boundaries;

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the tabulation record on the right
     */
    bool operator==( const TabulationRecord& rhs ) const {

        return ( InterpolationBase::operator==( static_cast<const InterpolationBase&>( rhs ) ) )
        and ( this->xValues == rhs.xValues )
        and ( this->yValues == rhs.yValues );
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the list record on the right
     */
    bool operator!=( const TabulationRecord& rhs ) const {

      return not ( *this == rhs );
    }

    /**
     *  @brief Return the number of lines in this record
     */
    long NC() const {

      return record::InterpolationBase::NC() + ( this->NP() + 2 ) / 3;
    }

    /**
     *  @brief Print the record
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     *  @param[in] MT            the MT number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF, int MT ) const {
      record::InterpolationBase::print( it, MAT, MF, MT );

      using namespace njoy::tools;

      using Format = disco::Record< disco::ENDF, disco::ENDF,
                                    disco::ENDF, disco::ENDF,
                                    disco::ENDF, disco::ENDF,
                                    disco::Integer< 4 >, disco::Integer< 2 >,
                                    disco::Integer< 3 >, disco::Column< 5 > >;

      auto nFullLines = this->NP() / 3;
      auto partialLineEntries = this->NP() - nFullLines * 3;

      auto x = this->x().begin();
      auto y = this->y().begin();

      while ( nFullLines-- ){
        Format::write( it, x[0], y[0], x[1], y[1], x[2], y[2], MAT, MF, MT );
        x += 3; y += 3;
      }

      if ( partialLineEntries ){
        auto blankEntries = 2 * ( 3 - partialLineEntries );
        while ( partialLineEntries-- ){
          disco::ENDF::write( *x, it );
          disco::ENDF::write( *y, it );
          ++x; ++y;
        }

        while ( blankEntries-- ){ disco::Column< 11 >::write( it ); }

        using Format =
          disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                         disco::Integer< 3 >, disco::Column< 5 > >;

        Format::write( it, MAT, MF, MT );
      }
    }
  };

} // ENDFtk namespace
} // njoy namespace

#endif
