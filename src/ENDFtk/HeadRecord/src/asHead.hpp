friend HeadRecord&
asHead( StructureDivision& record ){
  return static_cast< HeadRecord& >( record );
}
  
friend const HeadRecord&
asHead( const StructureDivision& record ){
  return static_cast< const HeadRecord& >( record );
}
