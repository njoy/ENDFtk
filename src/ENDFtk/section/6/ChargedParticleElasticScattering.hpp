/**
 *  @class
 *  @brief Charged particle elastic scattering data for secondary
 *         particles (LAW=5)
 *
 *  The ChargedParticleElasticScattering class is used to represent the
 *  charged particle law=5 data of MF6.
 *
 *  See ENDF102, section 6.2.7 for more information.
 */
class ENDFTK_PYTHON_EXPORT ChargedParticleElasticScattering {

public:

  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearAmplitudeExpansion.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ChargedParticleElasticScattering/NuclearPlusInterference.hpp"

  using Variant = std::variant< NuclearAmplitudeExpansion, // LTP=1
                                LegendreCoefficients,      // LTP=2
                                NuclearPlusInterference >; // LTP>2

private:

  /* fields */

  InterpolationSequenceRecord< Variant > data_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::vector< Variant >
  readSequence( long nep,
                Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) {

    std::vector< Variant > sequence;
    sequence.reserve( nep );

    while( nep-- ) {

      ListRecord list( begin, end, lineNumber, MAT, MF, MT );
      switch ( list.L1() ) {

        case 1 : sequence.emplace_back(
                    NuclearAmplitudeExpansion( std::move( list ) ) );
                    break;
        case 2 : sequence.emplace_back(
                    LegendreCoefficients( std::move( list ) ) );
                    break;
        case 12 :
        case 14 :
        case 15 : sequence.emplace_back(
                    NuclearPlusInterference( std::move( list ) ) );
                    break;
        default : {

          Log::error( "Encountered illegal LTP value" );
          Log::info( "LTP must be equal to 1, 2, 12, 14 or 15" );
          Log::info( "LTP value: {}", list.L1() );
          Log::info( "Line number: {}", lineNumber - list.NC() );
          throw std::exception();
        }
      }
    }

    return sequence;
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ChargedParticleElasticScattering( InterpolationRecord&& interpolation,
                                    std::vector< Variant >&& sequence ) :
    data_( std::move( interpolation ), std::move( sequence ) ) {}

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  ChargedParticleElasticScattering( InterpolationRecord&& interpolation,
                                    Iterator& begin,
                                    const Iterator& end,
                                    long& lineNumber,
                                    int MAT,
                                    int MF,
                                    int MT ) :
    ChargedParticleElasticScattering( std::move( interpolation ),
                                      readSequence( interpolation.NZ(),
                                                    begin, end, lineNumber,
                                                    MAT, MF, MT ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ChargedParticleElasticScattering() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] spin             the spin of the charged particle
   *  @param[in] lidp             the identicle particle flag
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the data for each incident energy value
   */
  ChargedParticleElasticScattering ( double spin, long lidp,
                                     std::vector< long >&& boundaries,
                                     std::vector< long >&& interpolants,
                                     std::vector< Variant >&& distributions )
    try : ChargedParticleElasticScattering(
            InterpolationRecord( spin, 0.0, lidp, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( distributions ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing charged particle elastic "
                 "scattering distribution data (LAW=5)" );
      throw;
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] it           the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   */
  template< typename Iterator >
  ChargedParticleElasticScattering ( Iterator& begin,
                                     const Iterator& end,
                                     long& lineNumber,
                                     int MAT,
                                     int MF,
                                     int MT )
    try : ChargedParticleElasticScattering(
            InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing charged particle elastic "
                 "scattering distribution data (LAW=5)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the LAW flag for charged particle elastic scattering
   */
  static constexpr int LAW() { return 5; }

  /**
   *  @brief Return the spin of the particle
   */
  double SPI() const { return this->data_.tab2().C1(); }

  /**
   *  @brief Return the spin of the particle
   */
  double spin() const { return this->SPI(); }

  /**
   *  @brief Return whether or not the particles are identical
   */
  bool LIDP() const { return this->data_.tab2().L1(); }

  /**
   *  @brief Return whether or not the particles are identical
   */
  bool identicalParticles() const { return this->LIDP(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident
   *         energy axis
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the distributions, one for each incident energy
   */
  auto distributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    using namespace njoy::tools;
    return this->distributions()
               | std20::views::transform(
                  [] ( const auto& variant )
                     { return std::visit( [] ( const auto& record )
                                             { return record.incidentEnergy(); },
                                          variant ); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  /**
   *  @brief Print the MF6 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    this->data_.print( it, MAT, MF, MT );
  }
};
