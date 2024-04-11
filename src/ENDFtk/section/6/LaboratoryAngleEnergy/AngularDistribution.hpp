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
  #include "ENDFtk/section/6/LaboratoryAngleEnergy/AngularDistribution/src/ctor.hpp"

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

    return InterpolationSequenceRecord::records()
               | ranges::cpp20::views::transform(
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
