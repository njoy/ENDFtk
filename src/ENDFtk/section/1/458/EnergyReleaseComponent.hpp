/**
 *  @class
 *  @brief A tabulated fission energy release component
 *
 *  See ENDF102, section 1.5 for more information.
 */
class EnergyReleaseComponent : protected TabulationRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/EnergyReleaseComponent/src/verify.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/458/EnergyReleaseComponent/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the primary evaluation flag (true/false)
   */
  bool LDRV() const { return TabulationRecord::L1() == 1 ? false : true; }

  /**
   *  @brief Return the primary evaluation flag (true/false)
   */
  bool primaryEvaluationFlag() const { return this->LDRV(); }

  /**
   *  @brief Return the index for the fission energy release component
   */
  int IFC() const { return TabulationRecord::L2(); }

  /**
   *  @brief Return the index for the fission energy release component
   */
  int componentIndex() const { return this->IFC(); }

  /**
   *  @brief Return the incident energy values
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the incident energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the fission energy release values
   */
  auto EIFC() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the fission energy release values
   */
  auto qValues() const { return this->EIFC(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
