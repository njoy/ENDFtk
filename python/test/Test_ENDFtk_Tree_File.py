# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.tree import File

class Test_ENDFtk_Tree_File( unittest.TestCase ) :
    """Unit test for the File class."""

    def test_file( self ) :

        # the file is empty
        file = File( mat = 125, mf = 3 )

        self.assertEqual( 125, file.MAT )
        self.assertEqual( 125, file.material_number )
        self.assertEqual( 3, file.MF )
        self.assertEqual( 3, file.file_number )

        self.assertEqual( 0, len( file.section_numbers ) )
        self.assertEqual( 0, len( file.sections ) )

        self.assertEqual( '', file.content )

if __name__ == '__main__' :

    unittest.main()
