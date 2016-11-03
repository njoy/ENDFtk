class TextRecord : protected record::Base< record::Character< 66 > > {
public:
  /* convenience typedefs */
  using base = record::Base< record::Character< 66 > >;
  using tail = record::TailVerifying< record::MAT, record::MF, record::MT >;
  
  /* ctor */
  TextRecord( std::string&& text ) : base( std::move(text) ){}

  template< typename Iterator >
  TextRecord( Iterator& it, const Iterator& end, long& lineNumber,
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
  operator!=( const TextRecord& rhs ){ return not( *this == rhs ); }
};
