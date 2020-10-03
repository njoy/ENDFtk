# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import Tape

class TestTape( unittest.TestCase ) :
    """Unit test for the Tape class."""

    def verifyTape( self, tape ) :

        def verifyMaterials( materials ) :

            self.assertEqual( 1, len( materials ) )
            self.assertEqual( 125, materials[0].MAT )
            self.assertEqual( 125, materials[0].material_number )

            self.assertEqual( 2211, len( tape.content.split( '\n' ) ) )

        self.assertEqual( [ 125 ], tape.material_numbers )

        self.assertEqual( False, tape.has_MAT( 100 ) )
        self.assertEqual( False, tape.has_material( 100 ) )
        self.assertEqual( True, tape.has_MAT( 125 ) )
        self.assertEqual( True, tape.has_material( 125 ) )
        self.assertEqual( False, tape.has_MAT( 9225 ) )
        self.assertEqual( False, tape.has_material( 9225 ) )

        materials = list( tape.materials )

        verifyMaterials( materials )

        materials = list( tape.MAT( 125 ) )

        verifyMaterials( materials )

        materials = list( tape.material( 125 ) )

        verifyMaterials( materials )

    def test_constructors( self ) :

        filename = 'test/tree/resources/n-001_H_001.endf'

        # the data is read from a file
        with open( filename, 'r' ) as file :

            tape = Tape( file.read() )

        self.verifyTape( tape )

        # the data is read from a file using the static from_file method
        tape = Tape.from_file( filename )

        self.verifyTape( tape )

    def test_failures( self ) :

        print( '\n' )

        # unknown file
        with self.assertRaises( Exception ) :

            filename = 'some unexisting file'
            tape = Tape.from_file( filename )

if __name__ == '__main__' :

    unittest.main()
