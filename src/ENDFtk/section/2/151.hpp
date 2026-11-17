#ifndef NJOY_ENDFTK_SECTION_2_151
#define NJOY_ENDFTK_SECTION_2_151

// system includes
#include <complex>
#include <variant>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF2 MT151 - resonance parameters
   *
   *  See ENDF102, section 2.1 for more information.
   */
  template<>
  class Type< 2, 151 > : protected BaseWithoutMT< Type< 2, 151 > > {

  public:

    #include "ENDFtk/section/2/151/BreitWignerReichMooreBase.hpp"
    #include "ENDFtk/section/2/151/BreitWignerReichMooreLValueBase.hpp"

    #include "ENDFtk/section/2/151/UnresolvedLValueBase.hpp"
    #include "ENDFtk/section/2/151/UnresolvedBaseWithoutSpin.hpp"
    #include "ENDFtk/section/2/151/UnresolvedBase.hpp"

    #include "ENDFtk/section/2/151/BreitWignerLValue.hpp"
    #include "ENDFtk/section/2/151/ReichMooreLValue.hpp"

    #include "ENDFtk/section/2/151/SpecialCase.hpp"

    #include "ENDFtk/section/2/151/SingleLevelBreitWigner.hpp"
    #include "ENDFtk/section/2/151/MultiLevelBreitWigner.hpp"
    #include "ENDFtk/section/2/151/ReichMoore.hpp"
    #include "ENDFtk/section/2/151/RMatrixLimited.hpp"

    using SLBW = SingleLevelBreitWigner;
    using MLBW = MultiLevelBreitWigner;
    using RM = ReichMoore;
    using RML = RMatrixLimited;

    #include "ENDFtk/section/2/151/UnresolvedEnergyIndependent.hpp"
    #include "ENDFtk/section/2/151/UnresolvedEnergyDependentFissionWidths.hpp"
    #include "ENDFtk/section/2/151/UnresolvedEnergyDependent.hpp"

    using CaseA = UnresolvedEnergyIndependent;
    using CaseB = UnresolvedEnergyDependentFissionWidths;
    using CaseC = UnresolvedEnergyDependent;

    #include "ENDFtk/section/2/151/ScatteringRadius.hpp"
    #include "ENDFtk/section/2/151/ResonanceRange.hpp"
    #include "ENDFtk/section/2/151/Isotope.hpp"

  private:

    friend BaseWithoutMT< Type< 2, 151 > >;

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
     *  @brief Special case constructor (only scattering radius is given)
     *
     *  @param[in] zaid   the material ZAID value
     *  @param[in] awr    the atomic weight ratio
     *  @param[in] el     the lower limit of the resonance range
     *  @param[in] eh     the upper limit of the resonance range
     *  @param[in] spin   the spin of the target nucleus
     *  @param[in] ap     the scattering radius (in units of 10^-12 cm)
     */
    Type( int zaid, double awr, double el, double eh, double spin, double ap ) :
      Type( zaid, awr,
            { { zaid, 1.0, 0,
                { { el, eh, 0, SpecialCase( spin, ap ), std::nullopt } } } } ) {}

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
                                       MAT, 2, 151, head.N1() ) ) {

          readSEND( begin, end, lineNumber, MAT, 2 );
      } catch( std::exception& e ){
        Log::info( "Trouble while reading section 151 of File 2 of Material {}",
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
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;

    /**
     *  @brief Print the MF2/MT151 section (includes SEND record)
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
     *  @brief Return the number of lines in this MF2/MT151 section
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
