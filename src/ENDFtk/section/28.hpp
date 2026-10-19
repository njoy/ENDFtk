#ifndef NJOY_ENDFTK_SECTION_28
#define NJOY_ENDFTK_SECTION_28

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF28 - atomic relaxation data
   *
   *  See ENDF102, section 28.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 28 > : protected Base {

  public:

    #include "ENDFtk/section/28/SubshellData.hpp"

  private:

    /* fields */

    std::vector< SubshellData > subshells_;

  public:

    /* constructor */

    //! @todo pybind11 variant needs default constructor workaround
    #ifdef PYBIND11
    /**
     *  @brief Default constructor - only enabled for pybind11
     */
    Type() = default;
    #endif

    /**
     *  @brief Constructor
     *
     *  @param[in] mt          the MT number
     *  @param[in] zaid        the ZA  identifier
     *  @param[in] awr         the atomic mass ratio
     *  @param[in] subshells   the subshell data (at least 1)
     */
    Type( int mt, int zaid, double awr,
          std::vector< SubshellData >&& subshells ) :
      Base( zaid, awr, mt ), subshells_( std::move( subshells ) ) {}

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
      try: Type( head.MT(), head.ZA(), head.AWR(),
                 readSequence< SubshellData >( begin, end, lineNumber,
                                               MAT, 28, head.MT(), head.N1() ) ) {

        readSEND(begin, end, lineNumber, MAT, 28 );
      }
      catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 28 of material {}",
          head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the number of subshells
     */
    int NSS() const { return this->subshells_.size(); }

    /**
     *  @brief Return the number of subshells
     */
    int numberSubshells() const { return this->NSS(); }

    /**
     *  @brief Return the subshell data
     */
    auto subshells() const {

      using namespace njoy::tools;
      return std20::views::all( this->subshells_ );
    }

    /**
     *  @brief Return the number of lines in this MF28 component
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->subshells_ ) {

        NC += entry.NC();
      }
      return NC;
    };

    /**
     *  @brief Print this MF28 component
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
      ControlRecord( this->ZA(), this->AWR(), 0, 0,
                     this->subshells_.size(), 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->subshells_ ) {

        entry.print( it, MAT, MF, MT );
      }
      SEND( MAT, MF ).print( it );
    }

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
