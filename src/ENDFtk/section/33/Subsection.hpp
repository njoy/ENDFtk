/**
 *  @class
 *  @brief A Subsection (subsection) given in an MF33 covariance section
 *
 *  The Subsection class is used to represent a subsection in
 *  an ENDF MF33 section, which represents a covariance of the reaction
 * cross section (MT) relative to another reaction (MF1/MT1).
 *
 *  See ENDF102, section 33.2 for more information.
 */
class Subsection {

  /* fields */
  double xmf1_;
  double xlfs1_;
  int mat1_;
  int mt1_;
  std::vector< NCType > nc_;
  std::vector< NIType > ni_;

  /* auxiliary functions */


public:

  /* constructor */
  #include "ENDFtk/section/33/Subsection/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the file number for the second cross section
   */
  double XMF1() const { return this->xmf1_; }

  /**
   *  @brief Return the file number for the second cross section
   */
  double secondFileNumber() const { return this->XMF1(); }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  double XLFS1() const { return this->xlfs1_; }

  /**
   *  @brief Return the final excited state for the second cross section
   */
  double secondFinalExcitedState() const { return this->XLFS1(); }

  /**
   *  @brief Return the material number for the second cross section
   */
  double MAT1() const { return this->mat1_; }

  /**
   *  @brief Return the material number for the second cross section
   */
  double secondMaterialNumber() const { return this->MAT1(); }

  /**
   *  @brief Return the section number for the second cross section
   */
  double MT1() const { return this->mt1_; }

  /**
   *  @brief Return the section number for the second cross section
   */
  double secondSectionNumber() const { return this->MT1(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  double NK() const { return this->nc_.size(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  double numberNCType() const { return this->NK(); }

  /**
   *  @brief Return the number of NC-type subsubsections
   */
  double NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type subsubsections
   */
  double numberNIType() const { return this->NI(); }

  /**
   *  @brief Return the NC-type subsubsections
   */
  auto componentsNC() const {

    return ranges::cpp20::views::all( this->nc_ );
  }

  /**
   *  @brief Return the NC-type subsubsections
   */
  auto componentsNI() const {

    return ranges::cpp20::views::all( this->ni_ );
  }

  // #include "ENDFtk/section/33/Subsection/src/NC.hpp"
  // #include "ENDFtk/section/33/Subsection/src/print.hpp"
};
