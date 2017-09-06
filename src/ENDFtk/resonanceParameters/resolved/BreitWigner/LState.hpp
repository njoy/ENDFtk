class LState {
protected:
  const LIST& list;

  auto stride( int s ) const {
    return list.B()
      | ranges::view::drop_exactly( s )
      | ranges::view::stride( 6 );
  }

  using Chunk = decltype( ( list.B() | ranges::view::chunk(6) )[0] );

public:
  #include "ENDFtk/resonanceParameters/resolved/BreitWigner/LState/Resonance.hpp"

  auto resonanceEnergies() const { return stride( 0 ); }
  auto AJs()               const { return stride( 1 ); }
  auto totalWidths()       const { return stride( 2 ); }
  auto neutronWidths()     const { return stride( 3 ); }
  auto radiationWidths()   const { return stride( 4 ); }
  auto fissionWidths()     const { return stride( 5 ); }

  LState( const LIST& list )
    : list( list )
  { }

  double AWRI() const { return list.C1(); }
  double QX() const { return list.C2(); }

  int L() const { return list.L1(); }
  int LRX() const { return list.L2(); }
  int NRS() const { return list.N2(); }

  auto resonances() const {
    return 
      this->list.B()
        | ranges::view::chunk(6)
        | ranges::view::transform(
            []( Chunk&& chunk ) -> Resonance
              { return Resonance( std::move( chunk ) ); }
          );
  }
};
