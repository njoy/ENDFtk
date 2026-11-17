/**
 *  @class
 *  @brief Continuum energy-angle data for secondary particles (LAW=1)
 *
 *  The ContinuumEnergyAngle class is used to represent the continuum
 *  energy-angle law=1 data of MF6.
 *
 *  See ENDF102, section 6.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT ContinuumEnergyAngle {

public:

  #include "ENDFtk/section/6/ContinuumEnergyAngle/Base.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/ThermalScatteringData.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/LegendreCoefficients.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/KalbachMann.hpp"
  #include "ENDFtk/section/6/ContinuumEnergyAngle/TabulatedDistribution.hpp"

  using Variant = std::variant< LegendreCoefficients,    // LANG=1
                                KalbachMann,             // LANG=2
                                ThermalScatteringData,   // LANG=3
                                TabulatedDistribution >; // LANG=11-15

private:

  /* fields */

  InterpolationSequenceRecord< Variant > data_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::vector< Variant >
  readSequence( long lang,
                long nep,
                Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) {

    std::vector< Variant > sequence;
    sequence.reserve( nep );

    while( nep-- ) {
      switch ( lang ) {
        case 1 : sequence.emplace_back(
                    LegendreCoefficients( begin, end, lineNumber, MAT, MF, MT ) );
                    break;
        case 2 : sequence.emplace_back(
                    KalbachMann( begin, end, lineNumber, MAT, MF, MT ) );
                    break;
        case 3 : sequence.emplace_back(
                    ThermalScatteringData( begin, end, lineNumber, MAT, MF, MT ) );
                    break;
        case 11 :
        case 12 :
        case 13 :
        case 14 :
        case 15 : sequence.emplace_back(
                    TabulatedDistribution( lang, begin, end, lineNumber,
                                           MAT, MF, MT ) );
                    break;
        default : {

          Log::error( "Encountered illegal LANG value" );
          Log::info( "LANG must be equal to 1, 2, 3, 11, 12, 13, 14 or 15" );
          Log::info( "LANG value: {}", lang );
          throw std::exception();
        }
      }
    }

    return sequence;
  }

  template< typename Array >
  static void
  verifyLANG( int LANG, const Array& sequence ) {

    auto compare = [LANG] ( const auto& variant )
                          { return std::visit( [] ( const auto& entry )
                                                  { return entry.LANG(); },
                                               variant ) == LANG; };

    auto iter = std::find_if_not( sequence.begin(), sequence.end(), compare );

    if ( iter != sequence.end() ) {

      using namespace njoy::tools;
      Log::error( "All subsections must use the same LANG format option" );
      Log::info( "Expected LANG={} for the subsection with index={}", LANG,
                 std20::distance( sequence.begin(), iter ) );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                        std::vector< Variant >&& sequence ) :
    data_( std::move( interpolation ), std::move( sequence ) ) {

    verifyLANG( this->LANG(), this->data_.records() );
  }

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  ContinuumEnergyAngle( InterpolationRecord&& interpolation,
                        Iterator& begin,
                        const Iterator& end,
                        long& lineNumber,
                        int MAT,
                        int MF,
                        int MT ) :
    ContinuumEnergyAngle( std::move( interpolation ),
                          readSequence( interpolation.L1(), interpolation.NZ(),
                                        begin, end, lineNumber, MAT, MF, MT ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  ContinuumEnergyAngle() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] lep              the secondary energy interpolation scheme
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the data for each incident energy value
   */
  ContinuumEnergyAngle( long lep,
                        std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< Variant >&& distributions )
    try : ContinuumEnergyAngle(
            InterpolationRecord( 0.0, 0.0,
                                 std::visit( [] ( const auto& entry )
                                                { return entry.LANG(); },
                                             distributions.front() ),
                                 lep,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( distributions ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing continuum energy angle "
                 "distribution data (LAW=1)" );
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
  ContinuumEnergyAngle( Iterator& begin,
                        const Iterator& end,
                        long& lineNumber,
                        int MAT,
                        int MF,
                        int MT )
    try : ContinuumEnergyAngle(
            InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading continuum energy angle "
                 "distribution data (LAW=1)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the LAW flag
   */
  static constexpr int LAW() { return 1; }

  /**
   *  @brief Return the LANG flag for the data representation type
   */
  int LANG() const { return this->data_.tab2().L1(); }

  /**
   *  @brief Return the interpolation scheme for secondary energies
   */
  int LEP() const { return this->data_.tab2().L2(); }

  /**
   *  @brief Return the interpolation scheme for secondary energies
   */
  int interpolationScheme() const { return this->LEP(); }

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
   *  @brief Return the subsections, one for each incident energy
   */
  auto distributions() const {

    return this->data_.records();
  }

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
