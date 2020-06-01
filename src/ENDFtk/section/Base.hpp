class Base : public BaseWithoutMT< Base > {

  /* fields */
  int MT_;

protected:
  
  /* constructor */
  #include "ENDFtk/section/Base/src/ctor.hpp"

public:

  /* get methods */
  int sectionNumber() const { return this->MT_; }
  using BaseWithoutMT::MT;
  using BaseWithoutMT::ZA;
  using BaseWithoutMT::AWR;
  using BaseWithoutMT::atomicWeightRatio;
  using BaseWithoutMT::readSEND;
};
