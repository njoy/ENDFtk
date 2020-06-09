class GendfBase : protected Base {

protected:
  /* fields */
  std::map< int, GendfDataRecord > data_;
  int num_legendre_;
  int num_sigma0_;
  int lrflag_;
  int num_groups_;
  double temperature_;

  /* methods */
  #include "ENDFtk/section/GendfBase/src/populateData.hpp"

public:
  /* constructor */
  #include "ENDFtk/section/GendfBase/src/ctor.hpp"

  /* getters */
  int legendreOrder() const { return num_legendre_-1; }
  int numLegendre() const { return num_legendre_; }
  int numSigma0() const { return num_sigma0_; }
  int breakupFlag() const { return lrflag_; }
  int numGroups() const { return num_groups_; }
  double temperature() const { return temperature_; }
  const auto& dataRecords() const { return data_; }

  /* getters inherited from Base */
  using Base::MT;
  using Base::ZA;
  using Base::AWR;
  using Base::atomicWeightRatio;
  
};
