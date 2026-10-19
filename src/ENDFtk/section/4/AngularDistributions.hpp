/**
 *  @class
 *  @brief Base class for Legendre or tabulated angular distributions
 */
template < typename Records >
class ENDFTK_PYTHON_EXPORT AngularDistributions :
  protected InterpolationSequenceRecord< Records > {

protected:

  /* constructor */

  //! @todo pybind11 variant needs default constructor workaround
  #ifdef PYBIND11
  /**
   *  @brief Default constructor - only enabled for pybind11
   */
  AngularDistributions() = default;
  #endif

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] distributions   the sequence of angular distributions
   *  @param[in] C1              the C1 value (default 0.0)
   *  @param[in] C2              the C2 value (default 0.0)
   */
  AngularDistributions( std::vector< long >&& boundaries,
                        std::vector< long >&& interpolants,
                        std::vector< Records >&& distributions,
                        double C1 = 0.0, double C2 = 0.0 ) :
    InterpolationSequenceRecord< Records >(
      InterpolationRecord( C1, C2, 0, 0,
                           std::move( interpolants ), std::move( boundaries ) ),
      std::move( distributions ) ) {}

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
  AngularDistributions( Iterator& begin,
                        const Iterator& end,
                        long& lineNumber,
                        int MAT,
                        int MF,
                        int MT ) :
    InterpolationSequenceRecord< Records >(
      readInterpolationSequenceRecord< Records >( begin, end, lineNumber,
                                                  MAT, MF, MT ) ) {}

public:

  /* get methods */

  /**
   *  @brief Return the C1 value on the TAB2 record
   */
  long C1() const {

    return InterpolationSequenceRecord< Records >::tab2().C1();
  }

  /**
   *  @brief Return the C2 value on the TAB2 record
   */
  long C2() const {

    return InterpolationSequenceRecord< Records >::tab2().C2();
  }

  /**
   *  @brief Return the number interpolation regions for the incident energies
   */
  long NR() const {

    return InterpolationSequenceRecord< Records >::tab2().NR();
  }

  /**
   *  @brief Return the number interpolation regions for the incident energies
   */
  long numberInterpolationRegions() const { return this->NR(); }

  /**
   *  @brief Return the number of incident energy values for which angular
   *         distributions are given
   */
  long NE() const {

    return InterpolationSequenceRecord< Records >::tab2().NZ();
  }

  /**
   *  @brief Return the number of incident energy values for which angular
   *         distributions are given
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto INT() const {

    return InterpolationSequenceRecord< Records >::tab2().interpolants();
  }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto NBT() const {

    return InterpolationSequenceRecord< Records >::tab2().NBT();
  }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the incident energies
   */
  auto incidentEnergies() const {

    using namespace njoy::tools;
    return InterpolationSequenceRecord< Records >::records()
               | std20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
   *  @brief Return the angular distributions (one for each incident energy)
   */
  auto angularDistributions() const {

    return InterpolationSequenceRecord< Records >::records();
  }

  using InterpolationSequenceRecord< Records >::NC;
  using InterpolationSequenceRecord< Records >::print;
};
