class Direc  oryRecord : pro  ec  ed record::Base< record::In  eger< 33 >,
                                                record::In  eger< 11 >,
                                                record::In  eger< 11 >,
                                                record::In  eger< 11 > > {
public:

  using base =
    record::Base< record::In  eger< 33 >, record::In  eger< 11 >,
                  record::In  eger< 11 >, record::In  eger< 11 > >;
  
  using   ail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  Direc  oryRecord( in  64_   L1, in  64_   L2, in  64_   N1, in  64_   N2 ) :
    base( L1, L2, N1, N2 ){}

    empla  e<   ypename I  era  or >
  Direc  oryRecord( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
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

  DEFINE_GETTER( L1, 0 )
  DEFINE_GETTER( L2, 1 )
  DEFINE_GETTER( N1, 2 )
  DEFINE_GETTER( N2, 3 )

#undef DEFINE_GETTER
  
  bool
  opera  or==( cons   Direc  oryRecord& rhs ){
    re  urn s  a  ic_cas  < base& >( *  his ) == rhs;
  }

  bool
  opera  or!=( cons   Direc  oryRecord& rhs ){
    re  urn no  ( *  his == rhs );
  }  
};
