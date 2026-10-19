/**
 *  @class
 *  @brief Discrete two-body scattering data for secondary particles (LAW=2)
 *
 *  The DiscreteTwoBodyScattering class is used to represent the two-body angular
 *  distribution law=2 data of MF26. It is similar to the MF6 law=2, but only
 *  supports the LANG=11 to 15 options.
 *
 *  See ENDF102, section 26.2.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscreteTwoBodyScattering {

public:

  #include "ENDFtk/section/6/DiscreteTwoBodyScattering/TabulatedDistribution.hpp"

private:

  /* fields */

  InterpolationSequenceRecord< TabulatedDistribution > data_;

  /* auxiliary functions */

  /* constructor */

  /**
   *  @brief Private constructor
   */
  DiscreteTwoBodyScattering( InterpolationRecord&& interpolation,
                             std::vector< TabulatedDistribution >&& sequence ) :
    data_( std::move( interpolation ), std::move( sequence ) ) {}

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  DiscreteTwoBodyScattering( InterpolationRecord&& interpolation,
                             Iterator& begin,
                             const Iterator& end,
                             long& lineNumber,
                             int MAT,
                             int MF,
                             int MT ) :
    DiscreteTwoBodyScattering( std::move( interpolation ),
                               readSequence< TabulatedDistribution >(
                                 begin, end, lineNumber,
                                 MAT, MF, MT, interpolation.NZ() ) ) {}

public:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  DiscreteTwoBodyScattering() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries     the interpolation range boundaries
   *  @param[in] interpolants   the interpolation types for each range
   *  @param[in] sequence       the data for each incident energy value
   */
  DiscreteTwoBodyScattering( std::vector< long >&& boundaries,
                             std::vector< long >&& interpolants,
                             std::vector< TabulatedDistribution >&& sequence )
    try : DiscreteTwoBodyScattering(
            InterpolationRecord( 0.0, 0.0, 0, 0,
                                 std::move( boundaries ),
                                 std::move( interpolants ) ),
            std::move( sequence ) ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete two body "
                 "scattering distribution data (LAW=2)" );
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
  DiscreteTwoBodyScattering ( Iterator& begin,
                              const Iterator& end,
                              long& lineNumber,
                              int MAT,
                              int MF,
                              int MT )
    try : DiscreteTwoBodyScattering(
            InterpolationRecord( begin, end, lineNumber, MAT, MF, MT ),
            begin, end, lineNumber, MAT, MF, MT ) {}
    catch ( std::exception& e ) {

      Log::info( "Encountered error while constructing discrete two body "
                 "scattering distribution data (LAW=2)" );
      throw;
    }

  /* methods */

  /**
   *  @brief Return the LAW flag
   */
  static constexpr int LAW() { return 2; }

  /**
   *  @brief Return the number of interpolation regions on the incident
   *         energy axis
   */
  long NR() const { return this->data_.tab2().NR(); }

  /**
   *  @brief Return the number of interpolation regions on the incident
   *         energy axis
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
   *  @brief Return the distributions, one for each incident energy
   */
  auto distributions() const { return this->data_.records(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    using namespace njoy::tools;
    return this->distributions()
               | std20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto INT() const { return this->data_.tab2().INT(); }

  /**
   *  @brief Return interpolation type for each range on the incident
   *         energy grid
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto NBT() const { return this->data_.tab2().NBT(); }

  /**
   *  @brief Return interpolation boundaries for the incident energy grid
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the number of lines in this MF6 component
   */
  long NC() const { return this->data_.NC(); }

  // taken from MF6

  /**
   *  @brief Print the component
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
