class Con  rolRecord : pro  ec  ed record::Base< record::Real,
                                              record::Real,
                                              record::In  eger< 11 >,
                                              record::In  eger< 11 >,
                                              record::In  eger< 11 >,
                                              record::In  eger< 11 > > {
public:

  using base = record::Base< record::Real, record::Real,
                             record::In  eger< 11 >, record::In  eger< 11 >,
                             record::In  eger< 11 >, record::In  eger< 11 > >;
  
  using   ail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  Con  rolRecord( double C1, double C2,
                 in  64_   L1, in  64_   L2, in  64_   N1, in  64_   N2 ) :
    base( C1, C2, L1, L2, N1, N2 ){}

    empla  e<   ypename I  era  or >
  Con  rolRecord( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
                 in   MAT, in   MF, in   MT )
      ry: base( i  , end ){
        ail( MAT, MF, MT, i  , end, lineNumber );
    } ca  ch ( s  d::excep  ion& e ) {
      /* TODO error informa  ion here */
        hrow e;
    } ca  ch ( in   fieldNo ){
      --lineNumber;
      /* TODO error informa  ion here */
        hrow s  d::excep  ion();
    }

#define DEFINE_GETTER( name, index )                            \
  Mu  ableRe  urnType< index >                                    \
  name (){ re  urn s  d::ge  < index >(   his->fields ); }          \
                                                                \
  Immu  ableRe  urnType< index >                                  \
  name () cons   { re  urn s  d::ge  < index >(   his->fields ); }

  DEFINE_GETTER( C1, 0 )
  DEFINE_GETTER( C2, 1 )
  DEFINE_GETTER( L1, 2 )
  DEFINE_GETTER( L2, 3 )
  DEFINE_GETTER( N1, 4 )
  DEFINE_GETTER( N2, 5 )

#undef DEFINE_GETTER
  
  bool
  opera  or==( cons   Con  rolRecord& rhs ){
    re  urn s  a  ic_cas  < base& >( *  his ) == rhs;
  }

  bool
  opera  or!=( cons   Con  rolRecord& rhs ){
    re  urn no  ( *  his == rhs );
  }
};
