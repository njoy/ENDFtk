
#include "ENDFtk/implementation/SectionBase.hpp"

ENDFtk::implementation::SectionBase::SectionBase( const HEAD& head, 
                                                  int MAT, int MF )
  : MT_(head.MT()), 
    ZA_(head.ZA()), 
    atomicWeightRatio_(head.atomicWeightRatio() )
{ 
  if( MAT != head.MAT() ){
    LOG(ERROR) << "Incorrect Material number (MAT).";
    LOG(INFO) << "Expected MAT=" << MAT
              << ". Got MAT=" << head.MAT();
    throw std::exception();
  }
  if( MF != head.MF() ){
    LOG(ERROR) << "Incorrect File number (MF).";
    LOG(INFO) << "Expected MF=" << MF
              << ". Got MF=" << head.MF();
    throw std::exception();
  }

}
