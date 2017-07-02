class Base {
public:
  /* fields */
  int sectionNo;
  int ZA_;
  double atomicWeightRatio_;
  
  /* ctor */
#include "ENDFtk/section/Base/src/ctor.hpp"

  /* methods */
  int& MT() { return this->sectionNo; }
  
  int MT() const { return const_cast< Base* >( this )->MT(); }

  int& ZA() { return this->ZA_; }
  
  int ZA() const { return const_cast< Base* >( this )->ZA(); }

  double& AWR() { return this->atomicWeightRatio_; }
  
  double AWR() const { return const_cast< Base* >( this )->AWR(); }
  
  double& atomicWeightRatio() { return this->AWR(); }
  
  double atomicWeightRatio() const { return this->AWR(); }

#include "ENDFtk/section/Base/src/readSEND.hpp"

};
