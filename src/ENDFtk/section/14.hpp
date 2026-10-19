#ifndef NJOY_ENDFTK_SECTION_14
#define NJOY_ENDFTK_SECTION_14

// system includes
#include <variant>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF14 - angular distributions of secondary photons
   *
   *  See ENDF102, section 14.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 14 > : protected Base {

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

    unsigned int nk_;
    std::vector< PhotonDistribution > photons_;

    /* auxiliary functions */

    template< typename Iterator >
    static std::vector< PhotonDistribution >
    readPhotons( Iterator& begin,
                 const Iterator& end,
                 long& lineNumber,
                 int MAT,
                 int MF,
                 int MT,
                 long LI,
                 long NI,
                 long NK,
                 long LTT) {

      std::vector< PhotonDistribution > sequence;
      if ( LI != 1 ) {

        sequence.reserve( NK );

        // NK is the total number of photon subsections
        // subtract the NI discrete photons we'll read first
        NK -= NI;

        while ( NI-- ) {

          sequence.push_back( IsotropicDiscretePhoton( begin, end, lineNumber,
                                                       MAT, MF, MT ) );
        }

        while ( NK-- ) {

          switch ( LTT ) {

            case 1 : {

              sequence.push_back( LegendreDistributions( begin, end, lineNumber,
                                                         MAT, MF, MT ) );
              break;
            }
            case 2 : {

              sequence.push_back( TabulatedDistributions( begin, end, lineNumber,
                                                          MAT, MF, MT ) );
              break;
            }
            default : {
              Log::error( "Encountered illegal LTT value" );
              Log::info( "LTT must be equal to 1 or 2" );
              Log::info( "LTT value: {}", LTT );
              Log::info( "Line number: {}", lineNumber - 2 );
              throw std::exception();
            }
          }
        }
      }

      return sequence;
    }

    static std::vector< PhotonDistribution >
    makePhotonDistributions( std::vector< std::array< double, 2 > >&& isotropic,
                             std::vector< AnisotropicPhotonDistribution >&& anisotropic ) {

      std::vector< PhotonDistribution > sequence;
      sequence.reserve( isotropic.size() + anisotropic.size() );

      for ( unsigned int i = 0; i < isotropic.size(); ++i ) {

        sequence.emplace_back( IsotropicDiscretePhoton( isotropic[i][0],
                                                        isotropic[i][1] ) );
      }

      for ( unsigned int i = 0; i < anisotropic.size(); ++i ) {

        std::visit( [&sequence] ( auto&& alternative )
                                { sequence.emplace_back( std::move( alternative ) ); },
                     anisotropic[i] );
      }

      return sequence;
    }

    static std::vector< std::array< double, 2 > >
    makeArrays( std::vector< double >&& energies,
                std::vector< double >&& levels ) {

      std::vector< std::array< double, 2 > > sequence;
      unsigned int size = energies.size();
      sequence.reserve( size );

      if ( size != levels.size() ) {

        Log::error( "Encountered inconsistent number of photon energy values and "
                    "level energy values" );
        Log::info( "Number of photon energy values: {}", size );
        Log::info( "Number of energy level values: {}", levels.size() );
        throw std::exception();
      }

      for ( unsigned int i = 0; i < size; ++i ) {

        sequence.push_back( {{ energies[i], levels[i] }} );
      }

      return sequence;
    }

    /* constructor */

    /**
     *  @brief Private intermediate constructor
     */
    Type( int MT, int zaid, double awr, unsigned int nk,
          std::vector< PhotonDistribution >&& photons ) :
      Base( zaid, awr, MT ),
      nk_( nk ), photons_( std::move( photons ) ) {}

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
     *  @brief Constructor for isotropic photon distributions
     *
     *  @param[in] mt              the MT number for the section
     *  @param[in] zaid            the material ZAID value
     *  @param[in] awr             the atomic weight ratio
     *  @param[in] nk              the number of photons
     */
    Type( int MT, int zaid, double awr, unsigned int nk ) :
      Base( zaid, awr, MT ),
      nk_( nk ), photons_() {}

    /**
     *  @brief Constructor
     *
     *  @param[in] mt        the MT number for the section
     *  @param[in] zaid      the material ZAID value
     *  @param[in] awr       the atomic weight ratio
     *  @param[in] photons   the photon distribution data
     */
    Type( int MT, int zaid, double awr,
          std::vector< PhotonDistribution >&& photons ) :
      Base( zaid, awr, MT ),
      nk_(0), photons_( std::move( photons ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number for the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] isotropic     the photon and level energies for the isotropic
     *                           photons
     *  @param[in] anisotropic   the distribution data for the anisotropic photons
     */
    Type( int MT, int zaid, double awr,
          std::vector< std::array< double, 2 > >&& isotropic,
          std::vector< AnisotropicPhotonDistribution >&& anisotropic ) :
      Type( MT, zaid, awr,
            makePhotonDistributions( std::move( isotropic ),
                                     std::move( anisotropic ) ) ) {}

    /**
     *  @brief Constructor
     *
     *  @param[in] mt            the MT number for the section
     *  @param[in] zaid          the material ZAID value
     *  @param[in] energies      the photon energy for each isotropic photon
     *  @param[in] levels        the level energy for each isotropic photon
     *  @param[in] anisotropic   the distribution data for the anisotropic photons
     */
     Type( int MT, int zaid, double awr,
           std::vector< double >&& energies,
           std::vector< double >&& levels,
           std::vector< AnisotropicPhotonDistribution >&& anisotropic ) :
       Type( MT, zaid, awr,
             makeArrays( std::move( energies ), std::move( levels ) ),
             std::move( anisotropic ) ) {}

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
      try: Type( head.MT(), head.ZA(), head.AWR(), head.N1(),
                 readPhotons( begin, end, lineNumber, head.MAT(), 14, head.MT(),
                              head.L1(), head.N2(), head.N1(), head.L2() ) ) {

        readSEND(begin, end, lineNumber, MAT, 14 );
      } catch( std::exception& e ) {

        Log::info
        ( "Encountered error while reading section {} of file 14 of material {}",
          head.MT(), MAT );
        throw;
      }

    /* get methods */

    /**
     *  @brief Return the number of photons with an isotropic angular
     *         distribution
     */
    int NI() const {

      return std::count_if( this->photons_.begin(), this->photons_.end(),
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
     *         angular distributionss
     */
    int NK() const {

      return this->photons_.size() ? this->photons_.size() : this->nk_;
    }

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

    /**
     *  @brief Return the number of lines in this MF14 section
     */
    long NC() const {

      long NC = 1;
      for ( const auto& entry : this->photons_ ) {

        NC += std::visit( [&] ( const auto& v ) { return v.NC(); }, entry );
      }
      return NC;
    };

    /**
     *  @brief Print the MF14 section (includes SEND record)
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
      ControlRecord( this->ZA(), this->AWR(), this->LI(), this->LTT(),
                     this->NK(), this->NI() ).print( it, MAT, MF, MT );
      for ( const auto& entry : this->photons_ ) {

        std::visit( [&] ( const auto& v )
                        { return v.print( it, MAT, MF, MT ); },
                    entry );
      }
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
