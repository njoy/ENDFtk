#ifndef NJOY_ENDFTK_CONTROLRECORD
#define NJOY_ENDFTK_CONTROLRECORD

// system includes

// other includes
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief ENDF CONT record
   *
   *  The control record is a single line record consisting of 2 doubles and
   *  4 integer values.
   *
   *  See ENDF102, section 1.1 for more information.
   */
  class ControlRecord : protected record::Base< record::Real,
                                                record::Real,
                                                record::Integer< 11 >,
                                                record::Integer< 11 >,
                                                record::Integer< 11 >,
                                                record::Integer< 11 > > {

    using base = record::Base< record::Real, record::Real,
                               record::Integer< 11 >, record::Integer< 11 >,
                               record::Integer< 11 >, record::Integer< 11 > >;

    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  public:

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] C1   the double in column 1
     *  @param[in] C2   the double in column 2
     *  @param[in] L1   the integer in column 3
     *  @param[in] L2   the integer in column 4
     *  @param[in] N1   the integer in column 5
     *  @param[in] N2   the integer in column 6
     */
    ControlRecord( double C1, double C2,
                   long L1, long L2, long N1, long N2 ) :
      base( C1, C2, L1, L2, N1, N2 ){}

#ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    ControlRecord() : ControlRecord( 0., 0., 0, 0, 0, 0 ) {}
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
    ControlRecord( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT )
      try: base( it, end ){
        tail( MAT, MF, MT, it, end, lineNumber );
      } catch ( std::exception& e ) {
        /* TODO error information here */
        throw e;
      } catch ( int fieldNo ){
        --lineNumber;
        /* TODO error information here */
        throw std::exception();
      }

    /* methods */

  #define DEFINE_GETTER( name, index )                            \
    MutableReturnType< index >                                    \
    name (){ return std::get< index >( this->fields ); }          \
                                                                  \
    ImmutableReturnType< index >                                  \
    name () const { return std::get< index >( this->fields ); }

    DEFINE_GETTER( C1, 0 )
    DEFINE_GETTER( C2, 1 )
    DEFINE_GETTER( L1, 2 )
    DEFINE_GETTER( L2, 3 )
    DEFINE_GETTER( N1, 4 )
    DEFINE_GETTER( N2, 5 )

  #undef DEFINE_GETTER

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the control record on the right
     */
    bool operator==( const ControlRecord& rhs ) const {

      return static_cast< const base& >( *this ) == rhs;
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the control record on the right
     */
    bool operator!=( const ControlRecord& rhs ) const {

      return not( *this == rhs );
    }

    /**
     *  @brief Return the number of lines in this record
     */
    long NC() const { return 1; }

    #include "ENDFtk/ControlRecord/src/print.hpp"
  };

  using CONT = ControlRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
