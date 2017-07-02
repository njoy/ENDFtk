class Tex  Record : pro  ec  ed record::Base< record::Charac  er< 66 > > {
public:
  /* convenience   ypedefs */
  using base = record::Base< record::Charac  er< 66 > >;
  using   ail = record::TailVerifying< record::MAT, record::MF, record::MT >;
  
  /* c  or */
  Tex  Record( s  d::s  ring&&   ex   ) : base( s  d::move(  ex  ) ){}

    empla  e<   ypename I  era  or >
  Tex  Record( I  era  or& i  , cons   I  era  or& end, long& lineNumber,
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
  
  /* me  hods */
  Mu  ableRe  urnType< 0 >
    ex  (){ re  urn s  d::ge  < 0 >(   his->fields ); }

  Immu  ableRe  urnType< 0 >
    ex  () cons   { re  urn s  d::ge  < 0 >(   his->fields ); }

  bool
  opera  or==( cons   Tex  Record& rhs ){
    re  urn s  a  ic_cas  < base& >( *  his ) == rhs;
  }

  bool
  opera  or!=( cons   Tex  Record& rhs ){ re  urn no  ( *  his == rhs ); }
};
