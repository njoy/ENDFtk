#ifndef NJOY_ENDFTK_SECTION_34
#define NJOY_ENDFTK_SECTION_34

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"

// fix a MacOS issue with an NL1 macro being defined at this point
#ifdef NL1
#undef NL1
#define __REDEFINE_NL1__
#endif

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 34 - covariances for angular distributions
   *
   *  See ENDF102, section 34.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 34 > : protected Base {

  public:

    // include classes for subsections
    #include "ENDFtk/section/34/LegendreBlock.hpp"
    #include "ENDFtk/section/34/ReactionBlock.hpp"

  private:

    /* fields */

    int ltt_;
    std::vector< ReactionBlock > reactions_;

    /* auxiliary functions */

  public:

    /* constructor */

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] ltt           the covariance representation
     *  @param[in] reactions     the reaction block subsections
     */
    Type( int MT, int zaid, double awr, int ltt,
          std::vector< ReactionBlock >&& reactions ) :
      Base( zaid, awr, MT ), ltt_( ltt ),
      reactions_( std::move( reactions ) ) {}

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
    Type( HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT )
      try:
        Base( head, MAT, 34 ), ltt_( head.L2() ),
        reactions_(
          readSequence< ReactionBlock >( begin, end, lineNumber,
                                         MAT, 34, head.MT(), head.N2() ) ) {

        readSEND(begin, end, lineNumber, MAT, 34 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while reading section {} of File 34 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the representation of the covariances
     */
    int LTT() const { return this->ltt_; }

    /**
     *  @brief Return the representation of the covariances
     */
    int representation() const { return this->LTT(); }

    /**
     *  @brief Return the number of subsections
     */
    int NMT1() const { return this->reactions_.size(); }

    /**
     *  @brief Return the number of subsections, representing reactions
     */
    int numberReactions() const { return this->NMT1(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto reactions() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_ );
    }

    /**
     *  @brief Return the number of lines in this MF34 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->reactions_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF34 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), 0,this->LTT(),
                     0, this->NMT1() ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->reactions_ ) { entry.print( it, MAT, MF, MT ); }
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

// fix a MacOS issue with an NL1 macro being defined at this point
#ifdef __REDEFINE_NL1__
#define         NL1     0x00000100
#undef __REDEFINE_NL1__
#endif

#endif
