#ifndef ENDFTK_IMPLEMENTATION_DIRECTORYRECORD_HPP
#define ENDFTK_IMPLEMENTATION_DIRECTORYRECORD_HPP

class ENDFtk::implementation::DirectoryRecord :
  protected ENDFtk::implementation::record::Base
            < ENDFtk::implementation::record::Integer< 33 >,
              ENDFtk::implementation::record::Integer< 11 >,
              ENDFtk::implementation::record::Integer< 11 >,
              ENDFtk::implementation::record::Integer< 11 > > {
public:

  using base =
    ENDFtk::implementation::record::Base
    < ENDFtk::implementation::record::Integer< 33 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 > >;
  
  using tail =
    ENDFtk::implementation::record::TailVerifying
    < ENDFtk::implementation::record::MAT,
      ENDFtk::implementation::record::MF,
      ENDFtk::implementation::record::MT >;

  DirectoryRecord( int64_t L1, int64_t L2, int64_t N1, int64_t N2 ) :
    base( L1, L2, N1, N2 ){}

  template< typename Iterator >
  DirectoryRecord( Iterator& it, const Iterator& end, long& lineNumber,
                   int MAT, int MF, int MT )
    try: base( it, end ){
      tail( MAT, MF, MT, it, end, lineNumber );
    } catch ( std::exception& e ) {
      /* error information here */
      throw e;
    } catch ( int fieldNo ){
      --lineNumber;
      /* error information here */
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
  operator==( const DirectoryRecord& rhs ){
    return static_cast< base& >( *this ) == rhs;
  }

  bool
  operator!=( const DirectoryRecord& rhs ){
    return not( *this == rhs );
  }
  
};


#endif
