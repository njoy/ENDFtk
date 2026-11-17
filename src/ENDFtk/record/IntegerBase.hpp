#ifndef NJOY_ENDFTK_RECORD_INTEGERBASE
#define NJOY_ENDFTK_RECORD_INTEGERBASE

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/record/Integer.hpp"
#include "ENDFtk/record/Zipper.hpp"

namespace njoy {
namespace ENDFtk {
namespace record {

  template < unsigned int NDIGIT, unsigned int N >
  class IntegerBase {

    /* type aliases */

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    /* fields */

    unsigned int i_;
    unsigned int j_;
    std::vector< int > k_;

    /* auxiliary methods */

    static void
    verifySize( unsigned int size ) {

      if ( size > N ) {

        Log::error( "Too many K values for INTG record with NDIGIT = {}", NDIGIT );
        Log::info( "Expected at most: {}", N );
        Log::info( "Got: {}", size );
        throw std::exception();
      }
    }

    template < typename String >
    static unsigned int verifyUnsigned( long value, const String& name ) {

      if ( value <= 0 ) {

        Log::error( "Encountered negative or zero integer for {}, "
                    "expected an unsigned integer", name );
        Log::info( "{}: {}", name, value );
      }

      return static_cast< unsigned int >( value );
    }

    template< typename Iterator >
    static std::vector< int > readIntegers( Iterator& it, const Iterator& end ) {

      std::vector< int > sequence;

      // NDIGIT != 6 : there's a space
      if ( NDIGIT != 6 ) { ++it; }

      // read N ints of length NDIGIT + 1
      for ( unsigned int i = 0; i < N; ++i ) {

        sequence.emplace_back( record::Integer< NDIGIT + 1 >::Parser::read( it, end ) );
      }

      // remove trailing zeros
      auto iter = std::find_if( sequence.rbegin(), sequence.rend(),
                                [] ( auto value ) { return value != 0; } ).base();
      sequence.erase( iter, sequence.end() );

      // NDIGIT == 2 and 5 : there's a space, NDIGIT == 3: there's three spaces
      switch ( NDIGIT ) {

        case 2 :
        case 5 : { it += 1; break; }
        case 3 : { it += 3; break; }
        default : { break; }
      }

      return sequence;
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    IntegerBase( int i, int j,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
      IntegerBase( verifyUnsigned( i, "I" ), verifyUnsigned( j, "K" ),
                   readIntegers( it, end ) ) {

        tail( MAT, MF, MT, it, end, lineNumber );
      }

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    IntegerBase( int i,
                 Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT ) :
      IntegerBase( i,
                   record::Integer< 5 >::Parser::read( it, end ),
                   it, end, lineNumber, MAT, MF, MT ) {}

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] i    the i coordinate
     *  @param[in] j    the j coordinate
     *  @param[in] k    the k values
     */
    IntegerBase( unsigned int i, unsigned int j, std::vector< int >&& k ) :
      i_( i ), j_( j ), k_( std::move( k ) ) {

        verifySize( this->k_.size() );
      }

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
    IntegerBase( Iterator& it, const Iterator& end, long& lineNumber,
                 int MAT, int MF, int MT )
      try: IntegerBase( record::Integer< 5 >::Parser::read( it, end ),
                        it, end, lineNumber, MAT, MF, MT ) {}
      catch ( int nPosition ) {

        Log::info( "Error in position {}", nPosition );
        Log::info( "Error encountered while parsing INTG record" );
        throw std::exception();
      }
      catch ( std::exception& e ) {

        Log::info( "Error encountered while parsing INTG record" );
        throw e;
      }

    unsigned int I() const { return this->i_; }

    unsigned int J() const { return this->j_; }

    auto K() const {

      using namespace njoy::tools;
      return std20::views::all( this->k_ );
    }

    constexpr long NC() { return 1; }

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

      using namespace njoy::tools;

      record::Integer< 5 >::Parser::write( this->I(), it );
      record::Integer< 5 >::Parser::write( this->J(), it );

      if ( NDIGIT != 6 ) { disco::Column< 1 >::write( it ); };

      for ( auto value : this->K() ) {

        record::Integer< NDIGIT + 1 >::Parser::write( value, it );
      }

      switch ( NDIGIT ) {

        case 2: { disco::Column< 1 >::write( it ); break; }
        case 3: { disco::Column< 3 >::write( it ); break; }
        case 5: { disco::Column< 1 >::write( it ); break; }
        default: { /* unreachable */ break; }
      }

      int blankEntries = N - this->K().size();
      while ( blankEntries-- ){ disco::Column< NDIGIT + 1 >::write( it ); }

      using Format =
        disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                       disco::Integer< 3 >, disco::Column< 5 > >;

      Format::write( it, MAT, MF, MT );
    }
  };

} // record namespace
} // ENDFtk namespace
} // njoy namespace

#endif
