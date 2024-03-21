/**
 *  @class
 *  @brief Mixed coherent and incoherent elastic scattering law
 *
 *  The MixedElastic class is used to represent the case where both coherent
 *  and incoherent elastic are used in MF7/MT2.
 *
 *  See ENDF102, section 7.4 for more information.
 */
class ENDFTK_PYTHON_EXPORT MixedElastic {

  /* fields */
  CoherentElastic coherent_;
  IncoherentElastic incoherent_;

public:

  /* constructor */
  #include "ENDFtk/section/7/2/MixedElastic/src/ctor.hpp"

  /**
   *  @brief Return the LTHR flag for mixed elastic scattering
   */
  static constexpr int LTHR() { return 3; }

  /**
   *  @brief Return the LTHR flag for mixed elastic scattering
   */
  int elasticScatteringType() const { return this->LTHR(); }

  /**
   *  @brief Return the coherent elastic scattering data
   */
  const CoherentElastic& coherent() const { return this->coherent_; }

  /**
   *  @brief Return the incoherent elastic scattering data
   */
  const IncoherentElastic& incoherent() const { return this->incoherent_; }

  #include "ENDFtk/section/7/2/MixedElastic/src/NC.hpp"
  #include "ENDFtk/section/7/2/MixedElastic/src/print.hpp"
};
