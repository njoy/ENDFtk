#ifndef NJOY_ENDFTK_SECTION_14
#define NJOY_ENDFTK_SECTION_14

// system includes
#include <variant>

// other includes
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

    #include "ENDFtk/section/4/Isotropic.hpp" // MF4 component taken over as is
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

  private:

    /* type aliases */

    /* fields */
    int lct_;
    std::vector< PhotonDistribution > photons_;

    /* auxiliary functions */

  public:

    /* constructor */
    #include "ENDFtk/section/14/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool LI() const { return this->photons_.size() == 0; }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool isotropicAngularDistributions() const { return this->LI(); }

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
     *  @brief Return the partial distributions defined in this section
     */
    const auto& photons() const { return this->photons_; }

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
