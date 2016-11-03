friend HeadRecord&
asHead( StructureDivision& record ){
  return static_cast< HeadRecord& >( record );
}
  
friend HeadRecord&
asHead( double expectedZA,
        double expectedAtomicWeightRatio,
        StructureDivision& record ){
  auto& head = asHead( record );
  if ( head.ZA() != expectedZA ){
    LOG(WARNING) <<
      "Encountered ZA does not meet expectations for head record with:"
                 << "\n  Material number (MAT) = " <<  head.MAT()
                 << "\n  File number (MF) = " <<  head.MF()
                 << "\n  Section number (MT) = " <<  head.MT();
    LOG(INFO) << "Expected ZA: " << expectedZA;
    LOG(INFO) << "Encountered ZA: " << head.ZA();
  }
  if ( head.AWR() != expectedAtomicWeightRatio ){
    LOG(WARNING) <<
      "Encountered atomic weight ratio does not meet expectations for head record with:"
                 << "\n  Material number (MAT) = " <<  head.MAT()
                 << "\n  File number (MF) = " <<  head.MF()
                 << "\n  Section number (MT) = " <<  head.MT();
    LOG(INFO) << "Expected atomic weight ratio: "
              << expectedAtomicWeightRatio;
    LOG(INFO) << "Encountered atomic weight ratio: " << head.AWR();
  }
  return head;
}
  
friend const HeadRecord&
asHead( const StructureDivision& record ){
  return static_cast< const HeadRecord& >( record );
}
  
friend const HeadRecord&
asHead( double expectedZA,
        double expectedAtomicWeightRatio,
        const StructureDivision& record ){
  auto& head = asHead( record );
  if ( head.ZA() != expectedZA ){
    LOG(WARNING) <<
      "Encountered ZA does not meet expectations for head record with:"
                 << "\n  Material number (MAT) = " <<  head.MAT()
                 << "\n  File number (MF) = " <<  head.MF()
                 << "\n  Section number (MT) = " <<  head.MT();
    LOG(INFO) << "Expected ZA: " << expectedZA;
    LOG(INFO) << "Encountered ZA: " << head.ZA();
  }
  if ( head.AWR() != expectedAtomicWeightRatio ){
    LOG(WARNING) <<
      "Encountered atomic weight ratio does not meet expectations for head record with:"
                 << "\n  Material number (MAT) = " <<  head.MAT()
                 << "\n  File number (MF) = " <<  head.MF()
                 << "\n  Section number (MT) = " <<  head.MT();
    LOG(INFO) << "Expected atomic weight ratio: "
              << expectedAtomicWeightRatio;
    LOG(INFO) << "Encountered atomic weight ratio: " << head.AWR();
  }
  return head;
}
