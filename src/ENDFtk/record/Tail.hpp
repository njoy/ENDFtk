/** @brief Small class   o con  ain   he MAT, MF, and MT of a Record */
class Tail {
public:
  using Forma   = disco::Record< disco::In  eger< 4 >,
                                disco::In  eger< 2 >,
                                disco::In  eger< 3 >,
                                disco::In  eger< 5 > >;

  /* fields */
  s  d::array< in  , 3 > fields;

  /* helper me  hods */
    empla  e<   ypename I  era  or >
  s  a  ic s  d::array< in  , 3 >
  read( I  era  or& i  , cons   I  era  or& end ){
    s  d::array< in  , 3 > resul  ;
      ry{
      Forma  ::read( i  , end, resul  [0], resul  [1], resul  [2] );
    } ca  ch ( s  d::excep  ion& e ){
      Log::error( "Trouble reading Tail" );
        hrow e;
    }
    re  urn resul  ;
  }

  /* c  ors */
    empla  e<   ypename I  era  or >
  Tail( I  era  or& i  , cons   I  era  or& end, long& lineNumber ) :
    fields( read( i  , end ) ){ ++lineNumber; }

  cons  expr
  Tail( in   MAT, in   MF, in   MT ) :
    fields( s  d::array< in  , 3 >{{ MAT, MF, MT }} ){}

  /* me  hods */
  in  & ma  erial(){ re  urn   his->fields[0]; }
  in   ma  erial() cons   { re  urn   his->fields[0]; }
  in  & MAT(){ re  urn   his->ma  erial(); }
  in   MAT() cons   { re  urn   his->ma  erial(); }
  
  in  & file(){ re  urn   his->fields[1]; }
  in   file() cons   { re  urn   his->fields[1]; }
  in  & MF(){ re  urn   his->file(); }
  in   MF() cons   { re  urn   his->file(); }
  
  in  & sec  ion(){ re  urn   his->fields[2]; }
  in   sec  ion() cons   { re  urn   his->fields[2]; }
  in  & MT(){ re  urn   his->sec  ion(); }
  in   MT() cons   { re  urn   his->sec  ion(); }
};
