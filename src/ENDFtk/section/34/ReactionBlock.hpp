/**
 *  @class
 *  @brief A Reaction block (subsection) given in an MF34 covariance section
 *
 *  The ReactionBlock class is used to represent a subsection in
 *  an ENDF MF34 section, which represents a covariance of the reaction
 * cross section (MT) relative to another reaction (MF1/MT1).
 *
 *  See ENDF102, section 34.2 for more information.
 */
class ENDFTK_PYTHON_EXPORT ReactionBlock {

  /* fields */
  int mt1_;
  int nl_;
  int nl1_;
  std::vector< LegendreBlock > lblocks_;

  #include "ENDFtk/section/34/ReactionBlock/src/readLegendreBlocks.hpp"
  #include "ENDFtk/section/34/ReactionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/34/ReactionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the material number for the second cross section (must be 0)
   */
  static constexpr int MAT1() { return 0; }

  /**
   *  @brief Return the material number for the second cross section (must be 0)
   */
  int secondMaterialNumber() const { return this->MAT1(); }

  /**
   *  @brief Return the section number for the second cross section
   */
  int MT1() const { return this->mt1_; }

  /**
   *  @brief Return the section number for the second cross section
   */
  int secondSectionNumber() const { return this->MT1(); }

  /**
   *  @brief Return the number of Legendre orders of the first cross section
   */
  int NL() const { return this->nl_; }

  /**
   *  @brief Return the number of Legendre orders of the first cross section
   */
  int firstNumberLegendre() const { return this->NL(); }

  /**
   *  @brief Return the number of Legendre orders of the second cross section
   */
  int NL1() const { return this->nl1_; }

  /**
   *  @brief Return the number of Legendre orders of the second cross section
   */
  int secondNumberLegendre() const { return this->NL1(); }

  /**
   *  @brief Return the number of subsubsections (Legendre blocks)
   */
  int NSS() const { return this->lblocks_.size(); }

  /**
   *  @brief Return the number of subsubsections (Legendre blocks)
   */
  int numberLegendreBlocks() const { return this->NSS(); }

  /**
   *  @brief Return the Legendre blocks
   */
  auto legendreBlocks() const {

    using namespace njoy::tools;
    return this->lblocks_ | std20::views::all;
  }

  #include "ENDFtk/section/34/ReactionBlock/src/NC.hpp"
  #include "ENDFtk/section/34/ReactionBlock/src/print.hpp"
};
