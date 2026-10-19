/**
 *  @class
 *  @brief Discrete two-body scattering data for secondary particles (LAW=2)
 *
 *  The DiscreteTwoBodyScattering class is used to represent the discrete
 *  two-body scattering law=2 data of MF6.
 *
 *  See ENDF102, section 6.2.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscreteTwoBodyScattering {

public:

  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution.hpp"

  using Variant = std::variant< LegendreCoefficients,    // LANG=1
                                TabulatedDistribution >; // LANG=12,14

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

        case 0 : sequence.emplace_back(
                    LegendreCoefficients( std::move( list ) ) );
                    break;
        case 12 :
        case 14 : sequence.emplace_back(
                    TabulatedDistribution( std::move( list ) ) );
                    break;
        default : {

          Log::error( "Encountered illegal LANG value" );
          Log::info( "LANG must be equal to 0, 12 or 14" );
          Log::info( "LANG value: {}", list.L1() );
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
  DiscreteTwoBodyScattering( InterpolationRecord&& interpolation,
                             std::vector< Variant >&& sequence ) :
    data_( std::move( interpolation ), std::move( sequence ) ) {}

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  DiscreteTwoBodyScattering( InterpolationRecord&& interpolation,
                             Iterator& begin,
                             const Iterator& end,
                             long& lineNumber,
                             int MAT,
                             int MF,
                             int MT ) :
    DiscreteTwoBodyScattering( std::move( interpolation ),
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
  DiscreteTwoBodyScattering() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries     the interpolation range boundaries
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] sequence       the data for each incident energy value
   */
  DiscreteTwoBodyScattering( std::vector< long >&& boundaries,
                             std::vector< long >&& interpolants,
                             std::vector< Variant >&& sequence )
    try : DiscreteTwoBodyScattering(
            InterpolationRecord( 0.0, 0.0, 0, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( sequence ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete two body "
                 "scattering distribution data (LAW=2)" );
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
  DiscreteTwoBodyScattering ( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT )
    try : DiscreteTwoBodyScattering(
            InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete two body "
                 "scattering distribution data (LAW=2)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the LAW flag
   */
  static constexpr int LAW() { return 2; }

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
   *  @brief Return the number of secondary energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of secondary energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the distributions, one for each incident energy
   */
  auto distributions() const { return this->data_.records(); }

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
   *  @brief Print the component
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
