FileSkeleton_t&
fileNumber( int fileNo ){
  try{
    return this->fileMap.at( fileNo );
  } catch( std::out_of_range& o ){
    LOG(ERROR) << "Requested file number (MF) does not"
               << " correspond to a stored file skeleton";
    LOG(INFO)  << "Requested file number: " << fileNo;
    LOG(INFO)  << "Material number of queried material skeleton: "
               << this->materialNumber();
    throw o;
  }   
}
