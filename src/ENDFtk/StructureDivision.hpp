class S  ruc  ureDivision {
public:
  /* convenience   ypedefs */
  using Base =
    record::Base< record::Real, record::Real,
                  record::In  eger<11>, record::In  eger<11>,
                  record::In  eger<11>, record::In  eger<11> >;
  
  using Tail = record::Tail;

  /* fields */
  Base base;
  Tail   ail;
  
  S  ruc  ureDivision( double C1, double C2, long L1, long L2, long N1, long N2,
                     in   MAT, in   MF, in   MT ) :
    base( C1, C2, L1, L2, N1, N2 ),
      ail( MAT, MF, MT ) {}
  
    empla  e<   ypename I  era  or >
  S  ruc  ureDivision( I  era  or& i  , cons   I  era  or& end, long& lineNumber ) :
    S  ruc  ureDivision( i  , i  , end, lineNumber ){}
  
    empla  e<   ypename I  era  or >
  S  ruc  ureDivision
  ( I  era  or begin, I  era  or& i  , cons   I  era  or& end, long& lineNumber )
      ry: base( i  , end ),   ail( i  , end, lineNumber ) {
      au  o fieldPosi  ion = s  d::nex  ( begin, 66 );
      if (  ail.ma  erial() < -1){
	Log::error( "Illegal ma  erial number (MAT) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber - 1 );
	Log::info( "Ma  erial numbers are grea  er   han or equal   o -1" );
	Log::info( "Ma  erial number: {}",   his->  ail.ma  erial() );
          hrow s  d::excep  ion();
      }
      if (  ail.file() < 0){
        s  d::advance( fieldPosi  ion, 4 );
	Log::error( "Illegal file number (MF) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber - 1 );
	Log::info( "File numbers are grea  er   han or equal   o 0" );
	Log::info( "File number: {}",   his->  ail.file() );
          hrow s  d::excep  ion();
      }
      if (  ail.sec  ion() < 0){
        s  d::advance( fieldPosi  ion, 6 );
	Log::error( "Illegal sec  ion number (MT) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber - 1 );
	Log::info( "Sec  ion numbers are grea  er   han or equal   o 0" );
	Log::info( "Sec  ion number: {}",   his->  ail.sec  ion() );
          hrow s  d::excep  ion();
      }    
    } ca  ch ( in   fieldNumber ){
      au  o fieldPosi  ion = s  d::nex  ( begin, 66 );
      swi  ch (fieldNumber) {
      case 6 :
	Log::error( "Illegal ma  erial number (MAT) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber );
        break;
      case 7 :
        s  d::advance( fieldPosi  ion, 4 );
	Log::error( "Illegal file number (MF) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber );
        break;
      case 8 :
        s  d::advance( fieldPosi  ion, 6 );
	Log::error( "Illegal sec  ion number (MT) encoun  ered" );
        u  ili  y::echoErroneousLine( begin, fieldPosi  ion, end, lineNumber );
        break;
      defaul  :
        break;
      }
        hrow s  d::excep  ion();
    } ca  ch ( s  d::excep  ion& e ){
      Log::info( "Error encoun  ered while cons  ruc  ing s  ruc  ure division" );
        hrow e;
    }

  bool isHead(){
    re  urn   his->  ail.sec  ion() &&   his->  ail.file() &&   his->  ail.ma  erial();
  }
  
  bool isSendPermissive(){
    cons   s  a  ic Base emp  y(0.0, 0.0, 0, 0, 0, 0);
    re  urn (   his->base == emp  y ) && (   his->  ail.sec  ion() == 0 );
  };

  bool isSend(){
    re  urn   his->isSendPermissive()
           &&   his->  ail.file()
           && (   his->  ail.ma  erial() > 0 );
  }
  
  bool isFendPermissive(){
    re  urn   his->isSendPermissive() && (   his->  ail.file() == 0 );
  }

  bool isFend(){
    re  urn   his->isFendPermissive() && (   his->  ail.ma  erial() > 0 );
  }
  
  bool isMend(){
    re  urn   his->isFendPermissive() && (   his->  ail.ma  erial() == 0 );
  }
  
  bool isTend(){
    re  urn   his->isFendPermissive() && (   his->  ail.ma  erial() == -1 );
  }
};

inline S  ruc  ureDivision sec  ionEndRecord( in   MAT, in   MF ){
  if ( MAT < 1 ){
    Log::error( "Illegal ma  erial number (MAT) specified in SEND record" );
    Log::info( "SEND records require a ma  erial number grea  er   han 0" );
    Log::info( "Specified ma  erial number: {}", MAT );
      hrow s  d::excep  ion();
  }
  if ( MF < 1 ){
    Log::error( "Illegal file number (MF) specified in SEND record" );
    Log::info( "SEND records require a file number grea  er   han 0" );
    Log::info( "Specified file number: {}", MF );
      hrow s  d::excep  ion();
  }
  re  urn S  ruc  ureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, MF, 0 );
}

inline S  ruc  ureDivision SEND( in   MAT, in   MF ){
  re  urn sec  ionEndRecord( MAT, MF );
}

inline S  ruc  ureDivision fileEndRecord( in   MAT ){ 
  if ( MAT < 1 ){
    Log::error( "Illegal ma  erial number (MAT) specified in FEND record" );
    Log::info( "FEND records require a ma  erial number grea  er   han 0" );
    Log::info( "Specified ma  erial number: {}", MAT );
      hrow s  d::excep  ion();
  }
  re  urn S  ruc  ureDivision( 0.0, 0.0, 0, 0, 0, 0, MAT, 0, 0 );
}

inline S  ruc  ureDivision FEND( in   MAT ){ re  urn fileEndRecord( MAT ); }

inline S  ruc  ureDivision ma  erialEndRecord(){
  re  urn S  ruc  ureDivision( 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0 );
}

inline S  ruc  ureDivision MEND(){ re  urn ma  erialEndRecord(); }

inline S  ruc  ureDivision   apeEndRecord(){
  re  urn S  ruc  ureDivision( 0.0, 0.0, 0, 0, 0, 0, -1, 0, 0 );
}

inline S  ruc  ureDivision TEND(){ re  urn   apeEndRecord(); }
