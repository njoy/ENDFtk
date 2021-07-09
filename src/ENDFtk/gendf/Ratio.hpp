#ifndef NJOY_ENDFTK_GENDF_RATIO
#define NJOY_ENDFTK_GENDF_RATIO

// system includes

// other includes
#include "ENDFtk/gendf/SectionBase.hpp"

namespace njoy {
namespace ENDFtk {
namespace gendf {

  class Ratio : protected SectionBase {

  protected:

    /* constructor */
    #include "ENDFtk/gendf/Ratio/src/ctor.hpp"

  public:


    /* convenience functions */

    /**
     *  @brief Return a list of fluxes for each group.
     *
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    auto fluxes( unsigned int order, unsigned int dilution ) {

      checkBounds( order, dilution );
      return ranges::view::iota( 1, this->num_groups_+1 )
             | ranges::view::transform(
                   [&] ( unsigned int group ) -> double
                       { return getValue( 0, group, order, dilution ); } );
    }

    /**
     *  @brief Return a list of fluxes for each group.
     *
     *  @note Assumes order=0.  Most CrossSections in a GENDF have NL=1.
     *
     *  @param[in] dilution   the index of the dilution
     */
    auto fluxes( unsigned int dilution ) { return fluxes( 0, dilution ); }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    double flux( unsigned int group, unsigned int order,
                 unsigned int dilution ) {

      checkBounds( group, order, dilution );
      return getValue( 0, group, order, dilution );
    }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] dilution   the index of the dilution
     */
    double flux( unsigned int group, unsigned int dilution ) {
      return flux( group, 0, dilution );
    }

    /**
     *  @brief Return the flux for a given energy group.
     *
     *  @param[in] group      the energy group index
     */
    double flux( unsigned int group ) { return flux( group, 0, 0 ); }

    /**
     *  @brief Return a list of ratios for each group.
     *
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    auto ratios( unsigned int order, unsigned int dilution ) {

      checkBounds( order, dilution );
      return ranges::view::iota( 1, this->num_groups_+1 )
             | ranges::view::transform(
                   [&] ( unsigned int group ) -> double
                       { return getValue( 1, group, order, dilution ); } );
    }

    /**
     *  @brief Return a list of ratios for each group.
     *
     *  @note Assumes order=0.  Most Ratios in a GENDF have NL=1.
     *
     *  @param[in] dilution   the index of the dilution
     */
    auto ratios( unsigned int dilution ) {
      return ratios( 0, dilution );
    }

    /**
     *  @brief Return the ratio for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    double ratio( unsigned int group, unsigned int order,
                         unsigned int dilution ) {

      checkBounds( group, order, dilution );
      return getValue( 1, group, order, dilution );
    }

    /**
     *  @brief Return the ratio for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] dilution   the index of the dilution
     */
    double ratio( unsigned int group, unsigned int dilution ) {
      return ratio( group, 0, dilution );
    }

    /**
     *  @brief Return the ratio for a given energy group.
     *
     *  @param[in] group      the energy group index
     */
    double ratio( unsigned int group ) {
      return ratio( group, 0, 0 );
    }

    /**
     *  @brief Return a list of cross sections for each group.
     *
     *  @param[in] order      the Legendre order
     *  @param[in] dilution   the index of the dilution
     */
    auto crossSections( unsigned int order, unsigned int dilution ) {

      checkBounds( order, dilution );
      return ranges::view::iota( 1, this->num_groups_+1 )
             | ranges::view::transform(
                   [&] ( unsigned int group ) -> double
                       { return getValue( 2, group, order, dilution ); } );
    }

    /**
     *  @brief Return a list of cross sections for each group.
     *
     *  @note Assumes order=0.  Most CrossSections in a GENDF have NL=1.
     *
     *  @param[in] dilution   the index of the dilution
     */
    auto crossSections( unsigned int dilution ) {
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
                         unsigned int dilution ) {

      checkBounds( group, order, dilution );
      return getValue( 2, group, order, dilution );
    }

    /**
     *  @brief Return the cross section for a given energy group.
     *
     *  @param[in] group      the energy group index
     *  @param[in] dilution   the index of the dilution
     */
    double crossSection( unsigned int group, unsigned int dilution ) {
      return crossSection( group, 0, dilution );
    }

    /**
     *  @brief Return the cross section for a given energy group.
     *
     *  @param[in] group      the energy group index
     */
    double crossSection( unsigned int group ) {
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
