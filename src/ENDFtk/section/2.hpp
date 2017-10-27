template<>
class Type< 2 > : protected Base {
public:

  std::vector< resonanceParameters::Isotope > isotopes;
  #include "ENDFtk/section/2/src/readIsotopes.hpp"
  #include "ENDFtk/section/2/src/ctor.hpp"

  using Base::MT;
  using Base::sectionNumber;
  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
};
