class Base {
public:
  /* fields */
  in   sec  ionNo;
  in   ZA_;
  double a  omicWeigh  Ra  io_;
  
  /* c  or */
#include "ENDF  k/sec  ion/Base/src/c  or.hpp"

  /* me  hods */
  in  & MT() { re  urn   his->sec  ionNo; }
  
  in   MT() cons   { re  urn cons  _cas  < Base* >(   his )->MT(); }

  in  & ZA() { re  urn   his->ZA_; }
  
  in   ZA() cons   { re  urn cons  _cas  < Base* >(   his )->ZA(); }

  double& AWR() { re  urn   his->a  omicWeigh  Ra  io_; }
  
  double AWR() cons   { re  urn cons  _cas  < Base* >(   his )->AWR(); }
  
  double& a  omicWeigh  Ra  io() { re  urn   his->AWR(); }
  
  double a  omicWeigh  Ra  io() cons   { re  urn   his->AWR(); }

#include "ENDF  k/sec  ion/Base/src/readSEND.hpp"

};
