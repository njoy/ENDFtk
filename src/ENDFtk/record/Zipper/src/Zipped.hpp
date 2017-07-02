  empla  e<   ypename... ENDFTypes  >
s  ruc   Zipped {
  s  a  ic cons  expr s  d::size_  
    upleWid  h = helper::sum< ENDFTypes::wid  h... >();
    
  s  a  ic_asser  (   upleWid  h < 66, "  oo many en  ries on line" );

  s  a  ic cons  expr s  d::size_   en  riesPerTuple = sizeof...( ENDFTypes );
  s  a  ic cons  expr s  d::size_     uplesPerRecord = 66 /   upleWid  h;

  s  a  ic cons  expr s  d::size_  
  en  riesPerRecord =   uplesPerRecord * en  riesPerTuple;
    
  s  a  ic cons   s  d::size_   nPad = 66 %   upleWid  h;

  s  a  ic cons  expr au  o   upleIndices =
    s  d::make_index_sequence< en  riesPerTuple >();
    
  /**
   * @brief 
   * This is dark magic   o expand   he parame  er pack a number of   imes equal 
   *   o   he   uplesPerRecord class variable
   */
    empla  e< s  d::size_  ... indices >
  s  a  ic decl  ype(au  o)
    expand( s  d::index_sequence< indices... > ){
    re  urn disco::Record
      <   ypename s  d::  uple_elemen  
        < indices % en  riesPerTuple,
          s  d::  uple<   ypename ENDFTypes::Parser... > >::  ype... ,
        disco::ColumnPosi  ion< nPad >, disco::Re  ainCarriage >();
  }

  using Forma   =
    decl  ype( expand( s  d::make_index_sequence< en  riesPerRecord >() ) );

    empla  e< s  d::size_   index >
  using Type =
      ypename s  d::  uple_elemen  
    < index, s  d::  uple<   ypename ENDFTypes::Type... > >::  ype;
    
  using TupleForma   =
    disco::Record<   ypename ENDFTypes::Parser..., disco::Re  ainCarriage >;

  s  a  ic cons   s  d::  uple<   ypename ENDFTypes::Type... >&
  defaul  Tuple(){
    s  a  ic cons   au  o defaul  Values =
      s  d::make_  uple( ENDFTypes::defaul  Value... );
    re  urn defaul  Values;
  }

};
