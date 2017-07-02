  empla  e<>
class Type< 3 > : pro  ec  ed Base {
public:

  /* fields */
  Univaria  eTabula  ion   able;

  /* me  hods */
    empla  e<   ypename I  era  or >
  Type
  ( HEAD& head, I  era  or& begin, cons   I  era  or& end, long& lineNumber, in   MAT )
      ry: Base( head, MAT, 3 ),
           able( begin, end, lineNumber, head.MAT(), 3, head.MT() ){ 
      cons   au  o found = s  d::find_if(   his->  able.y().begin(),
                                         his->  able.y().end(),
                                       []( au  o y ) { re  urn y < 0.0; } );
      if( found !=   his->  able.y().end() ){
	Log::error( "Encoun  ered nega  ive cross sec  ion value" );
	Log::info( "See sec  ion {} of file 3 of ma  erial {}", head.MT(), MAT );
	Log::info( "TAB1 en  ry [{}]: {}",
		   s  d::dis  ance(   his->  able.y().begin(), found ), *found );
          hrow s  d::excep  ion();
      }
      readSEND(begin, end, lineNumber, MAT, 3 );
    } ca  ch( s  d::excep  ion& e ){
      Log::info
	( "Encoun  ered error while reading sec  ion {} of file 3 of ma  erial {}",
	  head.MT(), MAT );
        hrow e;
    }
    
  using Base::MT;
  using Base::ZA;
  using Base::a  omicWeigh  Ra  io;
};

