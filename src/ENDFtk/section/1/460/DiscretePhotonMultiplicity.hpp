/**
 *  @class
 *  @brief Discrete photon multiplicity data
 *
 *  See ENDF102, section 1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscretePhotonMultiplicity :
  protected TabulationRecord {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] energy            the discrete photon energy
   *  @param[in] lph               the index of the discrete photon
   *  @param[in] boundaries        the interpolation range boundaries
   *  @param[in] interpolants      the interpolation types for each range
   *  @param[in] time              the time values
   *  @param[in] multiplicities    the multiplicity values
   */
  DiscretePhotonMultiplicity( double energy, int lph,
                              std::vector< long >&& boundaries,
                              std::vector< long >&& interpolants,
                              std::vector< double >&& time,
                              std::vector< double >&& multiplicities )
    try : TabulationRecord( energy, 0.0, lph, 0,
                            std::move( boundaries ),
                            std::move( interpolants ),
                            std::move( time ),
                            std::move( multiplicities ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a discrete photon "
                 "multiplicity" );
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
  DiscretePhotonMultiplicity( Iterator& begin, const Iterator& end,
                              long& lineNumber, int MAT, int MF, int MT )
    try : TabulationRecord( begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing a discrete photon "
                 "multiplicity" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the photon energy
   */
  double E() const { return TabulationRecord::C1(); }

  /**
   *  @brief Return the photon energy
   */
  double energy() const { return this->E(); }

  /**
   *  @brief Return the photon index (between 1 and NG)
   */
  int LPH() const { return TabulationRecord::L1(); }

  /**
   *  @brief Return the photon index (between 1 and NG)
   */
  int index() const { return this->LPH(); }

  /**
   *  @brief Return the time values
   */
  auto time() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the time dependent multiplicity values (in units of 1/s)
   */
  auto multiplicities() const { return TabulationRecord::y(); }

  using TabulationRecord::x;
  using TabulationRecord::y;
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
