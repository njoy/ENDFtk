class DirectoryRecord : protected record::Base< record::Integer< 33 >,
                                                record::Integer< 11 >,
                                                record::Integer< 11 >,
                                                record::Integer< 11 > > {
  using base =
    record::Base< record::Integer< 33 >, record::Integer< 11 >,
                  record::Integer< 11 >, record::Integer< 11 > >;
  
  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;

public:  
  DirectoryRecord( long L1, long L2, long N1, long N2 ) :
    base( L1, L2, N1, N2 ){}

  template< typename Iterator >
  DirectoryRecord( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT )
    try: base( it, end ){
      tail( MAT, MF, MT, it, end, lineNumber );
    } catch ( std::exception& e ) {
      /* TODO error information here */
      throw e;
    } catch ( int fieldNo ){
      --lineNumber;
      /* TODO error information here */
      throw std::exception();
    }

#define DEFINE_GETTER( name, index )                            \
  MutableReturnType< index >                                    \
  name (){ return std::get< index >( this->fields ); }          \
                                                                \
  ImmutableReturnType< index >                                  \
  name () const { return std::get< index >( this->fields ); }

  DEFINE_GETTER( L1, 0 )
  DEFINE_GETTER( L2, 1 )
  DEFINE_GETTER( N1, 2 )
  DEFINE_GETTER( N2, 3 )

#undef DEFINE_GETTER
  
  bool
  operator==( const DirectoryRecord& rhs ) const {
    return static_cast< const base& >( *this ) == rhs;
  }

  bool
  operator!=( const DirectoryRecord& rhs ) const {
    return not( *this == rhs );
  }

  long NC() const { return 1; }
  
  #include "ENDFtk/DirectoryRecord/src/print.hpp"
};
