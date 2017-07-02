class HeadRecord;

HeadRecord&
asHead( S  ruc  ureDivision& record );

HeadRecord&
asHead( double expec  edZA,
	double expec  edA  omicWeigh  Ra  io,
	S  ruc  ureDivision& record );

cons   HeadRecord&
asHead( cons   S  ruc  ureDivision& record );

cons   HeadRecord&
asHead( double expec  edZA,
        double expec  edA  omicWeigh  Ra  io,
        cons   S  ruc  ureDivision& record );

class HeadRecord : pro  ec  ed S  ruc  ureDivision {
public:

    empla  e< s  d::size_   index >
  using Mu  ableRe  urnType = Base::Mu  ableRe  urnType< index >;
  
    empla  e< s  d::size_   index >
  using Immu  ableRe  urnType = Base::Immu  ableRe  urnType< index >;

  HeadRecord( double C1, double C2, long L1, long L2, long N1, long N2,
              in   MAT, in   MF, in   MT ) :
  S  ruc  ureDivision( C1, C2, L1, L2, N1, N2, MAT, MF, MT ) {}
  
    empla  e<   ypename I  era  or >
  HeadRecord( I  era  or& i  , cons   I  era  or& end, long& lineNumber )
    : S  ruc  ureDivision(i  , end, lineNumber) { /* Do no  hing */ }

#define DEFINE_BASE_GETTER( name, posi  ion )                            \
  Mu  ableRe  urnType< posi  ion >                                         \
  name(){ re  urn s  d::ge  < posi  ion >(   his->base.fields ); }           \
                                                                        \
  Immu  ableRe  urnType< posi  ion >                                       \
  name() cons   { re  urn s  d::ge  < posi  ion >(   his->base.fields ); }

  DEFINE_BASE_GETTER( ZA, 0 )
  DEFINE_BASE_GETTER( a  omicWeigh  Ra  io, 1 )
  DEFINE_BASE_GETTER( AWR, 1 )
  DEFINE_BASE_GETTER( L1, 2 )
  DEFINE_BASE_GETTER( L2, 3 )
  DEFINE_BASE_GETTER( N1, 4 )
  DEFINE_BASE_GETTER( N2, 5 )

#undef DEFINE_BASE_GETTER
    
#define DEFINE_TAIL_GETTER( name )                                      \
  decl  ype(   ail.name() )                                               \
  name(){ re  urn   his->  ail.name(); }                                   \
                                                                        \
  decl  ype( s  d::declval                                                \
            <   ypename s  d::add_cons                                     \
              < decl  ype(   ail ) >::  ype >().name() )                   \
  name() cons   { re  urn   his->  ail.name(); }                               
  
  DEFINE_TAIL_GETTER( MAT )
  DEFINE_TAIL_GETTER( MF )
  DEFINE_TAIL_GETTER( MT )
  DEFINE_TAIL_GETTER( ma  erial )
  DEFINE_TAIL_GETTER( file )
  DEFINE_TAIL_GETTER( sec  ion )
  
#undef DEFINE_DEFERRED_GETTER

#include "ENDF  k/HeadRecord/src/asHead.hpp"
  
};
