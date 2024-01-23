#ifndef NJOY_ENDFTK_SECTION_1_451
#define NJOY_ENDFTK_SECTION_1_451

// system includes

// other includes
#include "range/v3/iterator/operations.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/all.hpp"
#include "range/v3/view/concat.hpp"
#include "range/v3/view/join.hpp"
#include "range/v3/view/single.hpp"
#include "range/v3/view/split.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF1 MT451 - descriptive data and directory
   *
   *  See ENDF102, section 1.1 for more information.
   */
  template<>
  class Type< 1, 451 > : protected BaseWithoutMT< Type< 1, 451 > > {

    friend BaseWithoutMT< Type< 1, 451 > >;

    /* fields */
    int lrp_;
    int lfi_;
    int nlib_;
    int nmod_;
    std::array< ControlRecord, 3 > parameters_;
    std::vector< TextRecord > description_;
    std::vector< DirectoryRecord > index_;

    /* auxiliary functions */
    #include "ENDFtk/section/1/451/src/makeParameters.hpp"
    #include "ENDFtk/section/1/451/src/makeDescription.hpp"
    #include "ENDFtk/section/1/451/src/readParameters.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/1/451/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the resonance parameter flag
     */
    int LRP() const { return this->lrp_; }

    /**
     *  @brief Return the resonance parameter flag
     */
    int resonanceParameterFlag() const { return this->LRP(); }

    /**
     *  @brief Return the fissile flag
     */
    int LFI() const { return this->lfi_; }

    /**
     *  @brief Return the fissile flag
     */
    bool isFissile() const { return this->LFI(); }

    /**
     *  @brief Return the library type
     */
    int NLIB() const { return this->nlib_; }

    /**
     *  @brief Return the library type
     */
    int libraryType() const { return this->NLIB(); }

    /**
     *  @brief Return the modification number
     */
    int NMOD() const { return this->nmod_; }

    /**
     *  @brief Return the modification number
     */
    int modificationNumber() const { return this->NMOD(); }

    /**
     *  @brief Return the excitation energy
     */
    double ELIS() const { return std::get< 0 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the excitation energy
     */
    double excitationEnergy() const { return this->ELIS(); }

    /**
     *  @brief Return the stability flag
     */
    double STA() const { return std::get< 0 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return the stability flag
     */
    bool isStable() const { return this->STA(); }

    /**
     *  @brief Return the excited level number
     */
    int LIS() const { return std::get< 0 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the excited level number
     */
    int excitedLevel() const { return this->LIS(); }

    /**
     *  @brief Return the isomeric state number
     */
    int LISO() const { return std::get< 0 >( this->parameters_ ).L2(); }

    /**
     *  @brief Return the isomeric state number
     */
    int isomericLevel() const { return this->LISO(); }

    /**
     *  @brief Return the library format version number
     */
    int NFOR() const { return std::get< 0 >( this->parameters_ ).N2(); }

    /**
     *  @brief Return the library format version number
     */
    int libraryFormat() const { return this->NFOR(); }

    /**
     *  @brief Return the atomic weight ratio of the incident particle
     */
    double AWI() const { return std::get< 1 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the atomic weight ratio of the incident particle
     */
    double projectileAtomicMassRatio() const { return this->AWI(); }

    /**
     *  @brief Return the maximum energy
     */
    double EMAX() const { return std::get< 1 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return the maximum energy
     */
    double maximumEnergy() const { return this->EMAX(); }

    /**
     *  @brief Return the release number
     */
    int LREL() const { return std::get< 1 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the release number
     */
    int releaseNumber() const { return this->LREL(); }

    /**
     *  @brief Return the sublibrary number
     */
    int NSUB() const { return std::get< 1 >( this->parameters_ ).N1(); }

    /**
     *  @brief Return the sublibrary number
     */
    int subLibrary() const { return this->NSUB(); }

    /**
     *  @brief Return the version number
     */
    int NVER() const { return std::get< 1 >( this->parameters_ ).N2(); }

    /**
     *  @brief Return the version number
     */
    int versionNumber() const { return this->NVER(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return std::get< 2 >( this->parameters_ ).C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the reconstruction tolerance
     */
    double RTOL() const { return std::get< 2 >( this->parameters_ ).C2(); }

    /**
     *  @brief Return the reconstruction tolerance
     */
    double reconstructionTolerance() const { return this->RTOL(); }

    /**
     *  @brief Return the derived material flag
     */
    int LDRV() const { return std::get< 2 >( this->parameters_ ).L1(); }

    /**
     *  @brief Return the derived material flag
     */
    int derivedMaterial() const { return this->LDRV(); }

    /**
     *  @brief Return the number of lines of descriptive data
     */
    int NWD() const { return static_cast< int >( this->description_.size() ); }

    /**
     *  @brief Return the number of index entries
     */
    int NXC() const { return static_cast< int >( this->index_.size() ); }

    /**
     *  @brief Return the index of available files and sections
     */
    auto index() const {

      return ranges::cpp20::views::all( this->index_ );
    }

    /**
     *  @brief Return the number of lines in this MF1/MT451 section
     */
    long NC() const { return 4 + this->NWD() + this->NXC(); }

    #include "ENDFtk/section/1/451/src/description.hpp"
    #include "ENDFtk/section/1/451/src/print.hpp"

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
