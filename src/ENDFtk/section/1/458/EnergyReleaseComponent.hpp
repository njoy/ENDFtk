/**
 *  @class
 *  @brief A tabulated fission energy release component
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyReleaseComponent : protected TabulationRecord {

  /* auxiliary functions */

  static void verify( int LDRV, int IFC ) {

    if ( ( LDRV != 1 ) && ( LDRV != 2 ) ) {

      Log::error( "The value for the primary evaluation flag is not recognised" );
      Log::info( "Expected LDRV equal to 1 or 2" );
      Log::info( "Found {}", LDRV );
      throw std::exception();
    }
    if ( ( IFC < 1 ) || ( IFC > 9 ) ) {

      Log::error( "The index for the energy release component is invalid" );
      Log::info( "Expected IFC between 1 and 9" );
      Log::info( "Found {}", IFC );
      throw std::exception();
    }
  }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  EnergyReleaseComponent( TabulationRecord&& table ) :
    TabulationRecord( std::move( table ) ) {

      verify( TabulationRecord::L1(), TabulationRecord::L2() );
    }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] ldrv            the primary evaluation flag (true/false)
   *  @param[in] ifc             the index for the fission energy release
   *                             component
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the incident energy values
   *  @param[in] qvalues         the fission q values
   */
  EnergyReleaseComponent( bool ldrv, int ifc,
                          std::vector< long >&& boundaries,
                          std::vector< long >&& interpolants,
                          std::vector< double >&& energies,
                          std::vector< double >&& qvalues )
    try : EnergyReleaseComponent(
              TabulationRecord( 0.0, 0.0, ldrv ? 2 : 1, ifc,
                                std::move( boundaries ),
                                std::move( interpolants ),
                                std::move( energies ),
                                std::move( qvalues ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated fission "
      	         "energy release component" );
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
  EnergyReleaseComponent( Iterator& begin, const Iterator& end,
                          long& lineNumber, int MAT, int MF, int MT )
    try : EnergyReleaseComponent(
              TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated fission "
      	         "energy release component" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the primary evaluation flag (true/false)
   */
  bool LDRV() const { return TabulationRecord::L1() == 1 ? false : true; }

  /**
   *  @brief Return the primary evaluation flag (true/false)
   */
  bool primaryEvaluationFlag() const { return this->LDRV(); }

  /**
   *  @brief Return the index for the fission energy release component
   */
  int IFC() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the index for the fission energy release component
   */
  int componentIndex() const { return this->IFC(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the fission energy release values
   */
  auto EIFC() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the fission energy release values
   */
  auto qValues() const { return this->EIFC(); }

  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
