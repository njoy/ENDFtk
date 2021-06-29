#ifndef NJOY_ENDFTK_SECTION_4
#define NJOY_ENDFTK_SECTION_4

// system includes
#include <variant>
#include <vector>

// other includes
#include "range/v3/view/concat.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/view/empty.hpp"
#include "range/v3/view/any_view.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"
#include "utility/overload.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

  /**
   *  @class
   *  @brief MF4 - angular distributions of secondary particles
   *
   *  See ENDF102, section 4.2 for more information.
   */
  template<>
  class Type< 4 > : protected Base {

  protected:

    #include "ENDFtk/section/4/AngularDistributions.hpp"

  public:

    #include "ENDFtk/section/4/LegendreCoefficients.hpp"
    #include "ENDFtk/section/4/TabulatedDistribution.hpp"

    #include "ENDFtk/section/4/Isotropic.hpp"                    // LTT=0, LI=1
    #include "ENDFtk/section/4/LegendreDistributions.hpp"        // LTT=1, LI=0
    #include "ENDFtk/section/4/TabulatedDistributions.hpp"       // LTT=2, LI=0
    #include "ENDFtk/section/4/MixedDistributions.hpp"           // LTT=3, LI=0

    using LTT0 = Isotropic;
    using LTT1 = LegendreDistributions;
    using LTT2 = TabulatedDistributions;
    using LTT3 = MixedDistributions;

    /** @typedef Distributions
     *  @brief The secondary particle angular distribution of MF4
     *
     *  This distribution class is set up as a variant.
     */
    using Distributions =
              std::variant< Isotropic,                           // LTT=0, LI=1
                            LegendreDistributions,               // LTT=1, LI=0
                            TabulatedDistributions,              // LTT=2, LI=0
                            MixedDistributions >;                // LTT=3, LI=0

    using Variant =
      std::variant< std::reference_wrapper< const LegendreCoefficients >,
                    std::reference_wrapper< const TabulatedDistribution > >;

  private:

    /* type aliases */
    template < typename Element >
    using RandomAccessAnyView = ranges::any_view< Element, ranges::category::random_access >;
    using DoubleRange = RandomAccessAnyView< double >;
    using LongRange = RandomAccessAnyView< long >;
    using VariantRange = RandomAccessAnyView< Variant >;

    /* fields */
    int lct_;
    Distributions distributions_;

    /* auxiliary functions */
    #include "ENDFtk/section/4/src/readDistributions.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/4/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the reference frame
     */
    int LCT() const { return this->lct_; }

    /**
     *  @brief Return the reference frame
     */
    int referenceFrame() const { return this->LCT(); }

    /**
     *  @brief Return the distribution law
     */
    int LTT() const { return this->distributions_.index(); }

    /**
     *  @brief Return the distribution law
     */
    int LAW() const { return this->LTT(); }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool LI() const { return this->LTT() == 0; }

    /**
     *  @brief Return the isotropic angular distribution flag
     */
    bool isotropicDistributions() const { return this->LI(); }

    /**
     *  @brief Return the partial distributions defined in this section
     */
    const auto& distributions() const { return this->distributions_; }

    /**
     *  @brief Return the number of interpolation regions
     */
    auto NR() const {

      return std::visit(
               utility::overload{
                   [] ( const Isotropic& ) -> int
                      { return 0; },
                   [] ( const auto& distributions ) -> int
                      { return distributions.NR(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the number of energy points for which angular distributions
     *         are available.
     */
    auto NE() const {

      return std::visit(
               utility::overload{
                   [] ( const Isotropic& ) -> int
                      { return 0; },
                   [] ( const auto& distributions ) -> int
                      { return distributions.NE(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the boundaries of the interpolation ranges
     *
     *         The intersection point is considered as a jump in the incident
     *         energy.
     */
    auto boundaries() const {

      return std::visit(
               utility::overload{
                   [] ( const Isotropic& ) -> LongRange
                      { return ranges::view::empty< long >(); },
                   [] ( const auto& distributions ) -> LongRange
                      { return distributions.boundaries(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the interpolants of the interpolation ranges
     */
    auto interpolants() const {

      return std::visit(
               utility::overload{
                   [] ( const Isotropic& ) -> LongRange
                      { return ranges::view::empty< long >(); },
                   [] ( const auto& distributions ) -> LongRange
                      { return distributions.interpolants(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the incident energy values
     */
    auto incidentEnergies() const {

      return std::visit(
               utility::overload{
                   [] ( const Isotropic& ) -> DoubleRange
                      { return ranges::view::empty< double >(); },
                   [] ( const auto& distributions ) -> DoubleRange
                      { return distributions.incidentEnergies(); } },
               this->distributions_ );
    }

    #include "ENDFtk/section/4/src/angularDistributions.hpp"

    #include "ENDFtk/section/4/src/NC.hpp"
    #include "ENDFtk/section/4/src/print.hpp"

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
