/**
 *  @class
 *  @brief A Level block (subsection) given in an MF40 covariance section
 *
 *  The LevelBlock class is used to represent a subsection in
 *  an ENDF MF40 section, which represents a covariance of radionuclide
 *  production cross sections (MT, XLFS) relative to another reaction
 *  (MF1/MT1/XLFS1).
 *
 *  See ENDF102, section 40.2 for more information.
 */
class LevelBlock {

  /* fields */
  double qm_;
  double qi_;
  int izap_;
  int lfs_;
  std::vector< ReactionBlock > reactions_;

public:

  /* constructor */
  #include "ENDFtk/section/40/LevelBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the mass-difference Q-value
   */
  double QM() const { return this->qm_; }

  /**
   *  @brief Return the mass-difference Q-value
   */
  double massDifferenceQValue() const { return this->QM(); }

  /**
   *  @brief Return the reaction Q-value
   */
  double QI() const { return this->qi_; }

  /**
   *  @brief Return the reaction Q-value
   */
  double reactionQValue() const { return this->QI(); }

  /**
   *  @brief Return the product ZA identifier
   */
  int IZAP() const { return this->izap_; }

  /**
   *  @brief Return the product ZA identifier
   */
  int productIdentifier() const { return this->IZAP(); }

  /**
   *  @brief Return the level number of the product
   */
  int LFS() const { return this->lfs_; }

  /**
   *  @brief Return the level number of the product
   */
  int excitedLevel() const { return this->LFS(); }

  /**
   *  @brief Return the number of reaction blocks
   */
  int NL() const { return this->reactions_.size(); }

  /**
   *  @brief Return the number of reaction blocks
   */
  int numberReactions() const { return this->NL(); }

  /**
   *  @brief Return the reaction blocks
   */
  auto reactionBlocks() const {

    return ranges::cpp20::views::all( this->reactions_ );
  }

  #include "ENDFtk/section/40/LevelBlock/src/NC.hpp"
  #include "ENDFtk/section/40/LevelBlock/src/print.hpp"
};
