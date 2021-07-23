/**
 *  @class
 *  @brief NC-Type Sub-subsection with LTY=1,2,3
 *
 *  See ENDF102, section 33.2 for more information.
 */
class DerivedRatioToStandard {

   /* fields */
   int lty_;
   ListRecord list_;

   /* auxiliary functions */
   #include "ENDFtk/section/33/DerivedRatioToStandard/src/verifyLTY.hpp"
   #include "ENDFtk/section/33/DerivedRatioToStandard/src/generateList.hpp"

 public:

  /* constructor */
  #include "ENDFtk/section/33/DerivedRatioToStandard/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the procedure
   */
  int LTY() const { return this->lty_; }

  /**
   *  @brief Return the procedure
   */
  int procedure() const { return this->LTY(); }

  /**
   *  @brief Return the lower energy bound
   */
  int E1() const { return this->list_.C1(); }

  /**
   *  @brief Return the lower energy bound
   */
  int lowerEnergy() const { return this->E1(); }

  /**
   *  @brief Return the upper energy bound
   */
  int E2() const { return this->list_.C2(); }

  /**
   *  @brief Return the upper energy bound
   */
  int upperEnergy() const { return this->E2(); }

  /**
   *  @brief Return the standard's material number
   */
  int MATS() const { return this->list_.L1(); }

  /**
   *  @brief Return the standard's material number
   */
  int standardMaterialNumber() const { return this->MATS(); }

  /**
   *  @brief Return the standard's MT number
   */
  int MTS() const { return this->list_.L2(); }

  /**
   *  @brief Return the standard's MT number
   */
  int standardSectionNumber() const { return this->MTS(); }

  /**
   *  @brief Return the number of energies
   */
  int NEI() const { return this->list_.N2(); }

  /**
   *  @brief Return the number of energies
   */
  int numberEnergies() const { return this->NEI(); }

  /**
   *  @brief Return the standard's MF number
   */
  double XMFS() const { return this->list_.list()[0]; }

  /**
   *  @brief Return the standard's MF number
   */
  double standardFileNumber() const { return this->XMFS(); }

  /**
   *  @brief Return the standard's final excited state
   */
  double XLFSS() const { return this->list_.list()[1]; }

  /**
   *  @brief Return the standard's final excited state
   */
  double standardFinalExcitedState() const { return this->XLFSS(); }

  /**
   *  @brief Return the energies
   */
  auto EI() const {

    return ranges::views::drop_exactly(this->list_.list(), 2)
        | ranges::views::stride(2);
  }

  /**
   *  @brief Return the energies
   */
  auto energies() const { return this->EI(); }

  /**
   *  @brief Return the weights
   */
  auto WEI() const {

    return ranges::views::drop_exactly(this->list_.list(), 3)
        | ranges::views::stride(2);
  }

  /**
   *  @brief Return the coefficients
   */
  auto weights() const { return this->WEI(); }


  #include "ENDFtk/section/33/DerivedRatioToStandard/src/NC.hpp"
  #include "ENDFtk/section/33/DerivedRatioToStandard/src/print.hpp"

};
