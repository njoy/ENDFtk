// forward declaration of the PartialDistribution class
class PartialDistribution;

/**
 *  @class
 *  @brief Probability for a given partial distribution
 *
 *  The Probability class is used to provide the probability
 *  that the associated distribution can be used at a given incident
 *  energy.
 *
 *  See ENDF102, section 5 for more information.
 */
class ENDFTK_PYTHON_EXPORT Probability : protected TabulationRecord {

  friend PartialDistribution;

  /**
   *  @brief Return the constant that defines the upper energy
   *         limit E - U for the secondary particle's energy E'
   */
  double U() const { return TabulationRecord::C1(); }

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] lf              the type of the underlying distribution
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] probabilities   the probability values
   *  @param[in] u               the energy limit constant U (default = 0.0)
   */
  Probability( long lf,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& energies,
               std::vector< double >&& probabilities,
               double u = 0.0 )
    try : TabulationRecord( u, 0.0, 0, lf,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( probabilities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing a partial probability" );
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
  Probability( Iterator& begin, const Iterator& end,
               long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing a partial probability" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution law (the LF flag)
   */
  int LF() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the distribution law (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the probability values
   */
  auto P() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the probability values
   */
  auto probabilities() const { return this->P(); }

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
