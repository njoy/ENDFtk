/**
 *  @class
 *  @brief A partial photon production cross section (either for the continuum
 *         or a discrete photon).
 *
 *  See ENDF102, section 13.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT PartialCrossSection : protected TabulationRecord {

  /* auxiliary functions */

public:
  /* constructor */

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
   *  @param[in] xs               the partial cross section values
   */
  PartialCrossSection( double energy,
                       double level,
                       int lp,
                       int law,
                       std::vector< long >&& boundaries,
                       std::vector< long >&& interpolants,
                       std::vector< double >&& energies,
                       std::vector< double >&& xs )
    try : TabulationRecord( energy, level, lp, law,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( xs ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a partial photon "
                 "production cross section" );
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
  PartialCrossSection( Iterator& begin, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a partial photon "
                 "production cross section" );
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
   *  @brief Return the cross section values
   */
  auto XS() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->XS(); }

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
