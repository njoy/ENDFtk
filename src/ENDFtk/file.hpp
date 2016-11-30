namespace file{

template< int MF >
class Type {
public:
  /* convenience typedefs */
  using Section = section::Type< MF >;

  /* fields */
  std::vector< Section > sectionVector;
  std::unordered_map< int, Section& > sectionMap;

  /* methods */
#include "ENDFtk/file/Type/src/ctor.hpp"
};

}
