#ifndef NJOY_ENDFTK_SECTION_33
#define NJOY_ENDFTK_SECTION_33

// system includes
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/section/ReactionBlock.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief 33 - covariances of cross sections
   *
   *  See ENDF102, section 33.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 33 > : protected Base {

    /* fields */

    int mtl_;
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
     *  @param[in] reactions     the reaction block subsections
     */
    Type( int MT, int zaid, double awr,
          std::vector< ReactionBlock >&& reactions ) :
      Base( zaid, awr, MT ), mtl_( 0 ),
      reactions_( std::move( reactions ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number of the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] awr           the atomic weight ratio
     *  @param[in] mtl           the lumped covariance index
     */
    Type( int MT, int zaid, double awr, int mtl ) :
      Base( zaid, awr, MT ), mtl_( mtl ) {}

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
        Base( head, MAT, 33 ), mtl_( head.L2() ),
        reactions_(
          readSequence< ReactionBlock >( begin, end, lineNumber,
                                      MAT, 33, head.MT(), head.N2() ) ) {
        readSEND(begin, end, lineNumber, MAT, 33 );
      } catch( std::exception& e ) {

        Log::info( "Trouble while reading section {} of File 33 of Material {}",
                   head.MT(), MAT );
        throw e;
      }

    /* methods */

    /**
     *  @brief Return the lumped covariance index
     */
    int MTL() const { return this->mtl_; }

    /**
     *  @brief Return the lumped covariance index
     */
    int lumpedCovarianceIndex() const { return this->MTL(); }

    /**
     *  @brief Return the number of subsections
     */
    int NL() const { return this->reactions_.size(); }

    /**
     *  @brief Return the number of subsections, representing reactions
     */
    int numberReactions() const { return this->NL(); }

    /**
     *  @brief Return the subsections defined in this section
     */
    auto reactions() const {

      using namespace njoy::tools;
      return std20::views::all( this->reactions_ );
    }

    /**
     *  @brief Return the number of lines in this MF33 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->reactions_ ) { NC += entry.NC(); }
      return NC;
    };

    /**
     *  @brief Print the MF33 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), 0,this->MTL(),
                     0, this->NL() ).print( it, MAT, MF, MT );
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

#endif
