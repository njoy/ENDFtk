# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF4 import Isotropic

class Test_ENDFtk_MF4_Isotropic( unittest.TestCase ) :
    """Unit test for the Isotropic class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LTT )
            self.assertEqual( 0, chunk.LAW )

            self.assertEqual( 0, chunk.NC )

            # verify string
            self.assertEqual( '', chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = Isotropic()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Isotropic( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
