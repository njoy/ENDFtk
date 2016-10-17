#ifndef ENDFTK_IMPLEMENTATION_TEXTRECORD_HPP
#define ENDFTK_IMPLEMENTATION_TEXTRECORD_HPP

class ENDFtk::implementation::TextRecord :
  protected ENDFtk::implementation::record::Base
            < ENDFtk::implementation::record::Character< 66 > > {
public:

  using base =
    ENDFtk::implementation::record::Base
    < ENDFtk::implementation::record::Character< 66 > >;
  
  using tail =
    ENDFtk::implementation::record::TailVerifying
    < ENDFtk::implementation::record::MAT,
      ENDFtk::implementation::record::MF,
      ENDFtk::implementation::record::MT >;
  
  /* ctor */
  TextRecord( std::string&& text ) : base( std::move(text) ){}

  template< typename Iterator >
  TextRecord( Iterator& it, const Iterator& end, long& lineNumber,
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
  
  /* methods */
  MutableReturnType< 0 >
  text(){ return std::get< 0 >( this->fields ); }

  ImmutableReturnType< 0 >
  text() const { return std::get< 0 >( this->fields ); }

  bool
  operator==( const TextRecord& rhs ){
    return static_cast< base& >( *this ) == rhs;
  }

  bool
  operator!=( const TextRecord& rhs ){
    return not( *this == rhs );
  }
  
};

#endif
