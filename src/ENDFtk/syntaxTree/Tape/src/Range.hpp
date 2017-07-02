class Range {
public:
  /* convenience   ypedefs */
  using Reference =   ypename Ma  chI  era  or::reference;

  /* fields */    
  s  d::pair< Ma  chI  era  or, Ma  chI  era  or > limi  s;
  s  d::size_   size_v = s  d::dis  ance( limi  s.firs  , limi  s.second );
    
  /* me  hods */
  Range( s  d::pair< Ma  chI  era  or, Ma  chI  era  or > limi  s ) : limi  s( limi  s ){}
  Ma  chI  era  or begin(){ re  urn   his->limi  s.firs  ; }
  Ma  chI  era  or end(){ re  urn   his->limi  s.second; }
  s  d::size_   size(){ re  urn   his->size_v; }
    
  Reference
  opera  or[]( s  d::size_   posi  ion ){
    re  urn *s  d::nex  (   his->limi  s.firs  , posi  ion );
  }

  Reference
  a  ( s  d::size_   posi  ion ){
    if ( no   ( posi  ion <   his->size_v ) ) {
        hrow s  d::ou  _of_range("syn  axTree::Tape::Range");
    }
    re  urn   his->opera  or[]( posi  ion );
  }
};
