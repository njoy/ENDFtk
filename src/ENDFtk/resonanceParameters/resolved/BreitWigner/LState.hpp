class LState {
protected:
  const LIST& list;

  using Chunk = decltype( ( list.B() | ranges::view::chunk(6) )[0] );

public:
  #include "ENDFtk/resonanceParameters/resolved/BreitWigner/LState/Resonance.hpp"

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
