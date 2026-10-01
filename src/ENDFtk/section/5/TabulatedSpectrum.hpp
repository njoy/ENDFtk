/**
 *  @class
 *  @brief Arbitrary tabulated energy distribution (LF=1)
 *
 *  The TabulatedSpectrum class is used to represent the case in which
 *  the energy distribution in an ENDF MF5 section is represented entirely
 *  as a tabulated function.
 *
 *  The tabulated g(E->E') functions are given as tabulated g(E') functions for
 *  fixed E values.
 *
 *  See ENDF102, section 5.1.1.1 and 5.2.1 for more information.
 */
class ENDFTK_PYTHON_EXPORT TabulatedSpectrum {

public:

  #include "ENDFtk/section/5/TabulatedSpectrum/OutgoingEnergyDistribution.hpp"

private:

  /* members */

  InterpolationSequenceRecord< OutgoingEnergyDistribution > data_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Constructor
   *
   *  @param[in] sequence   the interpolation sequence record
   */
  TabulatedSpectrum(
      InterpolationSequenceRecord< OutgoingEnergyDistribution >&& sequence ) :
    data_( std::move( sequence ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  TabulatedSpectrum() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] distributions   the sequence of outgoing energy distributions
   */
  TabulatedSpectrum( std::vector< long >&& boundaries,
                     std::vector< long >&& interpolants,
                     std::vector< OutgoingEnergyDistribution >&& distributions )
    try : TabulatedSpectrum(
              InterpolationSequenceRecord< OutgoingEnergyDistribution >(
                  InterpolationRecord( 0.0, 0.0, 0, 0,
                                       std::move( boundaries ),
                                       std::move( interpolants ) ),
                  std::move( distributions ) ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while constructing a tabulated energy "
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
  TabulatedSpectrum( Iterator& begin,
                     const Iterator& end,
                     long& lineNumber,
                     int MAT,
                     int MF,
                     int MT )
    try : TabulatedSpectrum(
              readInterpolationSequenceRecord< OutgoingEnergyDistribution >(
                  begin, end, lineNumber, MAT, MF, MT ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Error encountered while reading a tabulated energy "
                 "distribution (LF=1)" );
      throw;
    }

  /* get methods */

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  static constexpr int LF() { return 1; }

  /**
   *  @brief Return the distribution type (the LF flag)
   */
  int LAW() const { return this->LF(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident energy
   *         grid
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation ranges on the incident energy
   *         grid
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incoming energy values
   */
  long NE() const { return this->data_.tab2().NZ(); }

  /**
   *  @brief Return the number of incoming energy values
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the outgoing energy distributions
   */
  auto outgoingDistributions() const {

    return this->data_.records();
  }

  /**
   *  @brief Return the incoming energies
   */
  auto incidentEnergies() const {

    using namespace njoy::tools;
    return this->outgoingDistributions()
             | std20::views::transform(
                 [] ( const auto& entry )
                    { return entry.incidentEnergy(); } ); }

  /**
   *  @brief Return interpolation type for each range on the incoming
   *         energy grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return interpolation type for each range on the incoming
   *         energy grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the incoming
   *         energy grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return interpolation boundaries for the incoming
   *         energy grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the number of lines in this MF5 component
   */
  long NC() const { return this->data_.NC(); }

  /** 
   *  @brief Print this MF5 component
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
