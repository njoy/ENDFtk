# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import Tape

class TestTape( unittest.TestCase ) :
    """Unit test for the Tape class."""

    def verifyTape( self, tape ) :

        # basic tape interface
        self.assertEqual( False, tape.has_MAT( 100 ) )
        self.assertEqual( False, tape.has_material( 100 ) )
        self.assertEqual( True, tape.has_MAT( 125 ) )
        self.assertEqual( True, tape.has_material( 125 ) )
        self.assertEqual( False, tape.has_MAT( 9225 ) )
        self.assertEqual( False, tape.has_material( 9225 ) )

    def test_constructors( self ) :

        filename = 'test/tree/resources/n-001_H_001.endf'

        # the data is read from a file
        with open( filename, 'r' ) as file :

            tape = Tape( file.read() )

        print( 'about to verify for first tape' )
        self.verifyTape( tape )

        print( 'about to read second tape' )

        # the data is read from a file using the static from_file method
        tape = Tape.from_file( filename )

        self.verifyTape( tape )

if __name__ == '__main__' :

    unittest.main()
