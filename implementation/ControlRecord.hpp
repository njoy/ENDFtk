#ifndef ENDFTK_IMPLEMENTATION_CONTROLRECORD_HPP
#define ENDFTK_IMPLEMENTATION_CONTROLRECORD_HPP

class ENDFtk::implementation::ControlRecord :
  protected ENDFtk::implementation::record::Base
            < ENDFtk::implementation::record::Real,
              ENDFtk::implementation::record::Real,
              ENDFtk::implementation::record::Integer< 11 >,
              ENDFtk::implementation::record::Integer< 11 >,
              ENDFtk::implementation::record::Integer< 11 >,
              ENDFtk::implementation::record::Integer< 11 > > {
public:

  using base =
    ENDFtk::implementation::record::Base
    < ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Real,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 >,
      ENDFtk::implementation::record::Integer< 11 > >;
  
  using tail =
    ENDFtk::implementation::record::TailVerifying
    < ENDFtk::implementation::record::MAT,
      ENDFtk::implementation::record::MF,
      ENDFtk::implementation::record::MT >;

  ControlRecord( double C1, double C2,
                 int64_t L1, int64_t L2, int64_t N1, int64_t N2 ) :
    base( C1, C2, L1, L2, N1, N2 ){}

  template< typename Iterator >
  ControlRecord( Iterator& it, const Iterator& end, long& lineNumber,
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

  DEFINE_GETTER( C1, 0 )
  DEFINE_GETTER( C2, 1 )
  DEFINE_GETTER( L1, 2 )
  DEFINE_GETTER( L2, 3 )
  DEFINE_GETTER( N1, 4 )
  DEFINE_GETTER( N2, 5 )

#undef DEFINE_GETTER
  
  bool
  operator==( const ControlRecord& rhs ){
    return static_cast< base& >( *this ) == rhs;
  }

  bool
  operator!=( const ControlRecord& rhs ){
    return not( *this == rhs );
  }
  
};

#endif
