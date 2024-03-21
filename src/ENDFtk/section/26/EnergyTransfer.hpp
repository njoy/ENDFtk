/**
 *  @class
 *  @brief Only energy transfer during electro-atomic excitation or
 *         bremsstrahlung is given (LAW=8)
 *
 *  The EnergyTransfer class is used to represent law=8 data of MF26.
 *
 *  See ENDF102, section 26.2.3 for more information.
 */
class ENDFTK_PYTHON_EXPORT EnergyTransfer : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/26/EnergyTransfer/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the LAW flag for energy transfer data only
   */
  static constexpr int LAW() { return 8; }

  /**
   *  @brief Return the energies
   */
  auto E() const { return TabulationRecord::x(); }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the energy transfer values
   */
  auto ET() const { return TabulationRecord::y(); }

  /**
   *  @brief Return the energy transfer values
   */
  auto energyTransferValues() const { return this->ET(); }

  using TabulationRecord::NP;
  using TabulationRecord::NR;
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
