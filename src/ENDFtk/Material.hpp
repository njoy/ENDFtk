#ifndef NJOY_ENDFTK_MATERIAL
#define NJOY_ENDFTK_MATERIAL

// system includes
#include <variant>

// other includes
#include "ENDFtk/file/1.hpp"
#include "ENDFtk/file/2.hpp"
#include "ENDFtk/file/3.hpp"
#include "ENDFtk/file/4.hpp"
#include "ENDFtk/file/5.hpp"
#include "ENDFtk/file/6.hpp"
#include "ENDFtk/file/7.hpp"
#include "ENDFtk/file/8.hpp"
#include "ENDFtk/file/9.hpp"
#include "ENDFtk/file/10.hpp"
#include "ENDFtk/file/12.hpp"
#include "ENDFtk/file/13.hpp"
#include "ENDFtk/file/14.hpp"
#include "ENDFtk/file/15.hpp"
#include "ENDFtk/file/23.hpp"
#include "ENDFtk/file/26.hpp"
#include "ENDFtk/file/27.hpp"
#include "ENDFtk/file/28.hpp"
#include "ENDFtk/file/30.hpp"
#include "ENDFtk/file/31.hpp"
#include "ENDFtk/file/32.hpp"
#include "ENDFtk/file/33.hpp"
#include "ENDFtk/file/34.hpp"
#include "ENDFtk/file/35.hpp"
#include "ENDFtk/file/40.hpp"

namespace njoy {
namespace ENDFtk {

  class Material {

  public:

    using FileVariant = std::variant<
                            file::Type< 1 >, file::Type< 2 >, file::Type< 3 >,
                            file::Type< 4 >, file::Type< 5 >, file::Type< 6 >,
                            file::Type< 7 >, file::Type< 8 >, file::Type< 9 >,
                            file::Type< 10 >, file::Type< 12 >, file::Type< 13 >,
                            file::Type< 14 >, file::Type< 15 >, file::Type< 23 >,
                            file::Type< 26 >, file::Type< 27 >, file::Type< 28 >,
                            file::Type< 32 >, file::Type< 33 >, file::Type< 34 > >;

  private:

    using Text = record::Base< record::Character< 66 > >;
    using Tail = record::Tail;

    /* fields */
    int mat_;
    std::map< int, FileVariant > files_;

    /* auxiliary functions */
    #include "ENDFtk/Material/src/fill.hpp"
    #include "ENDFtk/Material/src/read.hpp"
    #include "ENDFtk/Material/src/verifyMEND.hpp"

  public:

    /* constructors */
    #include "ENDFtk/Material/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the material number
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return the material number
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() {

      return this->files_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() {

      return this->MFs();
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto MFs() const {

      return this->files_ | ranges::cpp20::views::values;
    }

    /**
     *  @brief Return the files stored in this material
     */
    auto files() const {

      return this->MFs();
    }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() { return this->files().end(); }

    /**
     *  @brief Return an iterator to the start of the files
     */
    auto begin() const { return this->files().begin(); }

    /**
     *  @brief Return an iterator to the end of the files
     */
    auto end() const { return this->files().end(); }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasMF( int mf ) const {

      return this->files_.count( mf );
    }

    /**
     *  @brief Verify if a given file (defined by the MF number) is defined
     *
     *  @param mf   the MF number of the file to be verified
     */
    bool hasFile( int mf ) const {

      return this->hasMF( mf );
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& file( int mf ) const {

      try {

        return this->files_.at( mf );
      }
      catch( std::out_of_range& o ) {

        Log::error( "Requested file number (MF) does not"
                    " correspond to a stored file" );
        Log::info( "Requested file number: {}", mf );
        Log::info( "Material queried: ", this->MAT() );
        throw o;
      }
    }

    /**
     *  @brief Return the file with the requested MF number
     *
     *  @param[in] mf   the MF number of the file to be returned
     */
    const FileVariant& MF( int mf ) const {

      return this->file( mf );
    }

    #include "ENDFtk/Material/src/print.hpp"
  };

} // ENDFtk namespace
} // njoy namespace

#endif
