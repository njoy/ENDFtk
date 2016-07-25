#ifndef ENDFTK_IMPLEMENTATION_HEADRECORD_HPP
#define ENDFTK_IMPLEMENTATION_HEADRECORD_HPP

class ENDFtk::implementation::HeadRecord : protected StructureDivision {
public:

  template< std::size_t index >
  using MutableReturnType = Base::MutableReturnType< index >;
  
  template< std::size_t index >
  using ImmutableReturnType = Base::ImmutableReturnType< index >;

  HeadRecord( double C1, double C2, long L1, long L2, long N1, long N2,
              int MAT, int MF, int MT ) :
  StructureDivision( C1, C2, L1, L2, N1, N2, MAT, MF, MT ) {}
  
  template< typename Iterator >
  HeadRecord( Iterator& it, const Iterator& end, long& lineNumber )
    : StructureDivision(it, end, lineNumber) { /* Do nothing */ }

#define DEFINE_BASE_GETTER( name, position )                            \
  MutableReturnType< position >                                         \
  name(){ return std::get< position >( this->base.fields ); }           \
                                                                        \
  ImmutableReturnType< position >                                       \
  name() const { return std::get< position >( this->base.fields ); }

  DEFINE_BASE_GETTER( ZA, 0 )
  DEFINE_BASE_GETTER( atomicWeightRatio, 1 )
  DEFINE_BASE_GETTER( AWR, 1 )
  DEFINE_BASE_GETTER( L1, 2 )
  DEFINE_BASE_GETTER( L2, 3 )
  DEFINE_BASE_GETTER( N1, 4 )
  DEFINE_BASE_GETTER( N2, 5 )

#undef DEFINE_BASE_GETTER
    
#define DEFINE_TAIL_GETTER( name )                                      \
  decltype( tail.name() )                                               \
  name(){ return this->tail.name(); }                                   \
                                                                        \
  decltype( std::declval                                                \
            < typename std::add_const                                   \
              < decltype( tail ) >::type >().name() )                   \
  name() const { return this->tail.name(); }                               
  
  DEFINE_TAIL_GETTER( MAT )
  DEFINE_TAIL_GETTER( MF )
  DEFINE_TAIL_GETTER( MT )
  DEFINE_TAIL_GETTER( material )
  DEFINE_TAIL_GETTER( file )
  DEFINE_TAIL_GETTER( section )
  
#undef DEFINE_DEFERRED_GETTER

#include "ENDFtk/implementation/HeadRecord/src/asHead.hpp"
};

#endif
