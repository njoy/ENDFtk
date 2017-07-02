  empla  e<   ypename Zip,   ypename Tuple,
            ypename I  era  or, s  d::size_  ... indices >
s  a  ic void
readPar  ialLine
( uin  64_   nEn  ries, Tuple& i  era  orTuple, I  era  or& i  , cons   I  era  or& end,
  long& lineNumber, in   MAT, in   MF, in   MT,
  s  d::index_sequence< indices... > ){

//au  o incremen   = []( uin  64_   offse  , au  o& i  era  or ){ i  era  or+= offse  ; };
  
  for ( uin  64_   offse   = 0; offse   < nEn  ries; ++offse   ){
    Zip::TupleForma  ::read
      ( i  , end, s  d::ge  < indices >( i  era  orTuple )[offse  ]... );
  }
  
  au  o remainingEn  ries = Zip::  uplesPerRecord - nEn  ries;    
  s  d::  uple<   ypename Zip::   empla  e Type< indices >... > lef  overs;

  while ( remainingEn  ries-- ){
    Zip::TupleForma  ::read( i  , end, s  d::ge  < indices >( lef  overs )... );
    if ( lef  overs != Zip::defaul  Tuple() ){
      Log::error( "Encoun  ered non-defaul   value where none was expec  ed" );
        hrow s  d::excep  ion();
    }
  }
  
  using Gap = disco::Record
              < disco::ColumnPosi  ion< Zip::nPad >, disco::Re  ainCarriage >;

  Gap::read( i  , end );

  verifyTail( i  , end, lineNumber, MAT, MF, MT );
}

