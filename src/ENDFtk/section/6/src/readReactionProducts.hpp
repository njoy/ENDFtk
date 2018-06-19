template< typename Iterator >
static std::vector< ReactionProduct >
readReactionProducts( Iterator& begin,
                      const Iterator& end,
                      long& lineNumber,
                      int MAT,
                      int MF,
                      int MT,
                      int size ) {
  std::vector< ReactionProduct > products;
  products.reserve( size );

  while( size-- ){
    products.emplace_back( begin, end, lineNumber, MAT, MF, MT );
  }

  return products;
}
