#ifndef NJOY_ENDFTK_SECTION_7_2
#define NJOY_ENDFTK_SECTION_7_2

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 7, 2 > :
    protected BaseWithoutMT< Type< 7, 2 > > {

    friend BaseWithoutMT< Type< 7, 2 > >;

  public:

    #include "ENDFtk/section/7/2/CoherentElastic.hpp"
    #include "ENDFtk/section/7/2/IncoherentElastic.hpp"
    #include "ENDFtk/section/7/2/MixedElastic.hpp"

    /** @typedef ScatteringLaw
     *  @brief The elastic scattering law of MF7/MT2
     *
     *  This scattering law class is set up as a variant because coherent and
     *  incoherent representations never occur together for a material.
     */
    using ScatteringLaw = std::variant< // LTHR=1
                                        CoherentElastic,
                                        // LTHR=2
                                        IncoherentElastic,
                                        // LTHR=3
                                        MixedElastic >;

  private:

    /* fields */

    ScatteringLaw law_;

    /* auxiliary functions */

    template< typename Iterator >
    static ScatteringLaw
    readScatteringLaw( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       int LTHR ) {

      switch ( LTHR ) {
        case 1: return CoherentElastic( begin, end, lineNumber, MAT, MF, MT );
        case 2: return IncoherentElastic( begin, end, lineNumber, MAT, MF, MT );
        case 3: return MixedElastic( begin, end, lineNumber, MAT, MF, MT );
        default : {
          Log::error( "Encountered illegal LTHR value" );
          Log::info( "LTHR is either 1 (coherent), 2 (incoherent) or 3 (mixed)" );
          Log::info( "LTHR value: {}", LTHR );
          Log::info( "Line number: {}", lineNumber );
          throw std::exception();
        }
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
     *  @param[in] zaid   the material ZAID value
     *  @param[in] awr    the atomic weight ratio
     *  @param[in] law    the thermal scattering law
     */
    Type( int zaid, double awr, ScatteringLaw&& law ) :
      BaseWithoutMT( zaid, awr ), law_( std::move( law ) ) {}

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
      try : BaseWithoutMT( head.ZA(), head.AWR() ),
            law_( readScatteringLaw( begin, end, lineNumber, MAT, 7, 2,
                                     head.L1() ) ) {
        readSEND(begin, end, lineNumber, MAT, 7 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section 2 of File 7 of Material {}",
                   MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the LTHR flag (coherent or incoherent elastic scattering)
     */
    int LTHR() const { return std::visit( [] ( const auto& v )
                                             { return v.LTHR(); },
                                             this->law_ ); }

    /**
     *  @brief Return the LTHR flag (coherent or incoherent elastic scattering)
     */
    int elasticScatteringType() const { return this->LTHR(); }

    /**
     *  @brief Return the thermal scattering law (either coherent or incoherent)
     */
    const ScatteringLaw& scatteringLaw() const { return this->law_; }

    /** 
     *  @brief Return the number of lines in this MF7/MT2 section
     */
    long NC() const {
      long NC = 1
              + std::visit( [&] ( const auto& v ) { return v.NC(); }, this->law_ );
      return NC;
    };

    /** 
     *  @brief Print the MF7/MT2 section (includes SEND record)
     *
     *  @tparam OutputIterator   an output iterator
     *
     *  @param[in] it            the current position in the output
     *  @param[in] MAT           the MAT number
     *  @param[in] MF            the MF number
     */
    template< typename OutputIterator >
    void print( OutputIterator& it, int MAT, int MF ) const {
      int MT = 2;
      ControlRecord( this->ZA(), this->AWR(), this->LTHR(), 0, 
                     0, 0 ).print( it, MAT, MF, MT );
      std::visit( [&] ( const auto& v ) -> void
                      { v.print( it, MAT, MF, MT ); },
                  this->law_ );
      SEND( MAT, MF ).print( it );
    } 

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 2; }

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
