class ListRecord {
public:
  using Base = record::Base< record::Real, record::Real,
                             record::Integer< 11 >, record::Integer< 11 >,
                             record::Integer< 11 >, record::Integer< 11 > >;

  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

  Base metadata;
  std::vector< double > list_;

  template< typename Iterator >
  static void
  verifyTail( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT ){
    tail( MAT, MF, MT, it, end, lineNumber );
  }

#include "ENDFtk/ListRecord/src/readMetadata.hpp"

  ListRecord( double C1, double C2, uint64_t L1, uint64_t L2, uint64_t N2,
              std::vector< double >&& list ) :
    metadata( C1, C2, L1, L2, list.size(), N2 ), list_( std::move(list) ){}

  template< typename Iterator >
  ListRecord( Iterator& it, const Iterator& end, long& lineNumber,
              int MAT, int MF, int MT )
    try: metadata( readMetadata( it, end, lineNumber, MAT, MF, MT ) ),
         list_( record::Sequence::read< record::Real >
                ( std::get<4>( this->metadata.fields ),
                  it, end, lineNumber, MAT, MF, MT ) ){
    } catch ( std::exception& e ){
      Log::info( "Error encountered while parsing List record" );
      throw e;
    } catch ( int nPosition ){
      Log::info( "Error in position {}" );
      throw std::exception();
    }
    
#define DEFINE_GETTER( name, index )                                    \
  Base::MutableReturnType< index >                                      \
  name (){ return std::get< index >( this->metadata.fields ); }         \
                                                                        \
  Base::ImmutableReturnType< index >                                    \
  name () const { return std::get< index >( this->metadata.fields ); }

  DEFINE_GETTER( C1, 0 )
  DEFINE_GETTER( C2, 1 )
  DEFINE_GETTER( L1, 2 )
  DEFINE_GETTER( L2, 3 )
  DEFINE_GETTER( N2, 5 )
    
#undef DEFINE_GETTER  
 
  std::vector< double >& list(){ return this->list_; }
  const std::vector< double >& list() const { return this->list_; }

  std::vector< double >& B(){ return this->list(); }
  const std::vector< double >& B() const { return this->list(); }

  long NPL() const { return this->list_.size(); }

  bool
  operator== ( const ListRecord& rhs ){
    return ( this->C1() == rhs.C1() )
      && ( this->C2() == rhs.C2() )
      && ( this->L1() == rhs.L1() )
      && ( this->L2() == rhs.L2() )
      && ( this->N2() == rhs.N2() )
      && ( this->list_  == rhs.list_ );
  }

  bool
  operator!= ( const ListRecord& rhs ){ return not ( *this == rhs ); }
};
