/**
 *  @class
 *  @brief Base class for Legendre or tabulated angular distributions
 */
template < typename Records >
class ENDFTK_PYTHON_EXPORT AngularDistributions :
  protected InterpolationSequenceRecord< Records > {

protected:

  /* constructor */
  #include "ENDFtk/section/4/AngularDistributions/src/ctor.hpp"

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
