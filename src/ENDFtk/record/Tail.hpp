/** @brief Small class to contain the MAT, MF, and MT of a Record */
class Tail {
public:

  /* convenience typedefs */
  using Format = disco::Record< disco::Integer< 4 >,
                                disco::Integer< 2 >,
                                disco::Integer< 3 >,
                                disco::Integer< 5 > >;

  /* fields */
  std::array< int, 3 > fields;

  /* helper methods */
  template< typename Iterator >
  static std::array< int, 3 >
  read( Iterator& it, const Iterator& end ){
    std::array< int, 3 > result;
    try{
      Format::read( it, end, result[0], result[1], result[2] );
    } catch ( std::exception& e ){
      Log::error( "Trouble reading Tail" );
      throw e;
    }
    return result;
  }

  /* ctors */
  template< typename Iterator >
  Tail( Iterator& it, const Iterator& end, long& lineNumber ) :
    fields( read( it, end ) ){ ++lineNumber; }

  constexpr
  Tail( int MAT, int MF, int MT ) :
    fields( std::array< int, 3 >{{ MAT, MF, MT }} ){ }

  /* methods */
  int& material(){ return this->fields[0]; }
  int material() const { return this->fields[0]; }
  int& MAT(){ return this->material(); }
  int MAT() const { return this->material(); }
  
  int& file(){ return this->fields[1]; }
  int file() const { return this->fields[1]; }
  int& MF(){ return this->file(); }
  int MF() const { return this->file(); }
  
  int& section(){ return this->fields[2]; }
  int section() const { return this->fields[2]; }
  int& MT(){ return this->section(); }
  int MT() const { return this->section(); }
};
