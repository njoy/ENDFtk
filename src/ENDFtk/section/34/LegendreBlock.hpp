/**
 *  @class
 *  @brief A LegendreBlock block (subsubsection) given in an MF34 covariance section
 *
 *  The LegendreBlock class is used to represent a subsubsection in
 *  an ENDF MF34 section, which represents a covariance of a given
 *  Legendre coefficient to another.
 *
 *  See ENDF102, section 34.2 for more information.
 */
class LegendreBlock {

  /* fields */
  int order_;
  int order1_;
  int lct_;
  std::vector< ExplicitCovariance > ni_;

  /* auxiliary functions */
  // intentionally taken from MF33
  #include "ENDFtk/section/33/ReactionBlock/src/readNI.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/34/LegendreBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the first Legendre order
   */
  int L() const { return this->order_; }

  /**
   *  @brief Return the first Legendre order
   */
  int firstLegendreOrder() const { return this->L(); }

  /**
   *  @brief Return the second Legendre order
   */
  int L1() const { return this->order1_; }

  /**
   *  @brief Return the second Legendre order
   */
  int secondLegendreOrder() const { return this->L1(); }

  /**
   *  @brief Return the coordinate system
   */
  int LCT() const { return this->lct_; }

  /**
   *  @brief Return the coordinate system
   */
  int coordinateSystem() const { return this->LCT(); }

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int NI() const { return this->ni_.size(); }

  /**
   *  @brief Return the number of NI-type data blocks
   */
  int numberDataBlocks() const { return this->NI(); }

  /**
   *  @brief Return the NI-type subsubsections
   */
  auto data() const {

    return ranges::cpp20::views::all( this->ni_ );
  }

  // #include "ENDFtk/section/33/ReactionBlock/src/NC.hpp"
  // #include "ENDFtk/section/33/ReactionBlock/src/print.hpp"
};
