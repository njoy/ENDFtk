#ifndef NJOY_ENDFTK_TEXTRECORD
#define NJOY_ENDFTK_TEXTRECORD

// system includes

// other includes
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  class TextRecord : protected record::Base< record::Character< 66 > > {

    using base = record::Base< record::Character< 66 > >;
    using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  public:

    /* constructor */

    TextRecord( std::string&& text ) : base( std::move( text ) ) {}

    template< typename Iterator >
    TextRecord( Iterator& it, const Iterator& end, long& lineNumber,
                int MAT, int MF, int MT )
      try : base( it, end ) {

        tail( MAT, MF, MT, it, end, lineNumber );
      }
      catch ( std::exception& e ) {

        /* TODO error information here */
        throw e;
      }
      catch ( int fieldNo ) {

        --lineNumber;
        /* TODO error information here */
        throw std::exception();
      }

    /* methods */

    /**
     *  @brief Return the text of the record
     */
    const std::string& text() const { 

      return std::get< 0 >( this->fields ); 
    }

    /**
     *  @brief Equality operator
     *
     *  @param[in] rhs   the text record on the right
     */
    bool operator==( const TextRecord& rhs ) const {

      return static_cast< const base& >( *this ) == rhs;
    }

    /**
     *  @brief Not equal operator
     *
     *  @param[in] rhs   the text record on the right
     */
    bool operator!=( const TextRecord& rhs ) const { 

      return not( *this == rhs );
    }

    /**
     *  @brief Return the number of lines in this record
     */
    static constexpr long NC() { return 1; }

    #include "ENDFtk/TextRecord/src/print.hpp"
  };

  using TEXT = TextRecord;

} // ENDFtk namespace
} // njoy namespace

#endif
