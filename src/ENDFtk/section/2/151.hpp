template<>
class Type< 2, 151 > : protected BaseWithoutMT< Type< 2, 151 > > {

public:

  using Isotope = resonanceParameters::Isotope;

private:

  friend BaseWithoutMT< Type< 2, 151 > >;

  /* fields */
  std::vector< Isotope > isotopes_;

  /* auxiliary functions */
  #include "ENDFtk/section/2/151/src/readIsotopes.hpp"
  #include "ENDFtk/section/2/151/src/ctor.hpp"

public:

  /**
   *  @brief Return the MT number of the section
   */
  static constexpr int sectionNumber() { return 151; }

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
