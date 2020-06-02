template<>
class GendfType< 3 > : protected GendfBase {

protected:


public:

  /* constructor */
  #include "ENDFtk/section/Gendf3/src/ctor.hpp"

  /* methods */
  #include "ENDFtk/section/Gendf3/src/getCrossSection.hpp"

  /* inherited from GendfBase */
  using GendfBase::legendreOrder;
  using GendfBase::numLegendre;
  using GendfBase::numSigma0;
  using GendfBase::breakupFlag;
  using GendfBase::numGroups;
  using GendfBase::temperature;

  /* inherited from Base */
  using GendfBase::MT;
  using GendfBase::ZA;
  using GendfBase::AWR;
  using GendfBase::atomicWeightRatio;

};
