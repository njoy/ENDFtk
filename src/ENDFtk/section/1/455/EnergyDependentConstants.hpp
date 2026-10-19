/**
 *  @class
 *  @brief Energy dependent decay constants for delayed neutron precursor
 *         families (LDG = 1)
 *
 *  See ENDF102, section 1.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyDependentConstants :
  protected InterpolationSequenceRecord< DecayConstants > {

  /* auxiliary functions */

  template < typename Range >
  static void verify( const Range& lists ) {

    int NNF = lists[0].NNF();
    for ( const auto& entry : lists ) {

      if ( entry.NNF() != NNF ) {

        Log::error( "Encountered inconsistent NNF values over all decay constants" );
        Log::info( "Expected NNF = {}", NNF );
        Log::info( "Found NNF = {}", entry.NNF() );
        throw std::exception();
      }
    }
  }

public:
  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  EnergyDependentConstants() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] constants       the decay constants
   */
  EnergyDependentConstants( std::vector< long >&& boundaries,
                            std::vector< long >&& interpolants,
                            std::vector< DecayConstants >&& constants )
    try : InterpolationSequenceRecord(
            InterpolationRecord( 0.0, 0.0, 0, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( constants ) ) {

      verify( this->records() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing energy dependent decay "
                 "constants" );
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
  EnergyDependentConstants( Iterator& it, const Iterator& end,
                            long& lineNumber, int MAT, int MF, int MT )
    try : InterpolationSequenceRecord(
            readInterpolationSequenceRecord< DecayConstants >(
              it, end, lineNumber, MAT, MF, MT ) ) {

      verify( this->records() );
    }
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading energy dependent decay "
                 "constants" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the type of decay constants
   */
  static constexpr int LDG() { return 1; }

  /**
   *  @brief Return the type of decay constants
   */
  int type() const { return this->LDG(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return this->records()[0].NNF();; }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long NR() const { return InterpolationSequenceRecord::tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return InterpolationSequenceRecord::tab2().NZ(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto INT() const {

    return InterpolationSequenceRecord::tab2().interpolants();
  }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto NBT() const {

    return InterpolationSequenceRecord::tab2().boundaries();
  }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the decay contants
   */
  auto constants() const {

    return this->records();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    using namespace njoy::tools;
    return this->constants()
               | std20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  using InterpolationSequenceRecord::NC;
  using InterpolationSequenceRecord::print;
};
