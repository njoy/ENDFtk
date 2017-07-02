class StructureDivision {
public:
  /* convenience typedefs */
  using Base =
    record::Base< record::Real, record::Real,
                  record::Integer<11>, record::Integer<11>,
                  record::Integer<11>, record::Integer<11> >;
  
  using Tail = record::Tail;

  /* fields */
  Base base;
  Tail tail;
  
  StructureDivision( double C1, double C2, long L1, long L2, long N1, long N2,
                     int MAT, int MF, int MT ) :
    base( C1, C2, L1, L2, N1, N2 ),
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
	Log::error( "Illegal material number (MAT) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
	Log::info( "Material numbers are greater than or equal to -1" );
	Log::info( "Material number: {}", this->tail.material() );
        throw std::exception();
      }
      if (tail.file() < 0){
        std::advance( fieldPosition, 4 );
	Log::error( "Illegal file number (MF) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
	Log::info( "File numbers are greater than or equal to 0" );
	Log::info( "File number: {}", this->tail.file() );
        throw std::exception();
      }
      if (tail.section() < 0){
        std::advance( fieldPosition, 6 );
	Log::error( "Illegal section number (MT) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber - 1 );
	Log::info( "Section numbers are greater than or equal to 0" );
	Log::info( "Section number: {}", this->tail.section() );
        throw std::exception();
      }    
    } catch ( int fieldNumber ){
      auto fieldPosition = std::next( begin, 66 );
      switch (fieldNumber) {
      case 6 :
	Log::error( "Illegal material number (MAT) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
        break;
      case 7 :
        std::advance( fieldPosition, 4 );
	Log::error( "Illegal file number (MF) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
        break;
      case 8 :
        std::advance( fieldPosition, 6 );
	Log::error( "Illegal section number (MT) encountered" );
        utility::echoErroneousLine( begin, fieldPosition, end, lineNumber );
        break;
      default:
        break;
      }
      throw std::exception();
    } catch ( std::exception& e ){
      Log::info( "Error encountered while constructing structure division" );
      throw e;
    }

  bool isHead(){
    return this->tail.section() && this->tail.file() && this->tail.material();
  }
  
  bool isSendPermissive(){
    const static Base empty(0.0, 0.0, 0, 0, 0, 0);
    return ( this->base == empty ) && ( this->tail.section() == 0 );
  };

  bool isSend(){
    return this->isSendPermissive()
           && this->tail.file()
           && ( this->tail.material() > 0 );
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

inline StructureDivision sectionEndRecord( int MAT, int MF ){
  if ( MAT < 1 ){
    Log::error( "Illegal material number (MAT) specified in SEND record" );
    Log::info( "SEND records require a material number greater than 0" );
    Log::info( "Specified material number: {}", MAT );
    throw std::exception();
  }
  if ( MF < 1 ){
    Log::error( "Illegal file number (MF) specified in SEND record" );
    Log::info( "SEND records require a file number greater than 0" );
    Log::info( "Specified file number: {}", MF );
    throw std::exception();
  }
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, MF, 0 );
}

inline StructureDivision SEND( int MAT, int MF ){
  return sectionEndRecord( MAT, MF );
}

inline StructureDivision fileEndRecord( int MAT ){ 
  if ( MAT < 1 ){
    Log::error( "Illegal material number (MAT) specified in FEND record" );
    Log::info( "FEND records require a material number greater than 0" );
    Log::info( "Specified material number: {}", MAT );
    throw std::exception();
  }
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, 0, 0 );
}

inline StructureDivision FEND( int MAT ){ return fileEndRecord( MAT ); }

inline StructureDivision materialEndRecord(){
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0 );
}

inline StructureDivision MEND(){ return materialEndRecord(); }

inline StructureDivision tapeEndRecord(){
  return StructureDivision( 0.0, 0.0, 0, 0, 0, 0, -1, 0, 0 );
}

inline StructureDivision TEND(){ return tapeEndRecord(); }
