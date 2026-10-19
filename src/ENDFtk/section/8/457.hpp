#ifndef NJOY_ENDFTK_SECTION_8_457
#define NJOY_ENDFTK_SECTION_8_457

// system includes
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class ENDFTK_PYTHON_EXPORT Type< 8, 457 > :
    protected BaseWithoutMT< Type< 8, 457 > > {

    friend BaseWithoutMT< Type< 8, 457 > >;

  public:

    #include "ENDFtk/section/8/457/AverageDecayEnergies.hpp"
    #include "ENDFtk/section/8/457/DecayMode.hpp"
    #include "ENDFtk/section/8/457/DecayModes.hpp"
    #include "ENDFtk/section/8/457/ContinuousSpectrum.hpp"
    #include "ENDFtk/section/8/457/DiscreteSpectrum.hpp"
    #include "ENDFtk/section/8/457/DecaySpectrum.hpp"

  private:

    /* fields */

    unsigned int lis_;
    unsigned int liso_;
    bool nst_;

    AverageDecayEnergies energies_;
    DecayModes modes_;
    std::vector< DecaySpectrum > spectra_;

    /* auxiliary functions */

    /* constructor */

    template< typename Iterator >
    Type( double za, double awr, int lis, int liso, int NSP,
          AverageDecayEnergies&& energies,
          DecayModes&& modes,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT ) :
      Type( za, awr, lis, liso,
            std::move( energies ),
            std::move( modes ),
            readSequence< DecaySpectrum >( begin, end, lineNumber,
                                           MAT, 8, 457, NSP ) ) {}

    template< typename Iterator >
    Type( double za, double awr, int lis, int liso, int NSP,
          AverageDecayEnergies&& energies,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT ) :
      Type( za, awr, lis, liso, NSP,
            std::move( energies ),
            DecayModes( begin, end, lineNumber, MAT, 8, 457 ),
            begin, end, lineNumber, MAT ) {}

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
     *  @brief Constructor for stable nuclides only
     *
     *  @param[in] zaid       the material ZAID value
     *  @param[in] awr        the atomic weight ratio
     *  @param[in] lis        the excited level number
     *  @param[in] liso       the isomeric state number
     *  @param[in] spin       the nuclide spin
     *  @param[in] parity     the nuclide parity
     */
    Type( int zaid, double awr, int lis, int liso, double spin, double parity ) :
      BaseWithoutMT( zaid, awr ),
      lis_( lis ), liso_( liso ), nst_( true ),
      energies_(), modes_(spin, parity), spectra_() {}

    /**
     *  @brief Constructor
     *
     *  @param[in] zaid       the material ZAID value
     *  @param[in] awr        the atomic weight ratio
     *  @param[in] lis        the excited level number
     *  @param[in] liso       the isomeric state number
     *  @param[in] energies   the average decay energies
     *  @param[in] modes      the decay modes
     *  @param[in] spectra    the decay spectra
     */
    Type( int zaid, double awr, int lis, int liso,
          AverageDecayEnergies&& energies,
          DecayModes&& modes,
          std::vector< DecaySpectrum >&& spectra ) :
      BaseWithoutMT( zaid, awr ),
      liso_( liso ), nst_( modes.NDK() == 0 ),
      energies_( std::move( energies ) ),
      modes_( std::move( modes ) ),
      spectra_( std::move( spectra ) ) {

        // initialisation of lis_ is moved here to fix a gcc-12 optimisation issue on Mac arm64
        this->lis_ = lis;
      }

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
      try : Type( head.ZA(), head.AWR(), head.L1(), head.L2(), head.N2(),
                  AverageDecayEnergies( begin, end, lineNumber, MAT, 8, 457 ),
                  begin, end, lineNumber, MAT ) {
        readSEND(begin, end, lineNumber, MAT, 8 );
      } catch ( std::exception& e ) {
        Log::info( "Trouble while reading section 457 of File 8 of Material {}",
                   MAT );
        throw e;
      }

    /* get methods */

    /**
     *  @brief Return the excited state number
     */
    unsigned int LIS() const { return this->lis_; }

    /**
     *  @brief Return the excited state number
     */
    unsigned int excitedState() const { return this->LIS(); }

    /**
     *  @brief Return the isomeric state number
     */
    unsigned int LISO() const { return this->liso_; }

    /**
     *  @brief Return the isomeric state number
     */
    unsigned int isomericState() const { return this->LISO(); }

    /**
     *  @brief Return the stability flag
     */
    bool NST() const { return this->nst_; }

    /**
     *  @brief Return the stability flag
     */
    bool isStable() const { return this->NST(); }

    /**
     *  @brief Return the number of decay spectra
     */
    unsigned int NSP() const { return this->spectra_.size(); }

    /**
     *  @brief Return the number of decay spectra
     */
    unsigned int numberDecaySpectra() const { return this->NSP(); }

    /**
     *  @brief Return the half life and its uncertainty
     */
    auto T() const { return this->energies_.halfLife(); }

    /**
     *  @brief Return the half life and its uncertainty
     */
    auto halfLife() const { return this->T(); }

    /**
     *  @brief Return the target spin
     */
    auto SPI() const { return this->modes_.spin(); }

    /**
     *  @brief Return the target spin
     */
    auto spin() const { return this->SPI(); }

    /**
     *  @brief Return the target parity
     */
    auto PAR() const { return this->modes_.parity(); }

    /**
     *  @brief Return the target parity
     */
    auto parity() const { return this->PAR(); }

    /**
     *  @brief Return the half life and decay energy information
     */
    const AverageDecayEnergies& averageDecayEnergies() const {

      return this->energies_;
    }

    /**
     *  @brief Return the spin, parity and decay mode information
     */
    const DecayModes& decayModes() const { return this->modes_; }

    /**
     *  @brief Return the particle spectra
     */
    auto decaySpectra() const {

      using namespace njoy::tools;
      return std20::views::all( this->spectra_ );
    }

    /** 
     *  @brief Return the number of lines in this MF7/MT2 section
     */
    long NC() const {
      long NC = 1;
      NC += this->energies_.NC();
      NC += this->modes_.NC();
      for ( const auto& entry : this->spectra_ ) { NC += entry.NC(); }
      return NC;
    };

    /** 
     *  @brief Print the MF8/MT457 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), this->lis_, this->liso_,
                     this->nst_, this->NSP() ).print( it, MAT, MF, MT );
      this->energies_.print( it, MAT, MF, MT );
      this->modes_.print( it, MAT, MF, MT );
      for ( const auto& entry : this->spectra_ ) { entry.print( it, MAT, MF, MT ); }
      SEND( MAT, MF ).print( it );
    } 

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 457; }

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
