/**
 *  @class
 *  @brief An isotope with resonance energy ranges
 *
 *  The Isotope class is used to represent an isotope for which resonance
 *  energy ranges (resolved or unresolved) from MF2/MT151 are given.
 *
 *  See ENDF102, section 2.1 for more information.
 */
class Isotope {

  /* fields */
  double zai_;
  double abn_;
  bool lfw_;
  std::vector< ResonanceRange > ranges_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/Isotope/src/readScatteringRadius.hpp"
  #include "ENDFtk/section/2/151/Isotope/src/readParameters.hpp"
  #include "ENDFtk/section/2/151/Isotope/src/readRanges.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/Isotope/src/ctor.hpp"

  /* get methods */

  /**
   *  @brief Return the ZA identifier of the isotope
   */
  double ZAI() const { return this->zai_; }

  /**
   *  @brief Return the abundance of the isotope
   */
  double ABN() const { return this->abn_; }

  /**
   *  @brief Return the abundance of the isotope
   */
  double abundance() const { return this->ABN(); }

  /**
   *  @brief Return the average fission flag
   */
  int LFW() const { return this->lfw_; }

  /**
   *  @brief Return the average fission flag
   */
  int averageFissionWidthFlag() const { return this->LFW(); }

  /**
   *  @brief Return the number of resonance ranges for this isotope
   */
  unsigned int NER() const { return this->ranges_.size(); }

  /**
   *  @brief Return the number of resonance ranges for this isotope
   */
  unsigned int numberResonanceRanges() const { return this->NER(); }

  /**
   *  @brief Return the resonance ranges for this isotope
   */
  auto resonanceRanges() const {

    return ranges::cpp20::views::all( this->ranges_ );
  }

  #include "ENDFtk/section/2/151/Isotope/src/print.hpp"
  #include "ENDFtk/section/2/151/Isotope/src/NC.hpp"
};
