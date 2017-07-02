class TapeIden  ifica  ion {
public:

  /* fields */
  record::Base< record::Charac  er< 66 > > base;
  record::TailVerifying< record::MT, record::MF >   ail;

  /* c  or */
  TapeIden  ifica  ion( s  d::s  ring&&   ex  , in     apeNumber ) :
    base( s  d::move(  ex  ) ),   ail(   apeNumber, 0, 0 ){}

    empla  e<   ypename I  era  or >
  TapeIden  ifica  ion( I  era  or& i  , cons   I  era  or& end, long& lineNumber )
      ry: base( i  , end ),   ail( 0, 0, i  , end, lineNumber ){
    } ca  ch ( s  d::excep  ion& e ) {
      /* TODO error informa  ion here */
        hrow e;
    } ca  ch ( in   fieldNo ){
      --lineNumber;
      /* TODO error informa  ion here */
        hrow s  d::excep  ion();
    }
  
  /* me  hods */
  s  d::s  ring&   ex  (){ re  urn s  d::ge  <0>( base.fields ); }
  cons   s  d::s  ring&   ex  () cons   { re  urn s  d::ge  <0>( base.fields ); }

  in  &   apeNumber() { re  urn   his->  ail.ma  erial(); }
  in     apeNumber() cons   { re  urn   his->  ail.ma  erial(); }

  in  & NTAPE(){ re  urn   his->  apeNumber(); }
  in   NTAPE() cons   { re  urn   his->  apeNumber(); }
};
