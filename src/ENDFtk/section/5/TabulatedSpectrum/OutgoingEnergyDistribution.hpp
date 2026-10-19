/**
 *  @class
 *  @brief Outgoing energy distribution for a fixed value of E
 *
 *  The OutgoingDistribution class is used to represent the outgoing energy
 *  distribution for a fixed value of E from an ENDF MF5 section.
 *
 *  See ENDF102, section 5.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT OutgoingEnergyDistribution :
    protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] incident        the incident energy value
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the outgoing energy values
   *  @param[in] probabilities   the probability values
   */
  OutgoingEnergyDistribution( double incident,
                              std::vector< long >&& boundaries,
                              std::vector< long >&& interpolants,
                              std::vector< double >&& energies,
                              std::vector< double >&& probabilities )
    try : TabulationRecord( 0.0, incident, 0, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( energies ),
                            std::move( probabilities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing an outgoing energy "
                 "distribution (LF=1)" );
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
  OutgoingEnergyDistribution( Iterator& begin, const Iterator& end,
                              long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading an outgoing energy "
                 "distribution (LF=1)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the incident energy value
   */
  auto E() const { return TabulationRecord::C2(); }

  /**
   *  @brief Return the incident energy value
   */
  auto incidentEnergy() const { return this->E(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto EP() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const { return this->EP(); }

  /**
   *  @brief Return the distribution values
   */
  auto G() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the distribution values
   */
  auto probabilities() const { return this->G(); }

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
