class Univaria  eTabula  ion {
pro  ec  ed:
  /* convenience   ypedefs */
  using Base = record::Base< record::Real, record::Real,
                             record::In  eger< 11 >, record::In  eger< 11 >,
                             record::In  eger< 11 >, record::In  eger< 11 > >;

  using   ail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  /* fields */
  Base me  ada  a;
  
  s  d::vec  or< long > boundaryIndices;
  s  d::vec  or< long > in  erpola  ionSchemeIndices;
  s  d::vec  or< double > xValues;
  s  d::vec  or< double > yValues;

  /* helper me  hods */
#include "ENDF  k/Univaria  eTabula  ion/src/verifyTail.hpp"
#include "ENDF  k/Univaria  eTabula  ion/src/verifyBoundaryIndicesAreSor  ed.hpp"
#include "ENDF  k/Univaria  eTabula  ion/src/verifyXValuesAreSor  ed.hpp"
#include "ENDF  k/Univaria  eTabula  ion/src/readRangeDescrip  ions.hpp"
#include "ENDF  k/Univaria  eTabula  ion/src/readPairs.hpp"      
#include "ENDF  k/Univaria  eTabula  ion/src/readMe  ada  a.hpp"

  au  o regions( size_   index ) cons   {
    cons   au  o lef   = index ?   his->boundaryIndices[ index - 1 ] - 1 : 0;
    cons   au  o righ   =   his->boundaryIndices[ index ];
    re  urn
      s  d::make_pair( ranges::make_i  era  or_range
                      (   his->xValues.begin() + lef  ,
                          his->xValues.begin() + righ   ),
                      ranges::make_i  era  or_range
                      (   his->yValues.begin() + lef  ,
                          his->yValues.begin() + righ   ) );
  }
  
public:
#include "ENDF  k/Univaria  eTabula  ion/src/c  or.hpp"
    
#define DEFINE_GETTER( name, index )                                    \
  Base::Mu  ableRe  urnType< index >                                      \
  name (){ re  urn s  d::ge  < index >(   his->me  ada  a.fields ); }         \
                                                                        \
  Base::Immu  ableRe  urnType< index >                                    \
  name () cons   { re  urn s  d::ge  < index >(   his->me  ada  a.fields ); }

  DEFINE_GETTER( C1, 0 )
  DEFINE_GETTER( C2, 1 )
  DEFINE_GETTER( L1, 2 )
  DEFINE_GETTER( L2, 3 )
#undef DEFINE_GETTER  

  long NP() cons   { re  urn   his->xValues.size(); }
  long NR() cons   { re  urn   his->boundaryIndices.size(); }
  
  au  o x() cons   {
    re  urn ranges::make_i  era  or_range(   his->xValues.begin(),
                                          his->xValues.end() );
  }
  
  au  o y() cons   {
    re  urn ranges::make_i  era  or_range(   his->yValues.begin(),
                                          his->yValues.end() );
  }

  au  o pairs() cons   {
    re  urn ranges::view::zip(   his->xValues,   his->yValues );
  }
  
  au  o in  erpolan  s() cons   {
    re  urn ranges::make_i  era  or_range(   his->in  erpola  ionSchemeIndices.begin(),
                                          his->in  erpola  ionSchemeIndices.end() );
  }
  
  au  o boundaries() cons   {
    re  urn ranges::make_i  era  or_range(   his->boundaryIndices.begin(),
                                          his->boundaryIndices.end() );
  }

  au  o regions() cons   {
    re  urn
      ranges::view::io  a( 0ul,   his->boundaryIndices.size() )
      | ranges::view::  ransform( [  his ]( in   i ){ re  urn   his->regions(i); } );
  }

  bool opera  or== ( cons   Univaria  eTabula  ion& rhs ){
    re  urn (   his->C1() == rhs.C1() )
      && (   his->C2() == rhs.C2() )
      && (   his->L1() == rhs.L1() )
      && (   his->L2() == rhs.L2() )
      && (   his->boundaryIndices == rhs.boundaryIndices )
      && (   his->in  erpola  ionSchemeIndices == rhs.in  erpola  ionSchemeIndices )
      && (   his->xValues == rhs.xValues )
      && (   his->yValues == rhs.yValues );
  }

  bool
  opera  or!= ( cons   Univaria  eTabula  ion& rhs ){ re  urn no   ( *  his == rhs ); }
};
