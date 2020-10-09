#ifndef NJOY_ENDFTK_DIRECTORYRECORD
#define NJOY_ENDFTK_DIRECTORYRECORD

// system includes

// other includes
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief Directory record
   *
   *  The directory record is only used in MF1 MT451 and contains information
   *  for a single section available in the material.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class DirectoryRecord : protected record::Base< record::Integer< 33 >,
                                                  record::Integer< 11 >,
                                                  record::Integer< 11 >,
                                                  record::Integer< 11 > > {

    /* type aliases */
    using base =
      record::Base< record::Integer< 33 >, record::Integer< 11 >,
                    record::Integer< 11 >, record::Integer< 11 > >;
    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  public:

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] mf    the mf number
     *  @param[in] mt    the mt number
     *  @param[in] nc    the number of lines for this section
     *  @param[in] mod   the modification number
     */
    DirectoryRecord( long mf, long mt, long nc, long mod ) :
      base( mf, mt, nc, mod ){}

#ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    DirectoryRecord() : DirectoryRecord( 0, 0, 0, 0 ) {}
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
    DirectoryRecord( Iterator& it, const Iterator& end, long& lineNumber,
                     int MAT, int MF, int MT )

      try : base( it, end ) {

        tail( MAT, MF, MT, it, end, lineNumber );
      }
      catch ( std::exception& e ) {

        throw e;
      }
      catch ( int fieldNo ) {

        --lineNumber;
        throw std::exception();
      }

  #define DEFINE_GETTER( name, index )                            \
    MutableReturnType< index >                                    \
    name (){ return std::get< index >( this->fields ); }          \
                                                                  \
    ImmutableReturnType< index >                                  \
    name () const { return std::get< index >( this->fields ); }

    DEFINE_GETTER( MF, 0 )
    DEFINE_GETTER( MT, 1 )
    DEFINE_GETTER( NC, 2 )
    DEFINE_GETTER( MOD, 3 )

  #undef DEFINE_GETTER

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the directory record on the right
     */
    bool operator==( const DirectoryRecord& rhs ) const {

      return static_cast< const base& >( *this ) == rhs;
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the directory record on the right
     */
    bool operator!=( const DirectoryRecord& rhs ) const {

      return not( *this == rhs );
    }

    #include "ENDFtk/DirectoryRecord/src/print.hpp"
  };

  using DIR = DirectoryRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
