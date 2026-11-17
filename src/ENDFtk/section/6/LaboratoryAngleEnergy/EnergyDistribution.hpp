/**
 *  @class
 *  @brief The secondary energy distribution associated to a given cosine
 *         value
 *
 *  See ENDF102, section 12.2.8 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyDistribution : protected TabulationRecord {

  /* constructor */

  /**
   *  @brief Private constructor
   */
  EnergyDistribution( TabulationRecord&& table ) :
    TabulationRecord( std::move( table ) ) {};

public:
  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] cosine           the cosine value of the secondary energy
   *                              distribution
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] energies         the energy values
   *  @param[in] probabilities    the probability values
   */
  EnergyDistribution( double cosine,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< double >&& energies,
                      std::vector< double >&& probabilities )
    try : EnergyDistribution(
            TabulationRecord( 0.0, cosine, 0, 0, std::move( boundaries ),
                              std::move( interpolants ), std::move( energies ),
                              std::move( probabilities ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing energy distribution data "
                 "(LAW=7)" );
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
  EnergyDistribution( Iterator& it, const Iterator& end,
                      long& lineNumber,
                      int MAT, int MF, int MT )
    try : EnergyDistribution( TabulationRecord( it, end, lineNumber,
                                                MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading energy distribution data "
                 "(LAW=7)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the number of interpolation regions for the secondary energy
   */
  long NRP() const { return TabulationRecord::NR(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  long NEP() const { return TabulationRecord::NP(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  long numberOutgoingEnergies() const { return this->NEP(); }

  /**
   *  @brief Return the cosine value for this secondary energy distribition
   */
  double MU() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the cosine value for this secondary energy distribition
   */
  double cosine() const { return this->MU(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto EP() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto energies() const { return this->EP(); }

  /**
   *  @brief Return the probabilities
   */
  auto F() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the probabilities
   */
  auto probabilities() const { return  this->F(); }

  using TabulationRecord::NR;
  using TabulationRecord::numberInterpolationRegions;
  using TabulationRecord::NP;
  using TabulationRecord::numberPoints;
  using TabulationRecord::INT;
  using TabulationRecord::interpolants;
  using TabulationRecord::NBT;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
