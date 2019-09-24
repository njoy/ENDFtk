template<>
class Type< 2, 151 > : protected BaseWithoutMT< Type< 2, 151 > > {

  friend BaseWithoutMT< Type< 2, 151 > >;

public:

  std::vector< resonanceParameters::Isotope > isotopes;
  #include "ENDFtk/section/2/151/src/readIsotopes.hpp"
  #include "ENDFtk/section/2/151/src/ctor.hpp"

  #include "ENDFtk/section/2/151/src/print.hpp"
  #include "ENDFtk/section/2/151/src/NC.hpp"

  /**
   *  @brief Return the MT number of the section
   */
  static constexpr int sectionNumber() { return 151; }

  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::AWR;
};
