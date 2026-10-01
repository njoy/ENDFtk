#ifndef NJOY_ENDFTK_SECTION_32_151
#define NJOY_ENDFTK_SECTION_32_151

// system includes
#include <optional>
#include <variant>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/record.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section/ExplicitCovariance.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF32 MT151 - resonance parameters
   *
   *  See ENDF102, section 32.1 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 32, 151 > :
    protected BaseWithoutMT< Type< 32, 151 > > {

  public:

    #include "ENDFtk/section/32/151/ScatteringRadiusCovariances.hpp"

    // resolved covariance data components
    // LCOMP = 0 components
    #include "ENDFtk/section/32/151/LimitedBreitWignerLValue.hpp"
    #include "ENDFtk/section/32/151/LimitedCovarianceBase.hpp"
    #include "ENDFtk/section/32/151/LimitedSingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/LimitedMultiLevelBreitWigner.hpp"
    // LCOMP = 1 components
    #include "ENDFtk/section/32/151/ShortRangeBreitWignerReichMooreBlockBase.hpp"
    #include "ENDFtk/section/32/151/ShortRangeBreitWignerBlock.hpp"
    #include "ENDFtk/section/32/151/ShortRangeReichMooreBlock.hpp"
    #include "ENDFtk/section/32/151/ShortRangeRMatrixLimitedBlock.hpp"
    #include "ENDFtk/section/32/151/ReichMooreScatteringRadiusUncertainties.hpp"
    //! @todo add LB=-1 to Covariancepairs
    //! @todo add LRF=7 scattering radius uncertainties
    using LongRangeCovarianceBlock = std::variant< CovariancePairs, SquareMatrix >;
    #include "ENDFtk/section/32/151/GeneralCovarianceBase.hpp"
    #include "ENDFtk/section/32/151/GeneralSingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/GeneralMultiLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/GeneralReichMoore.hpp"
    #include "ENDFtk/section/32/151/GeneralRMatrixLimited.hpp"
    // LCOMP = 2 components
    #include "ENDFtk/section/32/151/CompactCorrelationMatrix.hpp"
    #include "ENDFtk/section/32/151/CompactCovarianceBase.hpp"
    #include "ENDFtk/section/32/151/CompactBreitWignerUncertainties.hpp"
    #include "ENDFtk/section/32/151/CompactReichMooreUncertainties.hpp"
    #include "ENDFtk/section/32/151/CompactRMatrixLimitedUncertainties.hpp"
    #include "ENDFtk/section/32/151/CompactSingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/CompactMultiLevelBreitWigner.hpp"
    #include "ENDFtk/section/32/151/CompactReichMoore.hpp"
    #include "ENDFtk/section/32/151/CompactRMatrixLimited.hpp"

    // unresolved covariance components
    #include "ENDFtk/section/32/151/UnresolvedRelativeCovariances.hpp"

    #include "ENDFtk/section/32/151/ResonanceRange.hpp"
    #include "ENDFtk/section/32/151/Isotope.hpp"

  private:

    friend BaseWithoutMT< Type< 32, 151 > >;

    /* fields */

    std::vector< Isotope > isotopes_;

    /* auxiliary functions */

    static void
    verifyNIS( int NIS ) {

      if ( NIS < 1 ) {

        Log::error( "No isotopes with resonance parameters were defined" );
        Log::info( "NIS must be greater than zero" );
        throw std::exception();
      }
    }

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
     *  @param[in] zaid       the material ZAID value
     *  @param[in] awr        the atomic weight ratio
     *  @param[in] isotopes   the isotopes for the section
     */
    Type( int zaid, double awr, std::vector< Isotope >&& isotopes ) :
      BaseWithoutMT( zaid, awr ), isotopes_( std::move( isotopes ) ) {

        verifyNIS( this->NIS() );
      }

    /**
     *  @brief Constructor for a single isotope
     *
     *  @param[in] zaid     the material ZAID value
     *  @param[in] awr      the atomic weight ratio
     *  @param[in] lfw      the lfw flag for unresolved resonances
     *  @param[in] ranges   the resonance ranges defined for the isotope
     */
    Type( int zaid, double awr, bool lfw,
          std::vector< ResonanceRange >&& ranges ) :
      Type( zaid, awr,
            std::vector< Isotope >{ Isotope( zaid, 1., lfw,
                                    std::move( ranges ) ) } ) {}

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
    Type ( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try:
        Type( head.ZA(), head.AWR(),
              readSequence< Isotope >( begin, end, lineNumber,
                                       MAT, 32, 151, head.N1() ) ) {

          readSEND( begin, end, lineNumber, MAT, 32 );
      } catch( std::exception& e ){
        Log::info( "Trouble while reading section 151 of File 32 of Material {}",
                   MAT );
        throw e;
      }

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 151; }

    /**
     *  @brief Return the number NIS of isotopes
     */
    unsigned int numberIsotopes() const { return this->NIS(); }

    /**
     *  @brief Return the number NIS of isotopes
     */
    unsigned int NIS() const { return this->isotopes_.size(); }

    /**
     *  @brief Return the isotopes defined in the section
     */
    auto isotopes() const {

      using namespace njoy::tools;
      return std20::views::all( this->isotopes_ );
    }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;

    /**
     *  @brief Print the MF32/MT151 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {

      int MT = 151;
      ControlRecord( this->ZA(), this->AWR(),
                     0, 0, this->NIS(), 0 ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->isotopes() ) {

        entry.print( it, MAT, MF, MT );
      }
      SEND( MAT, MF ).print( it );
    }

    /**
     *  @brief Return the number of lines in this MF32/MT151 section
     */
    long NC() const {

      long NC = 1;
      for ( auto& entry : this->isotopes() ) { NC += entry.NC(); }
      return NC;
    }
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
