#ifndef NJOY_ENDFTK_SECTION_12
#define NJOY_ENDFTK_SECTION_12

// system includes
#include <variant>
#include <optional>

// other includes
#include "tools/std20/views.hpp"
#include "tools/std23/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  /**
   *  @class
   *  @brief MF12 - photon production multiplicities and transition probability
   *                arrays
   *
   *  See ENDF102, section 12.2 for more information.
   */
  template<>
  class ENDFTK_PYTHON_EXPORT Type< 12 > : protected Base {

  public:

    #include "ENDFtk/section/12/TotalMultiplicity.hpp"
    #include "ENDFtk/section/12/PartialMultiplicity.hpp"

    #include "ENDFtk/section/12/Multiplicities.hpp"               // LO=1
    #include "ENDFtk/section/12/TransitionProbabilities.hpp"      // LO=2

    using LO1 = Multiplicities;
    using LO2 = TransitionProbabilities;

    /** @typedef PhotonProduction
     *  @brief The photon production multiplicities or transition probabilities
     *         of MF12
     *
     *  This photon production data class is set up as a variant.
     */
    using PhotonProduction =
              std::variant< Multiplicities,                      // LO=1
                            TransitionProbabilities >;           // LO=2

  private:

    /* fields */
    PhotonProduction photon_;

    /* auxiliary functions */
    #include "ENDFtk/section/12/src/readPhotonProduction.hpp"

  public:

    /* constructor */
    #include "ENDFtk/section/12/src/ctor.hpp"

    /* get methods */

    /**
     *  @brief Return the data type for the photon production data
     */
    int LO() const { return this->photon_.index() + 1; }

    /**
     *  @brief Return the data type for the photon production data
     */
    int representation() const { return this->LO(); }

    /**
     *  @brief Return the photon production data
     */
    const PhotonProduction& photonProduction() const { return this->photon_; }

    #include "ENDFtk/section/12/src/NC.hpp"
    #include "ENDFtk/section/12/src/print.hpp"

    using Base::MT;
    using Base::sectionNumber;
    using Base::ZA;
    using Base::targetIdentifier;
    using Base::atomicWeightRatio;
    using Base::AWR;
  };

} // section namespace
} // ENDFtk namespace
} // njoy namespace

#endif
