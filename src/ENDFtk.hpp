// include basic ENDF records and components
#include "ENDFtk/TapeIdentification.hpp"
#include "ENDFtk/StructureDivision.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DirectoryRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/InterpolationRecord.hpp"
#include "ENDFtk/TabulationRecord.hpp"
#include "ENDFtk/InterpolationSequenceRecord.hpp"

// include every section and their components
#include "ENDFtk/section/1.hpp"
#include "ENDFtk/section/2.hpp"
#include "ENDFtk/section/3.hpp"
#include "ENDFtk/section/4.hpp"
#include "ENDFtk/section/5.hpp"
#include "ENDFtk/section/6.hpp"
#include "ENDFtk/section/7.hpp"
#include "ENDFtk/section/8.hpp"
#include "ENDFtk/section/12.hpp"
#include "ENDFtk/section/13.hpp"

// include every file
#include "ENDFtk/file/1.hpp"
#include "ENDFtk/file/2.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/7.hpp"
#include "ENDFtk/file/8.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"

// include the material and tape
#include "ENDFtk/Material.hpp"
#include "ENDFtk/Tape.hpp"

// include the ENDF tree and its components
#include "ENDFtk/tree/Section.hpp"
#include "ENDFtk/tree/File.hpp"
#include "ENDFtk/tree/Material.hpp"
#include "ENDFtk/tree/Tape.hpp"
#include "ENDFtk/tree/makeTape.hpp"
#include "ENDFtk/tree/fromFile.hpp"

// utility functions
#include "ENDFtk/isRedundant.hpp"
