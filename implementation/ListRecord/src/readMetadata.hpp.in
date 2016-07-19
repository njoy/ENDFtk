template< typename Iterator >
static Base
readMetadata( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
  try{
    Base metadata( it, end );
    verifyTail( it, end, lineNumber, MAT, MF, MT );
    if ( std::get<4>( metadata.fields ) < 0 ){
      LOG(ERROR) << "Illegal NPL value encountered";
      LOG(INFO) << "NPL must be greater than or equal to 0";
      LOG(INFO) << "NPL value: " << std::get<4>( metadata.fields );
      throw std::runtime_error("List Record NPL value");
    }
    return metadata;
  } catch (std::exception& e){
    LOG(INFO) << "Error while reading metadata";
    throw e;
  }
}
