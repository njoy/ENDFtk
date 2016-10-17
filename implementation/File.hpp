namespace ENDFtk {
namespace implementation {

template< int MF >
class File{
public:
  using SectionMF = Section< MF >;

#include "ENDFtk/implementation/File/src/ctor.hpp"

  std::vector< SectionMF > sections_;
  std::unordered_map<int, SectionMF& > sectionMap_;

}; // File

} // namespace implementation
} // namespace ENDFtk

