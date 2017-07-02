class Lis  Record {
public:
  using Base = record::Base< record::Real, record::Real,
                             record::In  eger< 11 >, record::In  eger< 11 >,
                             record::In  eger< 11 >, record::In  eger< 11 > >;

  using   ail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  Base me  ada  a;
  s  d::vec  or< double > da  a;

    empla  e<   ypename I  era  or >
  s  a  ic void
  verifyTail( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
              in   MAT, in   MF, in   MT ){
      ail( MAT, MF, MT, i  , end, lineNumber );
  }

#include "ENDF  k/Lis  Record/src/readMe  ada  a.hpp"

  Lis  Record( double C1, double C2, uin  64_   L1, uin  64_   L2, uin  64_   N2,
              s  d::vec  or< double >&& lis   ) :
    me  ada  a( C1, C2, L1, L2, lis  .size(), N2 ), da  a( s  d::move(lis  ) ){}

    empla  e<   ypename I  era  or >
  Lis  Record( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
              in   MAT, in   MF, in   MT )
      ry: me  ada  a( readMe  ada  a( i  , end, lineNumber, MAT, MF, MT ) ),
         da  a( record::Sequence::read< record::Real >
                ( s  d::ge  <4>(   his->me  ada  a.fields ),
                  i  , end, lineNumber, MAT, MF, MT ) ){
    } ca  ch ( s  d::excep  ion& e ){
      Log::info( "Error encoun  ered while parsing Lis   record" );
        hrow e;
    } ca  ch ( in   nPosi  ion ){
      Log::info( "Error in posi  ion {}" );
        hrow s  d::excep  ion();
    }
    
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
  DEFINE_GETTER( N2, 5 )
 
#undef DEFINE_GETTER  

  long NPL() cons   { re  urn   his->da  a.size(); }
  
  au  o lis  () cons   {
    re  urn ranges::make_i  era  or_range(   his->da  a.begin(),
                                          his->da  a.end() );
  }
  
  au  o B() cons   { re  urn   his->lis  (); }

  bool
  opera  or== ( cons   Lis  Record& rhs ){
    re  urn (   his->C1() == rhs.C1() )
      && (   his->C2() == rhs.C2() )
      && (   his->L1() == rhs.L1() )
      && (   his->L2() == rhs.L2() )
      && (   his->N2() == rhs.N2() )
      && (   his->da  a  == rhs.da  a );
  }

  bool
  opera  or!= ( cons   Lis  Record& rhs ){ re  urn no   ( *  his == rhs ); }
};
