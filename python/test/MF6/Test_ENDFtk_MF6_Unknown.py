# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import Unknown

class Test_ENDFtk_MF6_Unknown( unittest.TestCase ) :
    """Unit test for the Unknown class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LAW )

            self.assertEqual( 0, chunk.NC )

            # verify string
            self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = Unknown()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Unknown( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
