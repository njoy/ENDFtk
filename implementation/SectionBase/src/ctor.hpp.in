SectionBase
( const HEAD& head, int MAT, int MF ) :
  sectionNo( head.MT() ), 
  ZA_( head.ZA() ), 
  atomicWeightRatio_( head.atomicWeightRatio() ) { 
  if( MAT != head.MAT() ){
    LOG(ERROR) << "Incorrect Material number (MAT).";
    LOG(INFO)  << "Expected MAT = " << MAT;
    LOG(INFO)  << "Encountered MAT =" << head.MAT();
    throw std::exception();
  }
  if( MF != head.MF() ){
    LOG(ERROR) << "Incorrect File number (MF).";
    LOG(INFO)  << "Expected MF = " << MF;
    LOG(INFO)  << "Encountered MF =" << head.MF();
    throw std::exception();
  }
}
