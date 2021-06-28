#ifndef NJOY_ENDFTK_SECTION_14
#define NJOY_ENDFTK_SECTION_14

// system includes
#include <variant>

// other includes
#include "range/v3/algorithm/count_if.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF14 - angular distributions of secondary photons
   *
   *  See ENDF102, section 14.2 for more information.
   */
  template<>
  class Type< 14 > : protected Base {

  protected:

    #include "ENDFtk/section/4/AngularDistributions.hpp" // MF4 component taken over as is

  public:

    #include "ENDFtk/section/14/IsotropicDiscretePhoton.hpp"
    #include "ENDFtk/section/4/LegendreCoefficients.hpp"  // MF4 component taken over as is
    #include "ENDFtk/section/4/TabulatedDistribution.hpp" // MF4 component taken over as is
    #include "ENDFtk/section/14/LegendreDistributions.hpp"
    #include "ENDFtk/section/14/TabulatedDistributions.hpp"

    /** @typedef PhotonDistribution
     *  @brief The angular distribution of a given discrete photon
     *
     *  This distribution class is set up as a variant.
     */
    using PhotonDistribution = std::variant< IsotropicDiscretePhoton,
                                             LegendreDistributions,
                                             TabulatedDistributions >;

    /** @typedef PhotonDistribution
     *  @brief The angular distribution of a given discrete photon
     *
     *  This distribution class is set up as a variant.
     */
    using AnisotropicPhotonDistribution = std::variant< LegendreDistributions,
                                                        TabulatedDistributions >;

  private:

    /* type aliases */

    /* fields */
    std::vector< PhotonDistribution > photons_;

    /* auxiliary functions */
    #include "ENDFtk/section/14/src/readPhotons.hpp"
    #include "ENDFtk/section/14/src/makePhotonDistributions.hpp"
    #include "ENDFtk/section/14/src/makeArrays.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/14/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the number of photons with an isotropic angular
     *         distribution
     */
    int NI() const {

      return ranges::count_if( this->photons_,
                               [] ( const auto& entry )
                                  { return entry.index() == 0; } );
    }

    /**
     *  @brief Return the number of photons with an isotropic angular
     *         distribution
     */
    int numberIsotropicPhotons() const { return this->NI(); }

    /**
     *  @brief Return the number of photons (discrete and continuum) with
     *         angular distributions
     */
    int NK() const { return this->photons_.size(); }

    /**
     *  @brief Return the number of photons (discrete and continuum) with
     *         angular distributions
     */
    int numberPhotons() const { return this->NK(); }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool LI() const { return this->photons_.size() == 0; }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool isotropicDistributions() const { return this->LI(); }

    /**
     *  @brief Return the distribution law
     */
    int LTT() const {

      return this->LI() ? 0
                        : std::visit( [] ( const auto& photon )
                                         { return photon.LTT(); },
                                      this->photons_.back() );
    }

    /**
     *  @brief Return the distribution law
     */
    int LAW() const { return this->LTT(); }

    /**
     *  @brief Return the secondary photons with their angular distribution
     */
    const auto& photonAngularDistributions() const { return this->photons_; }

    #include "ENDFtk/section/14/src/NC.hpp"
    #include "ENDFtk/section/14/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
