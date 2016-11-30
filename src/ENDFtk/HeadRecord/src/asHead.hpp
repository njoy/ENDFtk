friend HeadRecord&
asHead( StructureDivision& record ){
  return static_cast< HeadRecord& >( record );
}
  
friend HeadRecord&
asHead( double expectedZA,
        double expectedAtomicWeightRatio,
        StructureDivision& record ){
  auto& head = njoy::ENDFtk::asHead( record );
  if ( head.ZA() != expectedZA ){
    Log::warning(
      "Encountered ZA does not meet expectations for head record with:"
      "\n  Material number (MAT) = {}"
      "\n  File number (MF) = {}" 
      "\n  Section number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
    Log::info( "Expected ZA: {}", expectedZA );
    Log::info( "Encountered ZA: {}", head.ZA() );
  }
  if ( head.AWR() != expectedAtomicWeightRatio ){
    Log::warning(
      "Encountered atomic weight ratio does not meet expectations for head record with:"
      "\n  Material number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Section number (MT) = {}",
      head.MAT() , head.MF(),  head.MT() );
    Log::info( "Expected atomic weight ratio: {}", expectedAtomicWeightRatio );
    Log::info( "Encountered atomic weight ratio: {}", head.AWR() );
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
  auto& head = njoy::ENDFtk::asHead( record );
  if ( head.ZA() != expectedZA ){
    Log::warning(
      "Encountered ZA does not meet expectations for head record with:"
      "\n  Material number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Section number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
      
    Log::info( "Expected ZA: {}", expectedZA );
    Log::info( "Encountered ZA: {}", head.ZA() );
  }
  if ( head.AWR() != expectedAtomicWeightRatio ){
    Log::warning(
      "Encountered atomic weight ratio does not meet expectations for head record with:"
      "\n  Material number (MAT) = {}"
      "\n  File number (MF) = {}"
      "\n  Section number (MT) = {}",
      head.MAT(), head.MF(), head.MT() );
    Log::info( "Expected atomic weight ratio: {}", expectedAtomicWeightRatio );
      Log::info( "Encountered atomic weight ratio: {}", head.AWR() );
  }
  return head;
}
