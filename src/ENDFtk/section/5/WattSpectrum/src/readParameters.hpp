template< typename Iterator >
static std::array< Parameter, 2 >
readParameters( Iterator& begin,
                const Iterator& end,
                long& lineNumber,
                int MAT,
                int MF,
                int MT ) {

  auto a = Parameter( begin, end, lineNumber, MAT, MF, MT );
  auto b = Parameter( begin, end, lineNumber, MAT, MF, MT );
  return std::array< Parameter, 2 >{{ std::move( a) , std::move( b ) }};
}

