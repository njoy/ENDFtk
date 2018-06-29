/**
 *  @class
 *  @brief Incoherent elastic scattering law
 *
 *  The IncoherentElastic class is used to represent the incoherent elastic
 *  scattering law of MF7/MT2.
 *
 *  See ENDF102, section 7.2 for more information.
 */
class IncoherentElastic : protected TabulationRecord {

public:

  /* constructor */
  #include "ENDFtk/section/7/2/IncoherentElastic/src/ctor.hpp"

  /**
   *  @brief Return the LTHR flag for coherent elastic scattering
   */
  static constexpr int LTHR() { return 2; }

  /* get methods */
  double SB() const { return TabulationRecord::C1(); }
  using TabulationRecord::NP;
  using TabulationRecord::NR;
  auto temperatures() const { return TabulationRecord::x(); }
  auto debyeWallerValues() const { return TabulationRecord::y(); }
  using TabulationRecord::interpolants;
  using TabulationRecord::boundaries;
  using TabulationRecord::NC;
  using TabulationRecord::print;
};
