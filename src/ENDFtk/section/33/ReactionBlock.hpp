/**
 *  @class
 *  @brief A Reaction block (subsection) given in an MF33 covariance section
 *
 *  The ReactionBlock class is used to represent a subsection in
 *  an ENDF MF33 section, which represents a covariance of the reaction
 *  cross section (MT) relative to another reaction (MF1/MT1).
 *
 *  See ENDF102, section 33.2 for more information.
 */
class ReactionBlock {

  /* fields */
  double xmf1_;
  double xlfs1_;
  int mat1_;
  int mt1_;
  std::vector< DerivedCovariance > nc_;
  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */
  #include "ENDFtk/section/33/ReactionBlock/src/readNC.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/33/ReactionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the file number for the second cross section
   */
  int XMF1() const { return this->xmf1_; }

  /**
   *  @brief Return the file number for the second cross section
   */
  int secondFileNumber() const { return this->XMF1(); }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  int XLFS1() const { return this->xlfs1_; }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  int secondFinalExcitedState() const { return this->XLFS1(); }

  /**
   *  @brief Return the material number for the second cross section
   */
  int MAT1() const { return this->mat1_; }

  /**
   *  @brief Return the material number for the second cross section
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
   *  @brief Return the number of NC-type subsubsections
   */
  int NK() const { return this->nc_.size(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  int numberDerived() const { return this->NK(); }

  /**
   *  @brief Return the number of NI-type subsubsections
   */
  int NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type subsubsections
   */
  int numberExplicit() const { return this->NI(); }

  /**
   *  @brief Return the NC-type subsubsections
   */
  auto derivedCovariances() const {

    return ranges::cpp20::views::all( this->nc_ );
  }

  /**
   *  @brief Return the NI-type subsubsections
   */
  auto explicitCovariances() const {

    return ranges::cpp20::views::all( this->ni_ );
  }

  #include "ENDFtk/section/33/ReactionBlock/src/NC.hpp"
  #include "ENDFtk/section/33/ReactionBlock/src/print.hpp"
};
