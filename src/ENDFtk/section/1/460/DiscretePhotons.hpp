/**
 *  @class
 *  @brief A collection of discrete photon multiplicities
 *
 *  See ENDF102, section 1.6 for more information.
 */
class ENDFTK_PYTHON_EXPORT DiscretePhotons {

  /* fields */
  std::vector< DiscretePhotonMultiplicity > photons_;

  /* auxiliary functions */
  #include "ENDFtk/section/1/460/DiscretePhotons/src/verifySize.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/460/DiscretePhotons/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  static constexpr int LO() { return 1; }

  /**
   *  @brief Return the representation type for the delayed photon data
   */
  int representation() const { return this->LO(); }

  /**
   *  @brief Return the number of discrete photons
   */
  int NG() const { return this->photons_.size(); }

  /**
   *  @brief Return the number of discrete photons
   */
  int numberDiscretePhotons() const { return this->NG(); }

  /**
   *  @brief Return the discrete photon data
   */
  auto photons() const {

    using namespace njoy::tools;
    return std20::views::all( this->photons_ );
  }

  #include "ENDFtk/section/1/460/DiscretePhotons/src/NC.hpp"
  #include "ENDFtk/section/1/460/DiscretePhotons/src/print.hpp"
};
