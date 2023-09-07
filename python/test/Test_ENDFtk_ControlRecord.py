# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import ControlRecord

class Test_ENDFtk_ControlRecord( unittest.TestCase ) :
    """Unit test for the ControlRecord class."""

    chunk = ' 1.001000+3 9.991673-1          1          2          3          4 125 1451     \n'

    def test_record( self ) :

        def verify_chunk( self, chunk ) :

            self.assertAlmostEqual( chunk.C1, 1001. )
            self.assertAlmostEqual( chunk.C2, 0.9991673 )
            self.assertEqual( chunk.L1, 1 )
            self.assertEqual( chunk.L2, 2 )
            self.assertEqual( chunk.N1, 3 )
            self.assertEqual( chunk.N2, 4 )

            self.assertEqual( chunk.to_string( 125, 1, 451 ), self.chunk )

        chunk = ControlRecord( C1 = 1001., C2 = 0.9991673,
                               L1 = 1, L2 = 2,
                               N1 = 3, N2 = 4 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ControlRecord( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
