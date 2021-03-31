#ifndef NJOY_ENDFTK_SECTION_15
#define NJOY_ENDFTK_SECTION_15

// system includes
#include <variant>
#include <vector>

// other includes
#include "range/v3/view/all.hpp"
#include "range/v3/view/transform.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section{

template<>
class Type< 15 > : protected Base {

public:

  #include "ENDFtk/section/5/TabulatedSpectrum.hpp" // LF=1

  using LF1 = TabulatedSpectrum;

  /** @typedef Distribution
   *  @brief A secondary particle energy distribution of MF5
   */
  using Distribution = TabulatedSpectrum; // LF=1
  #include "ENDFtk/section/5/Probability.hpp"
//
//  #include "ENDFtk/section/5/PartialDistribution.hpp"
//
//private:
//
//  /* fields */
//  std::vector< PartialDistribution > partials_;
//
//  /* auxiliary functions */
//  #include "ENDFtk/section/5/src/verifyNK.hpp"
//
//public:
//
//  /* constructor */
//  #include "ENDFtk/section/5/src/ctor.hpp"
//
//  /* methods */
//
//  /**
//   *  @brief Return the number NK of subsections with partial distributions
//   */
//  int NK() const { return this->partials_.size(); }
//
//  /**
//   *  @brief Return the number NK of subsections with partial distributions
//   */
//  int numberPartialDistributions() const { return this->NK(); }
//
//  /**
//   *  @brief Return the partial distributions defined in this section
//   */
//  auto partialDistributions() const {
//
//    return ranges::view::all( this->partials_ );
//  }
//
//  #include "ENDFtk/section/5/src/NC.hpp"
//  #include "ENDFtk/section/5/src/print.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::ZA;
  using Base::atomicWeightRatio;
  using Base::AWR;
};

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
