/**
 *  @class
 *  @brief The angular distributions associated to a given incident energy value
 *
 *  See ENDF102, section 12.2.8 for more information.
 */
class ENDFTK_PYTHON_EXPORT AngularDistribution :
  protected InterpolationSequenceRecord< EnergyDistribution > {

public:

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] energy           the incident energy
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the secondary energy distributions
   */
  AngularDistribution(
      double energy,
      std::vector< long >&& boundaries,
      std::vector< long >&& interpolants,
      std::vector< EnergyDistribution >&& distributions )
    try : InterpolationSequenceRecord(
            InterpolationRecord( 0.0, energy, 0, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( distributions ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing angular distribution data "
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
  AngularDistribution( Iterator& it, const Iterator& end,
                       long& lineNumber, int MAT, int MF, int MT )
    try : InterpolationSequenceRecord(
            readInterpolationSequenceRecord< EnergyDistribution >(
              it, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading angular distribution data "
                 "(LAW=7)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the number of interpolation regions for the cosines
   */
  long NR() const { return InterpolationSequenceRecord::tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions for the cosines
   */
  long NRM() const { return this->NR(); }

  /**
   *  @brief Return the number of interpolation regions for the cosines
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of cosine values
   */
  long NMU() const { return InterpolationSequenceRecord::tab2().NZ(); }

  /**
   *  @brief Return the number of cosine values
   */
  long numberCosines() const { return this->NMU(); }

  /**
   *  @brief Return the incident energy value
   */
  double E() const {

    return InterpolationSequenceRecord::tab2().C2();
  }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const {

    return this->E();
  }

  /**
   *  @brief Return the interpolants for the cosine axis
   */
  auto INT() const { return InterpolationSequenceRecord::tab2().INT(); }

  /**
   *  @brief Return the interpolants for the cosine axis
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation region boundaries for the cosine axis
   */
  auto NBT() const { return InterpolationSequenceRecord::tab2().NBT(); }

  /**
   *  @brief Return the interpolation region boundaries for the cosine axis
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the cosines for this incident energy value
   */
  auto MU() const {

    using namespace njoy::tools;
    return InterpolationSequenceRecord::records()
               | std20::views::transform(
                     [] ( const auto& record )
                        { return record.cosine(); } );
  }

  /**
   *  @brief Return the cosines for this incident energy value
   */
  auto cosines() const { return this->MU(); }

  /**
   *  @brief Return the energy distributions for this incident energy value
   */
  auto energyDistributions() const {

    return InterpolationSequenceRecord::records();
  }

  using InterpolationSequenceRecord::NC;
  using InterpolationSequenceRecord::print;
};
