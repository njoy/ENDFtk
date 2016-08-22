SectionSkeleton_t&
sectionNumber( int sectionNo ){
  try{
    return this->sectionMap.at( sectionNo );
  } catch( std::out_of_range& o ){
    LOG(ERROR) << "Requested section number (MT) does not"
               << " correspond to a stored section skeleton";
    LOG(INFO)  << "Requested section number: " << sectionNo;
    LOG(INFO)  << "File number of queried file skeleton: "
               << this->fileNumber();
    throw o;
  }   
}
