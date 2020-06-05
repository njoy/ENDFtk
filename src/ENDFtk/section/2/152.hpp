template<>
class Type< 2, 152 > : protected BaseWithoutMT< Type< 2, 152 > > {

  friend BaseWithoutMT< Type< 2, 152 > >;

  /* fields */
  bool lssf_;
  int interpolation_;
  ListRecord data_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ENDFtk/section/2/152/src/ctor.hpp"

  /**
   *  @brief Return the MT number of the section
   */
  static constexpr int sectionNumber() { return 152; }

  /**
   *  @brief Return the self-shielding only flag
   */
  bool LSSF() const { return this->lssf_; }

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const { return this->interpolation_; }

  /**
   *  @brief Return the temperature
   */
  auto TEMZ() const { return this->data_.C1(); }

  /**
   *  @brief Return the temperature
   */
  auto temperature() const { return this->TEMZ(); }

  /**
   *  @brief Return the number of reactions (normally 5)
   */
  auto NREAC() const { return this->data_.L1(); }

  /**
   *  @brief Return the number of reactions (normally 5)
   */
  auto numberReactions() const { return this->NREAC(); }

  /**
   *  @brief Return the number of dilution or sigma zero values
   */
  auto NSIGZ() const { return this->data_.L2(); }

  /**
   *  @brief Return the number of dilution or sigma zero values
   */
  auto numberDilutions() const { return this->NSIGZ(); }

  /**
   *  @brief Return the dilution or sigma zero values
   */
  auto SIGZ() const {

    return this->data_.list()
             | ranges::view::take_exactly( this->NSIGZ() );
  }

  /**
   *  @brief Return the dilution or sigma zero values
   */
  auto dilutions() const { return this->SIGZ(); }

  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::AWR;

  #include "ENDFtk/section/2/152/src/print.hpp"
  #include "ENDFtk/section/2/152/src/NC.hpp"
};
