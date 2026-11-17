#ifndef NJOY_ENDFTK_SECTION_4
#define NJOY_ENDFTK_SECTION_4

// system includes
#include <variant>
#include <vector>

// other includes
#include "tools/std20/views.hpp"
#include "tools/views/AnyView.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/overload.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF4 - angular distributions of secondary particles
   *
   *  See ENDF102, section 4.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 4 > : protected Base {

  protected:

    #include "ENDFtk/section/4/AngularDistributions.hpp"

  public:

    #include "ENDFtk/section/4/LegendreCoefficients.hpp"
    #include "ENDFtk/section/4/TabulatedDistribution.hpp"

    using Variant =
      std::variant< std::reference_wrapper< const LegendreCoefficients >,
                    std::reference_wrapper< const TabulatedDistribution > >;

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

  private:

    /* type aliases */

    template < typename Element >
    using RandomAccessAnyView = njoy::tools::views::AnyRandomAccessView< Element >;
    using DoubleRange = RandomAccessAnyView< double >;
    using LongRange = RandomAccessAnyView< long >;
    using VariantRange = RandomAccessAnyView< Variant >;

    /* fields */

    int lct_;
    Distributions distributions_;

    /* auxiliary functions */

    template< typename Iterator >
    static Distributions
    readDistributions( Iterator& begin,
                       const Iterator& end,
                       long& lineNumber,
                       int MAT,
                       int MF,
                       int MT,
                       long LTT) {

      switch ( LTT ) {
        case 0 : return Isotropic();
        case 1 : return LegendreDistributions( begin, end, lineNumber,
                                               MAT, MF, MT );
        case 2 : return TabulatedDistributions( begin, end, lineNumber, MAT, MF, MT );
        case 3 : return MixedDistributions( begin, end, lineNumber, MAT, MF, MT );
        default : {
          Log::error( "Encountered illegal LTT value" );
          Log::info( "LTT must be equal to 0, 1, 2 or 3" );
          Log::info( "LTT value: {}", LTT );
          Log::info( "Line number: {}", lineNumber - 2 );
          throw std::exception();
        }
      }
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    template< typename Iterator >
    Type ( HEAD& head,
           const ControlRecord& cont,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT ) :
      Base( head, MAT, 4 ),
      lct_( cont.L2() ),
      distributions_( readDistributions( begin, end, lineNumber,
                                         head.MAT(), 4, head.MT(), head.L2() ) ) {}

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
     *  @param[in] mt              the MT number for the section
     *  @param[in] zaid            the material ZAID value
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] lct             the reference frame
     *  @param[in] distributions   the distributions
     */
    Type( int MT, int zaid, double awr, long lct,
          Distributions&& distributions ) :
      Base( zaid, awr, MT ), lct_( lct ),
      distributions_( std::move( distributions ) ) {}

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
    Type ( HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
      try: Type( head,
                 ControlRecord( begin, end, lineNumber, head.MAT(), 4, head.MT() ),
                 begin, end, lineNumber, MAT ) {

        readSEND(begin, end, lineNumber, MAT, 4 );
      } catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 4 of material {}",
          head.MT(), MAT );
        throw;
      }

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
    const Distributions& distributions() const { return this->distributions_; }

    /**
     *  @brief Return the number of interpolation regions
     */
    long NR() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> int
                      { return 0; },
                   [] ( const auto& distributions ) -> int
                      { return distributions.NR(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the number of interpolation regions
     */
    auto numberInterpolationRegions() const { return this->NR(); }

    /**
     *  @brief Return the number of incident energy points
     */
    auto NE() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> int
                      { return 0; },
                   [] ( const auto& distributions ) -> int
                      { return distributions.NE(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the number of incident energy points
     */
    auto numberIncidentEnergies() const { return this->NE(); }

    /**
     *  @brief Return the interpolants of the interpolation regions
     */
    auto INT() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> LongRange
                      { using namespace njoy::tools;
                        return std20::views::empty< long >; },
                   [] ( const auto& distributions ) -> LongRange
                      { return distributions.INT(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the interpolants of the interpolation regions
     */
    auto interpolants() const { return this->INT(); }

    /**
     *  @brief Return the boundaries of the interpolation regions
     *
     *         The intersection point is considered as a jump in the incident
     *         energy.
     */
    auto NBT() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> LongRange
                      { using namespace njoy::tools;
                        return std20::views::empty< long >; },
                   [] ( const auto& distributions ) -> LongRange
                      { return distributions.NBT(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the boundaries of the interpolation regions
     *
     *         The intersection point is considered as a jump in the incident
     *         energy.
     */
    auto boundaries() const { return this->NBT(); }

    /**
     *  @brief Return the incident energy values
     */
    auto incidentEnergies() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> DoubleRange
                      { using namespace njoy::tools;
                        return std20::views::empty< double >; },
                   [] ( const auto& distributions ) -> DoubleRange
                      { return distributions.incidentEnergies(); } },
               this->distributions_ );
    }

    /**
     *  @brief Return the angular distributions (one for each incident energy)
     *
     *  This function returns the underlying angular distributions as a variant of
     *  reference wrappers. See the section::Type< 4 > unit test for more
     *  information on how to use this.
     */
    auto angularDistributions() const {

      return std::visit(
               tools::overload{
                   [] ( const Isotropic& ) -> VariantRange
                        { using namespace njoy::tools;
                          return std20::views::empty<Variant>; 
                        },
                   [] ( const MixedDistributions& distributions ) -> VariantRange
                        { return distributions.angularDistributions(); 
                        },
                   [&] ( const LegendreDistributions& distributions ) -> VariantRange
                         { using namespace njoy::tools;
                           return distributions.angularDistributions()
                                | std20::views::transform( [] ( auto&& element ) -> Variant
                                                              { return std::cref( element ); } ); 
                         },
                   [&] ( const TabulatedDistributions& distributions ) -> VariantRange
                         { using namespace njoy::tools;
                         return distributions.angularDistributions()
                                | std20::views::transform( [] ( auto&& element ) -> Variant
                                                              { return std::cref( element ); } ); 
                         }
               },

               this->distributions_ );
    }

    /** 
     *  @brief Return the number of lines in this MF4 section
     */
    long NC() const {

      return 2 + std::visit( [&] ( const auto& v ) { return v.NC(); },
                             this->distributions_ );
    };

    /** 
     *  @brief Print the MF4 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), 0, this->LTT(),
                     0, 0 ).print( it, MAT, MF, MT );
      ControlRecord( 0, this->AWR(), this->LI(), this->LCT(),
                     0, 0 ).print( it, MAT, MF, MT );
      std::visit( [&] ( const auto& v ) { return v.print( it, MAT, MF, MT ); },
                  this->distributions_ );
      SEND( MAT, MF ).print( it );
    } 

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
