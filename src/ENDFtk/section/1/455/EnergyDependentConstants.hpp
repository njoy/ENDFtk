/**
 *  @class
 *  @brief Energy dependent decay constants for delayed neutron precursor
 *         families (LDG = 1)
 *
 *  See ENDF102, section 1.3 for more information.
 */
class EnergyDependentConstants :
  protected InterpolationSequenceRecord< DecayConstants > {

  /* auxiliary functions */
  #include "ENDFtk/section/1/455/EnergyDependentConstants/src/verify.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/1/455/EnergyDependentConstants/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the type of decay constants
   */
  static constexpr int LDG() { return 1; }

  /**
   *  @brief Return the type of decay constants
   */
  int type() const { return this->LDG(); }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int NNF() const { return this->records()[0].NNF();; }

  /**
   *  @brief Return the number of delayed neutron precursors
   */
  int numberPrecursors() const { return this->NNF(); }

  /**
   *  @brief Return the number of interpolation regions for the incident
   *         energies
   */
  long NR() const { return InterpolationSequenceRecord::tab2().NR(); }

  /**
   *  @brief Return the number of incident energy values
   */
  long NE() const { return InterpolationSequenceRecord::tab2().NZ(); }

  /**
   *  @brief Return the interpolants for the incident energy axis
   */
  AllRange< long > interpolants() const {

    return InterpolationSequenceRecord::tab2().interpolants();
  }

  /**
   *  @brief Return the interpolation region boundaries for the incident
   *         energy axis
   */
  AllRange< long > boundaries() const {

    return InterpolationSequenceRecord::tab2().boundaries();
  }

  /**
   *  @brief Return the decay contants
   */
  AllRange< DecayConstants > constants() const {

    return this->records();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const {

    return this->constants()
               | ranges::cpp20::views::transform(
                     [] ( const auto& record )
                        { return record.incidentEnergy(); } );
  }

  /**
  *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->E(); }

  using InterpolationSequenceRecord::NC;
  using InterpolationSequenceRecord::print;
};
