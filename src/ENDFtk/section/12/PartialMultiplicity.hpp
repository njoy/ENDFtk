/**
 *  @class
 *  @brief A partial photon multiplicity (either for the continuum of a
 *         discrete photon).
 *
 *  See ENDF102, section 12.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT PartialMultiplicity : protected TabulationRecord {

  /* auxiliary functions */

public:
  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  PartialMultiplicity() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] energy           the photon or binding energy
   *  @param[in] level            the energy of the level from which the photon
   *                              originates
   *  @param[in] lp               the primary photon flag (0, 1 or 2)
   *  @param[in] law              the photon energy distribution law
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] energies         the energy values
   *  @param[in] multiplicities   the multiplicity values
   */
  PartialMultiplicity( double energy,
                       double level,
                       int lp,
                       int law,
                       std::vector< long >&& boundaries,
                       std::vector< long >&& interpolants,
                       std::vector< double >&& energies,
                       std::vector< double >&& multiplicities )
    try : TabulationRecord( energy, level, lp, law,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( multiplicities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a partial multiplicity" );
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
  PartialMultiplicity( Iterator& begin, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a partial multiplicity" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double ES() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the energy of the level from which the photon originates
   */
  double levelEnergy() const { return this->ES(); }

  /**
   *  @brief Return the photon energy or the binding energy
   */
  double EG() const { return TabulationRecord::C1(); }

  /**
  *  @brief Return the photon energy or the binding energy
   */
  double photonOrBindingEnergy() const { return this->EG(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int LP() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the primary photon flag value
   */
  int primaryPhotonFlag() const { return this->LP(); }

  /**
   *  @brief Return the photon energy distribution law number
   */
  int LF() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the photon energy distribution law number
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the multiplicity values
   */
  auto Y() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the multiplicity values
   */
  auto multiplicities() const { return this->Y(); }

  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::x;
  using TabulationRecord::y;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
