/**
 *  @class
 *  @brief The distributions are given in the E,mu,E' ordering
 *
 *  This distribution provides the E,mu,E' ordering of distributions while
 *  the continuum energy-anle representation (law=1) provides the more
 *  traditional E,E',mu ordering. The reference system is supposed to be the
 *  lab system.
 *
 *  See ENDF102, section 6.2.8 for more information.
 */
class ENDFTK_PYTHON_EXPORT LaboratoryAngleEnergy {
public:

  #include "ENDFtk/section/6/LaboratoryAngleEnergy/EnergyDistribution.hpp"
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution.hpp"

private:
  InterpolationSequenceRecord
    < LaboratoryAngleEnergy::AngularDistribution > data_;

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  LaboratoryAngleEnergy() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the distribitions
   */
  LaboratoryAngleEnergy(
      std::vector< long >&& boundaries,
      std::vector< long >&& interpolants,
      std::vector< AngularDistribution >&& distributions )
    try : data_( InterpolationRecord( 0.0, 0.0, 0, 0,
                                      std::move( boundaries ),
                                      std::move( interpolants ) ),
                                      std::move( distributions ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing laboratory angle energy "
                 "distribution data (LAW=7)" );
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
  LaboratoryAngleEnergy( Iterator& begin,
                         const Iterator& end,
                         long& lineNumber,
                         int MAT,
                         int MF,
                         int MT )
    try : data_(
            readInterpolationSequenceRecord<
              LaboratoryAngleEnergy::AngularDistribution >(
                begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while reading laboratory angle energy "
                 "distribution data (LAW=7)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the distribution type (the LAW flag)
   */
  static constexpr int LAW() { return 7; }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the angular distributions
   */
  auto angularDistributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    using namespace njoy::tools;
    return this->angularDistributions()
               | std20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  /**
   *  @brief Print this MF6 component
   *
   *  @tparam OutputIterator   an output iterator
   *
   *  @param[in] it            the current position in the output
   *  @param[in] MAT           the MAT number
   *  @param[in] MF            the MF number
   *  @param[in] MT            the MT number
   */
  template< typename OutputIterator >
  void print( OutputIterator& it, int MAT, int MF, int MT ) const {

    this->data_.print( it, MAT, MF, MT );
  }
};
