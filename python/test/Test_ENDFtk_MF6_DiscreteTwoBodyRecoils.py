# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6 import DiscreteTwoBodyRecoils

class Test_ENDFtk_MF6_DiscreteTwoBodyRecoils( unittest.TestCase ) :
    """Unit test for the DiscreteTwoBodyRecoils class."""

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 4, chunk.LAW )

            self.assertEqual( 0, chunk.NC )

            # verify string
            self.assertEqual( '', chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = DiscreteTwoBodyRecoils()

        verify_chunk( self, chunk )

        # the data is copied
        copy = DiscreteTwoBodyRecoils( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
