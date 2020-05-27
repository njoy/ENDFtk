/* Placeholder class */
template< int MF, int... OptionalMT >
class GendfType {

public:
  // ctor
  GendfType() {}

  // methods
  int confirm { return 0; }
}


/*
 * @brief Parse a Section from a GENDF tape.
 */
template< typename BufferIterator >
template< int MF, int... OptionalMT >
GendfType< MF, Optional MT...>
Section< BufferIterator, GENDFTag >::parse() const {

  return {};

}
