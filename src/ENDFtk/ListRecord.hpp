#ifndef NJOY_ENDFTK_LISTRECORD
#define NJOY_ENDFTK_LISTRECORD

// system includes

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief ENDF LIST record
   *
   *  The list record is a multi-line ENDF record containing 2 doubles
   *  and 4 integers on the first line, followed by a list of values on the
   *  following lines.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class ListRecord {

    using Base = record::Base< record::Real, record::Real,
                               record::Integer< 11 >, record::Integer< 11 >,
                               record::Integer< 11 >, record::Integer< 11 > >;

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

    Base metadata;
    std::vector< double > data;

    /* auxiliary functions */

    template< typename Iterator >
    static void
    verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT ){
      tail( MAT, MF, MT, it, end, lineNumber );
    }

    template< typename Iterator >
    static Base
    readMetadata
    ( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ){
      try{
        Base metadata( it, end );
        verifyTail( it, end, lineNumber, MAT, MF, MT );
        if ( std::get<4>( metadata.fields ) < 0 ){
          Log::error( "Illegal NPL value encountered" );
          Log::info( "NPL must be greater than or equal to 0" );
          Log::info( "NPL value: ", std::get<4>( metadata.fields ) );
          throw std::runtime_error( "List Record NPL value" );
        }
        return metadata;
      } catch ( std::exception& e ){
        Log::info( "Error while reading metadata" );
        throw e;
      }
    }

  public:

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] C1     the double in column 1 on line 1
     *  @param[in] C2     the double in column 2 on line 1
     *  @param[in] L1     the integer in column 3 on line 1
     *  @param[in] L2     the integer in column 4 on line 1
     *  @param[in] N2     the integer in column 6 on line 1
     *  @param[in] list   the list of values
     */
    ListRecord( double C1, double C2, long L1, long L2, long N2,
                std::vector< double >&& list ) :
      metadata( C1, C2, L1, L2, list.size(), N2 ), data( std::move(list) ){}

//! @todo pybind11 variant needs default constructor workaround
#ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    ListRecord() : ListRecord( 0., 0., 0, 0, 0, {} ) {}
#endif

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

    /* methods */

  #define DEFINE_GETTER( name, index )                                    \
    Base::ImmutableReturnType< index >                                    \
    name () const { return std::get< index >( this->metadata.fields ); }

    DEFINE_GETTER( C1, 0 )
    DEFINE_GETTER( C2, 1 )
    DEFINE_GETTER( L1, 2 )
    DEFINE_GETTER( L2, 3 )
    DEFINE_GETTER( N2, 5 )

  #undef DEFINE_GETTER

    /**
     *  @brief Return the number of values in the list
     */
    long NPL() const { return this->data.size(); }

    /**
     *  @brief Return the number of values in the list
     */
    long numberValues() const { return this->NPL(); }

    /**
     *  @brief Return the list of values
     */
    auto list() const {

      using namespace njoy::tools;
      return std20::views::all( this->data );
    }

    /**
     *  @brief Return the list of values
     */
    auto B() const { return this->list(); }

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the list record on the right
     */
    bool operator==( const ListRecord& rhs ) const {

      return ( this->C1() == rhs.C1() )
        and ( this->C2() == rhs.C2() )
        and ( this->L1() == rhs.L1() )
        and ( this->L2() == rhs.L2() )
        and ( this->N2() == rhs.N2() )
        and ( this->data  == rhs.data );
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the list record on the right
     */
    bool operator!= ( const ListRecord& rhs ) const {

      return not ( *this == rhs );
    }

    /**
     *  @brief Return the number of lines in this record
     */
    long NC() const { return 1 + ( this->NPL() + 5 ) / 6; }

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
      {
        using Format = disco::Record< disco::ENDF, disco::ENDF,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 11 >, disco::Integer< 11 >,
                                      disco::Integer< 4 >, disco::Integer< 2 >,
                                      disco::Integer< 3 >, disco::Column<5> >;
        Format::write( it,
                       this->C1(), this->C2(),
                       this->L1(), this->L2(),
                       this->NPL(), this->N2(),
                       MAT, MF, MT );
      }{
        using Format = disco::Record< disco::ENDF, disco::ENDF,
                                      disco::ENDF, disco::ENDF,
                                      disco::ENDF, disco::ENDF,
                                      disco::Integer< 4 >, disco::Integer< 2 >,
                                      disco::Integer< 3 >, disco::Column<5> >;

        auto nFullLines = this->NPL() / 6;
        auto partialLineEntries = this->NPL() - nFullLines * 6;

        auto entry = this->list().begin();

        for ( ; nFullLines-- != 0; entry += 6 ){
          Format::write( it,
                         entry[0], entry[1], entry[2],
                         entry[3], entry[4], entry[5],
                         MAT, MF, MT );
        }

        if ( partialLineEntries ){
          do {
            disco::ENDF::write( *entry, it );
          } while( ++entry != this->list().end() );

          auto blankEntries = 6 - partialLineEntries;

          while ( blankEntries-- ){ disco::Column< 11 >::write( it ); }

          using Format =
            disco::Record< disco::Integer< 4 >, disco::Integer< 2 >,
                           disco::Integer< 3 >, disco::Column< 5 > >;

          Format::write( it, MAT, MF, MT );
        }
      }
    }

  };

  using LIST = ListRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
