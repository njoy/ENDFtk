class LState {
protected:
  const LIST& list;

public:
  auto stride( int s ){
    return list.B()
      | ranges::view::drop_exactly( s )
      | ranges::view::stride( 6 );
  }

  LState( const LIST& list )
    : list( list )
  { }

  double AWRI() const { return list.C1(); }
  int L() const { return list.L1(); }
  int LRX() const{ return list.L2(); }
};
