#ifndef NJOY_ENDFTK_TAPEIDENTIFICATION
#define NJOY_ENDFTK_TAPEIDENTIFICATION

// system includes

// other includes
#include "Log.hpp"
#include "ENDFtk/record.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief Tape identifier record
   *
   *  The tape identifier is essentially a string of text identifying the tape.
   *  It also contained additional information such as the tape number but this
   *  is no longer used.
   *
   *  See ENDF102, section 0.6.4.1 for more information.
   */
  class TapeIdentification {

    /* fields */
    record::Base< record::Character< 66 > > base;
    record::TailVerifying< record::MT, record::MF > tail;

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] text   the tape identification
     *  @param[in] tape   the tape number (defaults to 0)
     */
    TapeIdentification( std::string&& text, int tape = 0 ) :
      base( std::move(text) ), tail( tape, 0, 0 ){}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename Iterator >
    TapeIdentification( Iterator& it, const Iterator& end, long& lineNumber )
      try: base( it, end ), tail( 0, 0, it, end, lineNumber ) {}
      catch ( std::exception& e ) {

        Log::info( "Encountered trouble when reading TapeIdentification" );
        throw e;
      }
      catch ( int fieldNo ) {

        --lineNumber;
        /* TODO error information here */
        throw std::exception();
      }

    /* methods */

    /**
     *  @brief Return the tape indentification
     */
    std::string& text(){ return std::get<0>( base.fields ); }

    /**
     *  @brief Return the tape indentification
     */
    const std::string& text() const { return std::get<0>( base.fields ); }

    /**
     *  @brief Return the tape number
     */
    int& tapeNumber() { return this->tail.material(); }

    /**
     *  @brief Return the tape number
     */
    int tapeNumber() const { return this->tail.material(); }

    /**
     *  @brief Return the tape number
     */
    int& NTAPE(){ return this->tapeNumber(); }

    /**
     *  @brief Return the tape number
     */
    int NTAPE() const { return this->tapeNumber(); }

    /**
     *  @brief Return the number of lines for the record
     */
    long NC() const { return 1; }

    #include "ENDFtk/TapeIdentification/src/print.hpp"
  };

  using TPID = TapeIdentification;

} // ENDFtk namespace
} // njoy namespace

#endif
