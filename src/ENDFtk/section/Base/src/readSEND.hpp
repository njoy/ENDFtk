template< typename Iterator >
static void readSEND
( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF ){
  try{
    auto division =
    if( not division.isSend() ){
      LOG(ERROR) << "SEND record is misformatted.";
      utility::findLineBegin( it );
      utility::echoErroneousLine( it, it, end, lineNumber - 1 );
      throw std::exception();
    }

    if( MAT != division.tail.MAT() ){
      LOG(ERROR) << "Incorrect Material number (MAT) in SEND record.";
      LOG(INFO)  << "Expected MAT = " << MAT;
      LOG(INFO)  << "Encountered MAT = " << division.tail.MAT();
      throw std::exception();
    }
      
    if( MF != division.tail.MF() ){
      LOG(ERROR) << "Incorrect File number (MF) in SEND record";
      LOG(INFO)  << "Expected MF = " << MF;
      LOG(INFO)  << "Encountered MF = " << division.tail.MF();
      throw std::exception();
    }
  } catch ( std::exception& e ){
    LOG(INFO) << "There was a problem reading the SEND record.";
    throw e;
  }
}
