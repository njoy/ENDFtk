#ifndef NJOY_ENDFTK_TAPE
#define NJOY_ENDFTK_TAPE

// system includes
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/Material.hpp"

namespace njoy {
namespace ENDFtk {

  /**
   *  @class
   *  @brief An ENDF tape - a collection of one or more materials
   */
  class Tape {

    /* fields */

    TapeIdentification id_;
    std::vector< Material > materials_;

    /* auxialiary functions */

    /**
     *  @brief Function to read a sequence of ENDF components
     *
     *  @tparam Component        an ENDF component
     *  @tparam Iterator         an input iterator
     *
     *  This function requires the ENDF component to have a read style
     *  constructor.
     */
    template< typename Iterator >
    std::vector< Material >
    readMaterials( Iterator& begin,
                   const Iterator& end,
                   long& lineNumber ) {

      std::vector< Material > sequence;

      StructureDivision division( begin, end, lineNumber );
      while ( division.tail.MAT() != -1 ) {

        sequence.emplace_back( division, begin, end, lineNumber );
        division = StructureDivision( begin, end, lineNumber );
      }

      return sequence;
    }

    static void
    verifySize( int size ) {

      if ( size == 0 ) {

        Log::error( "No materials were defined" );
        Log::info( "There must be at least one material in a tape" );
        throw std::exception();
      }
    }

    /* constructor */

    /**
     *  @brief Private constructor
     */
    template< typename BufferIterator >
    Tape( TapeIdentification&& id,
          BufferIterator& begin, const BufferIterator& end, long& lineNumber ) :
      Tape( std::move( id ),
            readMaterials( begin, end, lineNumber ) ) {}

  public :

    /* constructors */

    /**
     *  @brief Constructor
     *
     *  @param[in] materials   the materials of the file
     */
    Tape( TapeIdentification&& id, std::vector< Material >&& materials ) :
      id_( std::move( id ) ), materials_( std::move( materials ) ) {

      verifySize( this->materials_.size() );
    }

    /**
     *  @brief Constructor
     *
     *  @param[in] string      the tape identifier string
     *  @param[in] materials   the materials of the file
     */
    Tape( std::string&& id, std::vector< Material >&& materials ) :
      Tape( TapeIdentification( std::move( id ) ), std::move( materials ) ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     */
    template< typename BufferIterator >
    Tape( BufferIterator& begin, const BufferIterator& end, long& lineNumber )
      try: Tape( TapeIdentification( begin, end, lineNumber ),
                 begin, end, lineNumber ) {}
      catch ( std::exception& e ) {

        Log::info("Encountered error while constructing Tape" );
        Log::info( "Line number: {}", lineNumber );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number of materials
     */
    auto numberMaterials() const { return this->materials_.size(); }

    /**
     *  @brief Return the materials stored in this file
     */
    auto materials() {

      using namespace njoy::tools;
      return this->materials_ | std20::views::all;
    }

    /**
     *  @brief Return the materials stored in this file
     */
    auto materials() const {

      using namespace njoy::tools;
      return this->materials_ | std20::views::all;
    }

    /**
     *  @brief Return an iterator to the start of the materials
     */
    auto begin() { return this->materials().begin(); }

    /**
     *  @brief Return an iterator to the end of the materials
     */
    auto end() { return this->materials().end(); }

    /**
     *  @brief Return an iterator to the start of the materials
     */
    auto begin() const { return this->materials().begin(); }

    /**
     *  @brief Return an iterator to the end of the materials
     */
    auto end() const { return this->materials().end(); }

    /**
     *  @brief Return all materials with the given MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    auto MAT( int mat ) const {

      using namespace njoy::tools;
      return this->materials_
                 | std20::views::filter(
                      [mat] ( const auto& material )
                            { return material.MAT() == mat; } );
    }

    /**
     *  @brief Return all materials with the given MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    auto material( int mat ) const { return this->MAT( mat ); }

    /**
     *  @brief Return whether or not the tape contains a material with the given
     *         MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    bool hasMAT( int mat ) const {

      using namespace njoy::tools;
      return std20::distance( this->material( mat ) ) > 0;
    }

    /**
     *  @brief Return whether or not the tape contains a material with the given
     *         MAT number
     *
     *  @param[in] mat    the MAT number to be verified
     */
    bool hasMaterial( int mat ) const { return this->hasMAT( mat ); }

    template< typename OutputIterator >
    void print( OutputIterator& it ) const {

      this->id_.print( it, 0, 0, 0 );
      for ( const auto& material : this->materials_ ) { material.print( it ); }
      TEND().print( it );
    }
  };

} // ENDFtk namespace
} // njoy namespace

#endif
