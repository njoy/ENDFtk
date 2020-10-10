/**
 *  @class
 *  @brief Base class for Legendre or tabulated angular distributions
 */
template < typename Records >
class AngularDistributions :
  protected InterpolationSequenceRecord< Records > {

protected:

  /* constructor */
  #include "ENDFtk/section/4/AngularDistributions/src/ctor.hpp"

public:

  /* get methods */

  /**
   *  @brief Return the number interpolation regions for the incident energies
   */
  long NR() const {

    return InterpolationSequenceRecord< Records >::tab2().NR();
  }

  /**
   *  @brief Return the number of incident energy values for which angular
   *         distributions are given
   */
  long NE() const {

    return InterpolationSequenceRecord< Records >::tab2().NZ();
  }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  auto interpolants() const {

    return InterpolationSequenceRecord< Records >::tab2().interpolants();
  }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  auto boundaries() const {

    return InterpolationSequenceRecord< Records >::tab2().boundaries();
  }

  /**
   *  @brief Return the incident energies
   */
  auto incidentEnergies() const {

    return InterpolationSequenceRecord< Records >::records()
               | ranges::view::transform(
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
