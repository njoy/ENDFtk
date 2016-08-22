#ifndef ENDFTK_IMPLEMENTATION_STRUCTUREDIVISION_HPP
#define ENDFTK_IMPLEMENTATION_STRUCTUREDIVISION_HPP

class ENDFtk::implementation::StructureDivision {
public:
  using Base =
    ENDFtk::implementation::record::Base
    < ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Integer<11>,
      ENDFtk::implementation::record::Integer<11>,
      ENDFtk::implementation::record::Integer<11>,
      ENDFtk::implementation::record::Integer<11> >;

  using Tail = ENDFtk::implementation::record::Tail;

  Base base;
  Tail tail;

  StructureDivision( double C1, double C2, long L1, long L2, long N1, long N2,
                     int MAT, int MF, int MT ) :
    base( C1, C2, L1, L2, N1, N2),
    tail( MAT, MF, MT ) {}

  template< typename Iterator >
  StructureDivision( Iterator& it, const Iterator& end, long& lineNumber ) :
    StructureDivision( it, it, end, lineNumber ){}
  
  template< typename Iterator >
  StructureDivision
    ( Iterator begin, Iterator& it, const Iterator& end, long& lineNumber )
  try: base( it, end ), tail( it, end, lineNumber ) {
    auto fieldPosition = std::next( begin, 66 );
    if (tail.material() < -1){
      LOG(ERROR) << "Illegal material number (MAT) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
      LOG(INFO)  << "Material numbers are greater than or equal to -1";
      LOG(INFO)  << "Material number: " << this->tail.material();
      throw std::exception();
    }
    if (tail.file() < 0){
      std::advance( fieldPosition, 4 );
      LOG(ERROR) << "Illegal file number (MF) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
      LOG(INFO)  << "File numbers are greater than or equal to 0";
      LOG(INFO)  << "File number: " << this->tail.file();
      throw std::exception();
    }
    if (tail.section() < 0){
      std::advance( fieldPosition, 6 );
      LOG(ERROR) << "Illegal section number (MT) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
      LOG(INFO)  << "Section numbers are greater than or equal to 0";
      LOG(INFO)  << "Section number: " << this->tail.section();
      throw std::exception();
    }    
  } catch ( int fieldNumber ){
    auto fieldPosition = std::next( begin, 66 );
    switch (fieldNumber) {
    case 6 :
      LOG(ERROR) << "Illegal material number (MAT) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
      break;
    case 7 :
      std::advance( fieldPosition, 4 );
      LOG(ERROR) << "Illegal file number (MF) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
      break;
    case 8 :
      std::advance( fieldPosition, 6 );
      LOG(ERROR) << "Illegal section number (MT) encountered";
      utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
      break;
    default:
      break;
    }
    throw std::exception();
  } catch ( std::exception& e ){
    LOG(INFO) << "Error encountered while constructing structure division";
    throw e;
  }

  bool isHead(){
    return this->tail.section() && this->tail.file() && this->tail.material();
  }
  
  bool isSendPermissive(){
    const static Base empty(0.0, 0.0, 0, 0, 0, 0);
    return (this->base == empty) && ( this->tail.section() == 0 );
  };

  bool isSend(){
    return this->isSendPermissive()
           && this->tail.file() && ( this->tail.material() > 0 );
  }
  
  bool isFendPermissive(){
    return this->isSendPermissive() && ( this->tail.file() == 0 );
  }

  bool isFend(){
    return this->isFendPermissive() && ( this->tail.material() > 0 );
  }
  
  bool isMend(){
    return this->isFendPermissive() && ( this->tail.material() == 0 );
  }
  
  bool isTend(){
    return this->isFendPermissive() && ( this->tail.material() == -1 );
  }
};

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::sectionEndRecord( int MAT, int MF ){
  if ( ( MAT < 1 ) ){
    LOG(ERROR) << "Illegal material number (MAT) specified in SEND record";
    LOG(INFO) << "SEND records require a material number greater than 0";
    LOG(INFO) << "Specified material number: " << MAT;
    throw std::exception();
  }
  if ( ( MF < 1 ) ){
    LOG(ERROR) << "Illegal file number (MF) specified in SEND record";
    LOG(INFO) << "SEND records require a file number greater than 0";
    LOG(INFO) << "Specified file number: " << MF;
    throw std::exception();
  }
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, MF, 0 );
}

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::SEND( int MAT, int MF ){
  return sectionEndRecord( MAT, MF );
}

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::fileEndRecord( int MAT ){ 
  if ( ( MAT < 1 ) ){
    LOG(ERROR) << "Illegal material number (MAT) specified in FEND record";
    LOG(INFO) << "FEND records require a material number greater than 0";
    LOG(INFO) << "Specified material number: " << MAT;
    throw std::exception();
  }
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, 0, 0 );
}

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::FEND( int MAT ){ return fileEndRecord( MAT ); }

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::materialEndRecord(){
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0 );
}

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::MEND(){ return materialEndRecord(); }

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::tapeEndRecord(){
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, -1, 0, 0 );
}

inline ENDFtk::implementation::StructureDivision
ENDFtk::implementation::TEND(){ return tapeEndRecord(); }

#endif
