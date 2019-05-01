/**
 *  @class
 *  @brief Base class for Legendre or tabulated angular distributions
 */
template < typename Distribution >
class AngularDistributions : protected InterpolationSequenceRecord< Distribution > {
protected:

  /* constructor */
  #include "ENDFtk/section/4/AngularDistributions/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the number interpolation regions for the incident energies
   */
  long NR() const { return InterpolationSequenceRecord< Distribution >::tab2().NR(); }

  /**
   *  @brief Return the number of incident energy values for which angular
   *         distributions are given
   */
  long NE() const { return InterpolationSequenceRecord< Distribution >::tab2().NZ(); }

  /**
   *  @brief Return the number of incident energy values for which angular
   *         distributions are given
   */
  long numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const {

    return InterpolationSequenceRecord< Distribution >::tab2().interpolants();
  }

  /**
   *  @brief Return the interpolation region boundaries for the incident 
   *         energy axis
   */
  auto boundaries() const {

    return InterpolationSequenceRecord< Distribution >::tab2().boundaries();
  }

  /**
   *  @brief Return the angular distributions (one for each incident energy)
   */
  auto angularDistributions() const {

    return InterpolationSequenceRecord< Distribution >::records();
  }

  using InterpolationSequenceRecord< Distribution >::NC;
  using InterpolationSequenceRecord< Distribution >::print;
};
