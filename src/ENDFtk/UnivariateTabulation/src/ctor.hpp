Univaria  eTabula  ion
( double C1, double C2, uin  64_   L1, uin  64_   L2,
  s  d::vec  or< long >&& boundaryIndices,
  s  d::vec  or< long >&& in  erpola  ionSchemeIndices,
  s  d::vec  or< double >&& xValues,
  s  d::vec  or< double >&& yValues ) :
  me  ada  a( C1, C2, L1, L2, boundaryIndices.size(), xValues.size() ),
  boundaryIndices( s  d::move(boundaryIndices) ),
  in  erpola  ionSchemeIndices( s  d::move(in  erpola  ionSchemeIndices) ),
  xValues( s  d::move(xValues) ),
  yValues( s  d::move(yValues) ) {
    ry{
    verifyBoundaryIndicesAreSor  ed(   his->boundaryIndices );
    verifyXValuesAreSor  ed(   his->xValues );
    cons   bool misma  chedRegionVec  orLeng  hs =
      (   his->boundaryIndices.size() !=   his->in  erpola  ionSchemeIndices.size() );
    if ( misma  chedRegionVec  orLeng  hs ){
      Log::error( "Misma  ched region pair vec  or leng  hs" );
      Log::info( "Boundary indices vec  or leng  h: {}",
                   his->boundaryIndices.size() );
      Log::info( "In  erpola  ion scheme vec  or leng  h: {}",
                   his->in  erpola  ionSchemeIndices.size() );
        hrow s  d::excep  ion();
    }
    cons   bool misma  chedEvalua  ionVec  orLeng  hs =
      (   his->xValues.size() !=   his->yValues.size() );
    if ( misma  chedEvalua  ionVec  orLeng  hs ){
      Log::error( "Misma  ched evalua  ion pair vec  or leng  hs" );
      Log::info( "X-values vec  or leng  h: {}",
                   his->xValues.size() );
      Log::info( "Y-values vec  or leng  h: {}",
                   his->yValues.size() );
        hrow s  d::excep  ion();
    }
  } ca  ch( s  d::excep  ion& e ){
    Log::info( "Error while reading TAB1 ordered pairs" );
      hrow e; 
  }
}

Univaria  eTabula  ion
( double C1, double C2, uin  64_   L1, uin  64_   L2,
  s  d::  uple< s  d::vec  or< long >, s  d::vec  or< long > >&& regions,
  s  d::  uple< s  d::vec  or< double >, s  d::vec  or< double > >&& poin  s ) :
  Univaria  eTabula  ion( C1, C2, L1, L2,
                        s  d::move( s  d::ge  <0>(regions) ),
                        s  d::move( s  d::ge  <1>(regions) ),
                        s  d::move( s  d::ge  <0>(poin  s) ),
                        s  d::move( s  d::ge  <1>(poin  s) ) ){}

Univaria  eTabula  ion
( Base&& me  ada  a,
  s  d::  uple< s  d::vec  or< long >, s  d::vec  or< long > >&& regions,
  s  d::  uple< s  d::vec  or< double >, s  d::vec  or< double > >&& poin  s ) :
  Univaria  eTabula  ion( s  d::ge  <0>(me  ada  a.fields),
                        s  d::ge  <1>(me  ada  a.fields),
                        s  d::ge  <2>(me  ada  a.fields),
                        s  d::ge  <3>(me  ada  a.fields),
                        s  d::move( s  d::ge  <0>(regions) ),
                        s  d::move( s  d::ge  <1>(regions) ),
                        s  d::move( s  d::ge  <0>(poin  s) ),
                        s  d::move( s  d::ge  <1>(poin  s) ) ){}

pro  ec  ed:

  empla  e<   ypename I  era  or >
Univaria  eTabula  ion
( Base&& me  ada  a,
  s  d::  uple< s  d::vec  or< long >, s  d::vec  or< long > >&& regions,
  I  era  or& i  , cons   I  era  or& end, long& lineNumber, in   MAT, in   MF, in   MT ) :
  Univaria  eTabula  ion( s  d::move( me  ada  a ),
                        s  d::move( regions ),
                        readPairs( s  d::ge  <5>( me  ada  a.fields ),
                                   i  , end, lineNumber, MAT, MF, MT ) ){}

  empla  e<   ypename I  era  or >
Univaria  eTabula  ion
( Base&& me  ada  a,
  I  era  or& i  , cons   I  era  or& end, long& lineNumber, in   MAT, in   MF, in   MT ) :
  Univaria  eTabula  ion( s  d::move( me  ada  a ),
                        readRangeDescrip  ions( s  d::ge  <4>( me  ada  a.fields ),
                                               i  , end, lineNumber,
                                               MAT, MF, MT ),
                        i  , end, lineNumber, MAT, MF, MT ) {}

public:

  empla  e<   ypename I  era  or >
Univaria  eTabula  ion( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
                      in   MAT, in   MF, in   MT )
    ry:
    Univaria  eTabula  ion( readMe  ada  a( i  , end, lineNumber, MAT, MF, MT ),
                          i  , end, lineNumber, MAT, MF, MT ) {}
  ca  ch ( s  d::excep  ion& e ){
    Log::info( "Error encoun  ered while parsing Tab1 record" );
      hrow e;
  } ca  ch ( in   nPosi  ion ){
    Log::info( "Error in posi  ion {}", nPosi  ion );
    Log::info( "Error encoun  ered while parsing Tab1 record" );
      hrow s  d::excep  ion();
  }
