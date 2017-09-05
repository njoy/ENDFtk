class LState {
protected:
  const LIST& list;

  auto stride( int s ) const {
    return list.B()
      | ranges::view::drop_exactly( s )
      | ranges::view::stride( 6 );
  }

public:

  auto resonanceEnergies() const { return stride( 0 ); }
  auto AJ()                const { return stride( 1 ); }
  auto totalWidth()        const { return stride( 2 ); }
  auto neutronWidth()      const { return stride( 3 ); }
  auto radiationWidth()    const { return stride( 4 ); }
  auto fissionWidth()      const { return stride( 5 ); }

  LState( const LIST& list )
    : list( list )
  { }

  double AWRI() const { return list.C1(); }
  int L() const { return list.L1(); }
  int LRX() const{ return list.L2(); }
};
