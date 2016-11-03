template< typename Iterator >
static Base
readMetadata( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
  try{
    Base metadata( it, end );
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    if ( std::get<4>( metadata.fields ) < 0 ){
      LOG(ERROR) << "Illegal NR value encountered";
      LOG(INFO) <<
        "NR (or number of regions) must be greater than or equal to 0";
      LOG(INFO) << "NR value: " << std::get<4>( metadata.fields );
      throw std::runtime_error("TAB1 Record NR value");
    }
    if ( std::get<5>( metadata.fields ) < 0 ){
      LOG(ERROR) << "Illegal NP value encountered";
      LOG(INFO) <<
        "NP (or number of pairs) must be greater than or equal to 0";
      LOG(INFO) << "NP value: " << std::get<5>( metadata.fields );
      throw std::runtime_error("TAB1 Record NP value");
    }
    return metadata;
  } catch (std::exception& e){
    LOG(INFO) << "Error while reading metadata";
    throw e;
  }
}
