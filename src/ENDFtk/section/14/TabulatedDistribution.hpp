/**
 *  @class
 *  @brief An angular distribution given as a tabulated function.
 *
 *  The TabulatedDistribution class is used to represent the case in which the
 *  angular distribution for a secondary particle at a given incident energy is
 *  is given as a tabulated function.
 *
 *  See ENDF102, section 14.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedDistribution : protected TabulationRecord {

  /* auxiliary functions */

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the incident energy value
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the cosine values
   *  @param[in] probabilities   the probability values
   */
  TabulatedDistribution( double energy,
                         std::vector< long >&& boundaries,
                         std::vector< long >&& interpolants,
                         std::vector< double >&& cosines,
                         std::vector< double >&& probabilities )
    try : TabulationRecord( 0.0, energy, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( cosines ),
                            std::move( probabilities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated angular "
      	         "distribution" );
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
  TabulatedDistribution( Iterator& begin, const Iterator& end,
                         long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a tabulated angular "
      	         "distribution" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double E() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the incident energy for which the angular distribution
   *         is given
   */
  double incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the cosine values
   */
  AllRange< double > MU() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the cosine values
   */
  AllRange< double > cosines() const { return this->MU(); }

  /**
   *  @brief Return the distribution probabilities
   */
  AllRange< double > F() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the distribution probabilities
   */
  AllRange< double > probabilities() const { return this->F(); }

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
