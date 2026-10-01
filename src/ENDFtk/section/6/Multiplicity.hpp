/**
 *  @class
 *  @brief Multiplicity data for a reaction product
 *
 *  See ENDF102, section 6.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT Multiplicity : protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] zap               the ZAID value for the reaction product
   *  @param[in] awp               the atomic weight ratio for the reaction
   *                               product
   *  @param[in] lip               the product modifier flag
   *  @param[in] law               the distribution type
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] energies          the x values
   *  @param[in] multiplicities    the function values
   */
  Multiplicity( int zap, double awp, long lip, long law,
                std::vector< long >&& boundaries,
                std::vector< long >&& interpolants,
                std::vector< double >&& energies,
                std::vector< double >&& multiplicities )
    try : TabulationRecord( static_cast< double >( zap ), awp, lip, law,
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
  int productIdentifier() const { return this->ZAP(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double AWP() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the atomic weight ratio of the reaction product
   */
  double productWeightRatio() const { return this->AWP(); }

  /**
   *  @brief Return the product modifier flag
   */
  int LIP() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the product modifier flag
   */
  int productModifierFlag() const { return this->LIP(); }

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
