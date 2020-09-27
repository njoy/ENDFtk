#ifndef NJOY_ENDFTK_SECTION_8_457
#define NJOY_ENDFTK_SECTION_8_457

// system includes

// other includes
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  template<>
  class Type< 8, 457 > : protected BaseWithoutMT< Type< 8, 457 > > {

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

  public:

    /* constructor */
    #include "ENDFtk/section/8/457/src/ctor.hpp"

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
    auto halfLife() const { return this->energies_.halfLife(); }

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
     *  @brief Return the spectra
     */
    auto decaySpectra() const {

      return ranges::view::all( this->spectra_ );
    }

    #include "ENDFtk/section/8/457/src/NC.hpp"
    #include "ENDFtk/section/8/457/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber() { return 457; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::atomicWeightRatio;
    using BaseWithoutMT::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
