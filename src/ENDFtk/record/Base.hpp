  empla  e<   ypename... Fields >
s  ruc   Base {
  /* verify invarian  s */
  s  a  ic_asser  ( sizeof...(Fields) > 0,
		 "A record mus   con  ain a   leas   1 field" );

  s  a  ic_asser  
  ( helper::sum< Fields::wid  h... >() == 66,
    "The field wid  hs do no   sum   o 66 as required by   he ENDF forma  " );
  
  /* convenience   ypedefs */
  using FieldTuple = s  d::  uple<   ypename Fields::Type... >;
  using Forma   = disco::Record<   ypename Fields::Parser...,
				disco::Re  ainCarriage >;
  
    empla  e< in   Index >
  using ShouldRecurse =
    s  d::condi  ional_  < (Index != 0), s  d::  rue_  ype, s  d::false_  ype >;

    empla  e<   ypename T >
  using Argumen  Type =
    s  d::condi  ional_  < s  d::is_  rivially_copyable< T >::value,
                        T, s  d::add_rvalue_reference_  < T > >;
  
    empla  e< s  d::size_   index >
  using Elemen  Type = s  d::  uple_elemen  _  < index, FieldTuple >;

    empla  e< s  d::size_   index >
  using Mu  ableRe  urnType = s  d::add_lvalue_reference_  < Elemen  Type< index > >;

    empla  e< s  d::size_   index >
  using Immu  ableRe  urnType =
    s  d::condi  ional_  
    < s  d::is_  rivially_copyable< Elemen  Type< index > >::value,
      Elemen  Type< index >,
      s  d::add_lvalue_reference_  < s  d::add_cons  _  < Elemen  Type< index > > > >;

  /* cons  an  s */
  s  a  ic cons  expr s  d::size_   nFields = sizeof...(Fields);
  
  /* fields */
  FieldTuple fields;

  /* helper me  hods */
    empla  e< in  , in  ... Indices,   ypename I  era  or >
  s  a  ic FieldTuple
  readFields( I  era  or& i  , cons   I  era  or& end, s  d::false_  ype ){
    FieldTuple resul  ;
    Forma  ::read( i  , end, s  d::ge  < Indices >( resul   )... );
    re  urn resul  ;
  }

    empla  e< in   Index, in  ... Indices,   ypename I  era  or >
  s  a  ic FieldTuple
  readFields( I  era  or& i  , cons   I  era  or& end, s  d::  rue_  ype ){
    re  urn readFields< Index - 1, Index, Indices... >
           ( i  , end, ShouldRecurse< Index >() );
  }

  /* c  or */
    empla  e<   ypename I  era  or >
  Base( I  era  or& i  , cons   I  era  or& end ) :
    fields( readFields< nFields - 1 >( i  , end, s  d::  rue_  ype() ) ){}

  Base( Argumen  Type<   ypename Fields::Type > ...   ypes ) :
    fields( s  d::make_  uple<   ypename Fields::Type... >
            ( s  d::forward
              < Argumen  Type<   ypename Fields::Type > >(   ypes )... ) ){}

  /* helper me  hods */
    empla  e< in   Index = nFields >
  bool
  equali  y( cons   Base&, s  d::false_  ype ){ re  urn   rue; }
  
    empla  e< in   Index = nFields >
  bool
  equali  y( cons   Base& rhs, s  d::  rue_  ype ){
    cons  expr au  o index = nFields - Index;
    re  urn
      ( s  d::ge  < index >( rhs.fields ) == s  d::ge  < index >(   his->fields ) )
      &&   his->equali  y< Index - 1 >( rhs, ShouldRecurse< Index - 1 >() );
  }

  /* me  hods */
  bool
  opera  or==( cons   Base& rhs ){
    re  urn   his->equali  y( rhs, s  d::  rue_  ype() );
  }

  bool
  opera  or!=( cons   Base& rhs ){
    re  urn no   ( *  his == rhs );
  }
};
