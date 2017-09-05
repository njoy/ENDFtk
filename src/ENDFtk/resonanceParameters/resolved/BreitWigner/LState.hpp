class LState {
protected:
  const LIST& list;

  auto chunks() const {
    return list.B() | ranges::view::chunk(6);
  }
  
  using Chunk = decltype( chunks() );
  
public:
  #include "ENDFtk/resonanceParameters/resolved/BreitWigner/LState/Resonance.hpp"
  
  LState( const LIST& list ) : list( list ){ }

  double AWRI() const { return list.C1(); }
  double QX() const { return list.C2(); }
  int L() const { return list.L1(); }
  int LRX() const { return list.L2(); }
  int NRS() const { return list.N2(); }

  auto resonances() const {
    return
      this->chunks()
      | ranges::view::transform
        ( []( auto&& chunk ){ return Resonance( std::move(chunk) ); } ); 
  }
};
