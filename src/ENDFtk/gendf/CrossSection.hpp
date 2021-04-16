#ifndef NJOY_ENDFTK_GENDF_CROSSSECTION
#define NJOY_ENDFTK_GENDF_CROSSSECTION

// system includes

// other includes
#include "ENDFtk/gendf/SectionBase.hpp"
// #include "range/v3/action.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class CrossSection : protected SectionBase {

  protected:

    /* constructor */
    #include "ENDFtk/gendf/CrossSection/src/ctor.hpp"

  public:

    /* convenience functions */

    # include "ENDFtk/gendf/CrossSection/src/makeDataRecord.hpp"

    /**
     *  @brief Return a list of fluxes for each group.
     *
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    auto fluxes( unsigned int order, unsigned int dilution ) const {

      checkBounds( order, dilution );
      return ranges::view::iota( 1, this->num_groups_+1 )
             | ranges::view::transform(
               [=] ( unsigned int group ) -> double
                   { return getValue( 0, group, order, dilution ); } );
    }

    /**
     *  @brief Return a list of fluxes for each group.
     *
     *  @note Assumes order=0.  Most CrossSections in a GENDF have NL=1.
     *
     *  @param[in] dilution   the index of the dilution
     */
    auto fluxes( unsigned int dilution ) const { return fluxes( 0, dilution ); }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    double flux( unsigned int group, unsigned int order,
                 unsigned int dilution ) const {

      checkBounds( group, order, dilution );
      return this->getValue( 0, group, order, dilution );
    }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] dilution   the index of the dilution
     */
    double flux( unsigned int group, unsigned int dilution ) const {
      return flux( group, 0, dilution );
    }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     */
    double flux( unsigned int group ) const { return flux( group, 0, 0 ); }

    /**
     *  @brief Return a list of cross sections for each group.
     *
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    auto crossSections( unsigned int order, unsigned int dilution ) const {

      checkBounds( order, dilution );
      return ranges::view::iota( 1, this->num_groups_+1 )
             | ranges::view::transform(
               [=] ( unsigned int group ) -> double
                   { return this->getValue( 1, group, order, dilution ); } );
    }

    /**
     *  @brief Return a list of cross sections for each group.
     *
     *  @note Assumes order=0.  Most CrossSections in a GENDF have NL=1.
     *
     *  @param[in] dilution   the index of the dilution
     */
    auto crossSections( unsigned int dilution ) const {
      return crossSections( 0, dilution );
    }

    /**
     *  @brief Return the cross section for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    double crossSection( unsigned int group, unsigned int order,
                         unsigned int dilution ) const {

      checkBounds( group, order, dilution );
      return this->getValue( 1, group, order, dilution );
    }

    /**
     *  @brief Return the cross section for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] dilution   the index of the dilution
     */
    double crossSection( unsigned int group, unsigned int dilution ) const {
      return crossSection( group, 0, dilution );
    }

    /**
     *  @brief Return the cross section for a given energy group.
     *
     *  @param[in] group      the energy group index
     */
    double crossSection( unsigned int group ) const {
      return crossSection( group, 0, 0 );
    }

    // from gendf::SectionBase
    using SectionBase::NL;
    using SectionBase::numberLegendreMoments;
    using SectionBase::legendreOrder;
    using SectionBase::NZ;
    using SectionBase::numberDilutions;
    using SectionBase::numberSigmaZeros;
    using SectionBase::NGN;
    using SectionBase::numberGroups;
    using SectionBase::LR;
    using SectionBase::complexBreakUp;

    // from section::Base
    using SectionBase::MT;
    using SectionBase::sectionNumber;
    using SectionBase::ZA;
    using SectionBase::AWR;
    using SectionBase::atomicWeightRatio;

  };

}
}
}

#endif
