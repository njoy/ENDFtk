/**
 *  @class
 *  @brief Multiplicity data for a photon or electron
 *
 *  Note: the multiplicity for MF26 is normally always equal to 1 (see ENDF102,
 *  section 26.2, y(E)).
 *
 *  See ENDF102, section 26.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT Multiplicity : protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] zap               the ZAID value for the reaction product
   *  @param[in] awi               the atomic weight ratio for the projectile
   *  @param[in] law               the distribution type
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] energies          the x values
   *  @param[in] multiplicities    the function values
   */
  Multiplicity( int zap, double awi, long law,
                std::vector< long >&& boundaries,
                std::vector< long >&& interpolants,
                std::vector< double >&& energies,
                std::vector< double >&& multiplicities )
    try : TabulationRecord( static_cast< double >( zap ), awi, 0, law,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( multiplicities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing Multiplicity" );
      throw;
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator        a buffer iterator
   *
   *  @param[in] begin        the current position in the buffer
   *  @param[in] end          the end of the buffer
   *  @param[in] lineNumber   the current line number
   *  @param[in] MAT          the expected MAT number
   *  @param[in] MF           the expected MF number
   *  @param[in] MT           the expected MT number
   *  @param[in] NK           the number of partials
   */
  template< typename Iterator >
  Multiplicity( Iterator& begin, const Iterator& end,
                long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing Multiplicity" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  int ZAP() const {

    return static_cast< int >( std::round( TabulationRecord::C1() ) );
  }

  /**
   *  @brief Return the ZA identifier of the reaction product
   */
  double productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double AWI() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the atomic weight ratio of the projectile
   */
  double projectileWeightRatio() const { return this->AWI(); }

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  int LAW() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the energies
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicities
   */
  auto Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicities
   */
  auto multiplicities() const { return this->Y(); }

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
