class LState: public Unresolved::LState {

public:
  // #include "ENDFtk/resonanceParameters/unresolved/EnergyDependent/LState/Resonance.hpp"
  using Unresolved::LState::LState;

  // auto resonances() const {
  //   return 
  //     this->lists 
  //       | ranges::view::for_each( 
  //           []( auto&& L ){ return L.B()
  //                           | ranges::view::drop_exactly(6); } )
  //       | ranges::view::chunk(6)
  //       | ranges::view::transform(
  //           []( Chunk&& chunk ) -> Resonance
  //             { return Resonance( std::move( chunk ) ); } );
  // }
};
