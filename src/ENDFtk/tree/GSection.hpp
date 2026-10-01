#ifndef NJOY_ENDFTK_TREE_GSECTION
#define NJOY_ENDFTK_TREE_GSECTION

// system includes

// other includes
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The GENDF tree section for multigroup data
   *
   *  This class represents a single section in a GENDF tape, it is the smallest
   *  piece available in the GENDF tree prior to parsing it.
   */
  class GSection {

    /* fields */

    int mat_;
    int mf_;
    int mt_;
    std::string content_;

    /* auxiliary function */

    // blatantly copied from the tree Section

    template< typename BufferIterator >
    static BufferIterator findEnd
    ( BufferIterator& position, const BufferIterator& end, long& lineNumber ) {

      // skip to the first SEND record
      while ( record::skip( position, end, lineNumber ).MT() != 0 ) {

        if ( position >= end ) {

          Log::error( "Encountered the end of stream before a SEND record was found" );
          throw std::exception();
        }
      }
      return position;
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  This constructor is not to be called directly by a user.
     *
     *  @param[in] MAT      the MAT number of the section
     *  @param[in] MF       the MF number of the section
     *  @param[in] MT       the MT number of the section
     *  @param[in] buffer   the buffer representing the section
     */
    GSection( int MAT, int MF, int MT, std::string&& buffer ) :
      mat_( MAT ), mf_( MF ), mt_( MT ), content_( std::move( buffer ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  This constructor is not to be called directly by a user.
     *
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the beginning of the buffer
     *  @param[in] position     the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename BufferIterator >
    GSection( const HEAD& head, BufferIterator begin,
              BufferIterator& position, const BufferIterator& end,
              long& lineNumber )
      try: GSection( head.MAT(), head.MF(), head.MT(),
                     std::string( begin, findEnd( position, end, lineNumber ) ) ) {}
      catch( std::exception& e ) {

        Log::info( "Trouble encountered while constructing a GENDF tree section" );
        Log::info( "Current position: MAT{} MF{} MT{} at line {}",
                   head.MAT(), head.MF(), head.MT(), lineNumber );
        throw e;
      }

    /* methods */

    /**
     *  @brief Parse the section
     *
     *  @param[in] lineNumber   the line number to be used in parsing
     */
    template< int MF, int... OptionalMT >
    section::GType< MF, OptionalMT... > parse( long& lineNumber ) const {

      auto position = this->content().begin();
      auto end = this->content().end();

      HeadRecord head( position, end, lineNumber );
      return { head, position, end, lineNumber, head.MAT() };
    }

    /**
     *  @brief Parse the section
     */
    template< int MF, int... OptionalMT >
    section::GType< MF, OptionalMT... > parse() const {

      long lineNumber = 1;
      return this->parse< MF, OptionalMT... >( lineNumber );
    }

    /**
     *  @brief Return MAT number of the section
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the section
     */
    int materialNumber() const { return this->MAT(); }
    /**
     *  @brief Return MF number of the section
     */
    int MF() const { return this->mf_; }

    /**
     *  @brief Return MF number of the section
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return MT number of the section
     */
    int MT() const { return this->mt_; }

    /**
     *  @brief Return MT number of the section
     */
    int sectionNumber() const { return this->MT(); }

    /**
     *  @brief Return the section's content
     */
    const std::string& content() const { return this->content_; }

    /**
     *  @brief Return the number lines in the section
     */
    unsigned int NC() const {

      // count all newline characters, subtract 1 for the SEND record
      return std::count( this->content_.begin(), this->content_.end(), '\n' ) - 1;
    }

    // blatantly copied from the tree Section

    /**
     *  @brief Clean up the section
     *
     *  This section removes the sequence numbers from the section
     */
    void clean() {

      int NC = this->NC();
      std::string content = this->content();
      auto position = content.begin();
      auto end = content.end();
      long lineNumber = 0;

      this->content_.clear();
      auto output = std::back_inserter( this->content_ );

      while ( NC-- > 0 ) {

        TextRecord text( position, end, lineNumber, this->MAT(), this->MF(), this->MT() );
        text.print( output, this->MAT(), this->MF(), this->MT() );
      }
      SEND( this->MAT(), this->MF() ).print( output );
    }
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
