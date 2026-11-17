#ifndef NJOY_ENDFTK_SECTION_7_451
#define NJOY_ENDFTK_SECTION_7_451

// system includes
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 7, 451 > :
    protected BaseWithoutMT< Type< 7, 451 > > {

    friend BaseWithoutMT< Type< 7, 451 > >;

  public:

    #include "ENDFtk/section/7/451/ElementInformation.hpp"

  private:

    /* fields */

    std::vector< ElementInformation > elements_;

    /* auxiliary functions */

    static void
    verifySize( unsigned int NA ) {

      if ( NA == 0 ) {

        Log::error( "Encountered illegal NA value" );
        Log::info( "NA must be greater than or equal to 1" );
        Log::info( "NA value: {}", NA );
        throw std::exception();
      }
    }

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] zaid       the ZA  identifier
     *  @param[in] awr        the atomic mass ratio
     *  @param[in] elements   the elements (at least 1)
     */
    Type( int zaid, double awr, std::vector< ElementInformation >&& elements ) :
      BaseWithoutMT( zaid, awr ), elements_( std::move( elements ) ) {

      verifySize( this->NA() );
    }

    /**
     *  @brief Constructor for a single element
     *
     *  @param[in] zaid       the ZA  identifier
     *  @param[in] awr        the atomic mass ratio
     *  @param[in] element    the element information
     */
    Type( int zaid, double awr, ElementInformation&& element ) :
      Type( zaid, awr, std::vector< ElementInformation >{ std::move( element ) } ) {}

    /**
     *  @brief Constructor (from a buffer)
     *
     *  @tparam Iterator        a buffer iterator
     *
     *  @param[in] head         the head record of the section
     *  @param[in] it           the current position in the buffer
     *  @param[in] end          the end of the buffer
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    Type ( HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: Type( head.ZA(), head.AWR(),
                 readSequence< ElementInformation >( begin, end, lineNumber,
                                                     MAT, 7, head.MT(), head.L1() ) ) {

        readSEND(begin, end, lineNumber, MAT, 7 );
      }
      catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 7 of material {}",
          head.MT(), MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the number of elements
     */
    unsigned int NA() const { return this->elements_.size(); }

    /**
     *  @brief Return the number of elements
     */
    unsigned int numberElements() const { return this->NA(); }

    /**
     *  @brief Return the element data
     */
    auto elements() const {

      using namespace njoy::tools;
      return std20::views::all( this->elements_ );
    }

    /**
     *  @brief Return the number of lines in this MF7 MT451 component
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->elements_ ) {

        NC += entry.NC();
      }
      return NC;
    };

    /**
     *  @brief Print this MF7 MT451 component
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = this->MT();
      ControlRecord( this->ZA(), this->AWR(),
                     this->NA(), 0,
                     0, 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->elements_ ) {

        entry.print( it, MAT, MF, MT );
      }
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 451; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
