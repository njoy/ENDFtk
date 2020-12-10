#ifndef NJOY_ENDFTK_SECTION_1_460
#define NJOY_ENDFTK_SECTION_1_460

// system includes
#include <variant>

// other includes
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF1 MT460 - delayed photon data
   *
   *  See ENDF102, section 1.6 for more information.
   */
  template<>
  class Type< 1, 460 > : protected BaseWithoutMT< Type< 1, 460 > > {

    friend BaseWithoutMT< Type< 1, 460 > >;

  public:

    #include "ENDFtk/section/1/460/DiscretePhotonMultiplicity.hpp"
    #include "ENDFtk/section/1/460/DiscretePhotons.hpp"
    #include "ENDFtk/section/1/460/ContinuousPhotons.hpp"

    using DelayedPhotonData = std::variant< // LO=1
                                            DiscretePhotons,
                                            // LO=2
                                            ContinuousPhotons >;

  protected:

    /* fields */
    DelayedPhotonData data_;

    /* auxiliary functions */
    #include "ENDFtk/section/1/460/src/readPhotonData.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/1/460/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the representation type for the delayed photon data
     */
    int LO() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.LO(); },
                                        this->data_ ); }

    /**
     *  @brief Return the representation type for the delayed photon data
     */
    int representation() const { return this->LO(); }

    /**
     *  @brief Return the number of discrete photons
     */
    int NG() const { return std::visit( [] ( const auto& v ) -> long
                                           { return v.NG(); },
                                        this->data_ ); }

    /**
     *  @brief Return the number of discrete photons
     */
    int numberDiscretePhotons() const { return this->NG(); }

    /**
     *  @brief Return the delayed photon data
     */
    const DelayedPhotonData& delayedPhotons() const { return this->data_; }

    /**
     *  @brief Return the number of lines in this MF1/MT460 section
     */
    long NC() const { return 1 + std::visit( [] ( const auto& v ) -> long
                                                { return v.NC(); },
                                             this->data_ ); }

    #include "ENDFtk/section/1/460/src/print.hpp"

    /**
     *  @brief Return the MT number of the section
     */
    static constexpr int sectionNumber(){ return 460; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
