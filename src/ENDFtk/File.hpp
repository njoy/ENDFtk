template< int MF >
class File {
  /* convenience typedefs */
  using Section = section::Type< MF >;

  /* fields */
  std::vector< Section > sectionVector;
  std::unordered_map< int, Section& > sectionMap;

  /* methods */
#include "ENDFtk/File/src/ctor.hpp"
};
