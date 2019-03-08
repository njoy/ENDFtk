class Base : public BaseWithoutMT< Base > {

  /* fields */
  int MT_;

public:
  
  /* constructor */
  #include "ENDFtk/section/Base/src/ctor.hpp"

  /* get methods */
  int sectionNumber() const { return this->MT_; }
  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::AWR;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::readSEND;
};
