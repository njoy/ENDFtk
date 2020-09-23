template<>
class Type< 2, 151 > : protected BaseWithoutMT< Type< 2, 151 > > {

public:

  using Isotope = resonanceParameters::Isotope;

private:

  friend BaseWithoutMT< Type< 2, 151 > >;

  /* fields */
  std::vector< Isotope > isotopes_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/src/verifyNIS.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/2/151/src/ctor.hpp"

  /**
   *  @brief Return the MT number of the section
   */
  static constexpr int sectionNumber() { return 151; }

  /**
   *  @brief Return the number NIS of isotopes
   */
  unsigned int numberIsotopes() const { return this->NIS(); }

  /**
   *  @brief Return the number NIS of isotopes
   */
  unsigned int NIS() const { return this->isotopes_.size(); }

  /**
   *  @brief Return the isotopes defined in the section
   */
  auto isotopes() const { return ranges::view::all( this->isotopes_ ); }

  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::AWR;

  #include "ENDFtk/section/2/151/src/print.hpp"
  #include "ENDFtk/section/2/151/src/NC.hpp"
};
