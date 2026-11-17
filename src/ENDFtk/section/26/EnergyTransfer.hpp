/**
 *  @class
 *  @brief Only energy transfer during electro-atomic excitation or
 *         bremsstrahlung is given (LAW=8)
 *
 *  The EnergyTransfer class is used to represent law=8 data of MF26.
 *
 *  See ENDF102, section 26.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyTransfer : protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the x values
   *  @param[in] transfer        the energy transfer values
   */
  EnergyTransfer( std::vector< long >&& boundaries,
                  std::vector< long >&& interpolants,
                  std::vector< double >&& energies,
                  std::vector< double >&& transfer )
    try : TabulationRecord( 0., 0., 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( transfer ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing EnergyTransfer" );
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
  EnergyTransfer( Iterator& begin, const Iterator& end,
                  long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing EnergyTransfer" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the LAW flag for energy transfer data only
   */
  static constexpr int LAW() { return 8; }

  /**
   *  @brief Return the energies
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the energy transfer values
   */
  auto ET() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the energy transfer values
   */
  auto energyTransferValues() const { return this->ET(); }

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
