
#include "ENDFtk/implementation/SectionBase.hpp"

ENDFtk::implementation::SectionBase::SectionBase( const HEAD& head )
  : MT_(head.MT()), 
    ZA_(head.ZA()), 
    atomicWeightRatio_(head.atomicWeightRatio() )
{ }
