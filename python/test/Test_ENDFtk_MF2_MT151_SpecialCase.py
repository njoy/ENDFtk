# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF2.MT151 import SpecialCase

class Test_ENDFtk_MF2_MT151_SpecialCase( unittest.TestCase ) :
    """Unit test for the SpecialCase class."""

    chunk = ' 5.000000-1 1.276553+0          0          0          0          02625 2151     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 0, chunk.LRU )
            self.assertEqual( 0, chunk.type )
            self.assertEqual( 0, chunk.LRF )
            self.assertEqual( 0, chunk.representation )

            self.assertAlmostEqual( 0.5, chunk.SPI )
            self.assertAlmostEqual( 0.5, chunk.spin )
            self.assertAlmostEqual( 1.276553, chunk.AP )
            self.assertAlmostEqual( 1.276553, chunk.scattering_radius )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 2, 151 ) )

        # the data is given explicitly
        chunk = SpecialCase( spin = 0.5, ap = 1.276553 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = SpecialCase.from_string( self.chunk, 2625, 2, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = SpecialCase( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
