# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF14 import IsotropicDiscretePhoton

class Test_ENDFtk_MF14_IsotropicDiscretePhoton( unittest.TestCase ) :
    """Unit test for the IsotropicDiscretePhoton class."""

    chunk = ' 1.000000+0 2.000000+0          0          0          0          0262514  2     \n'

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( True, chunk.LI )
            self.assertEqual( True, chunk.isotropic_distributions )
            self.assertEqual( 0, chunk.LTT )
            self.assertEqual( 0, chunk.LAW )

            self.assertAlmostEqual( 1., chunk.EG )
            self.assertAlmostEqual( 1., chunk.photon_energy )
            self.assertAlmostEqual( 2., chunk.ES )
            self.assertAlmostEqual( 2., chunk.level_energy )

            self.assertEqual( 1, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 2625, 14, 2 ) )

        # the data is given explicitly
        chunk = IsotropicDiscretePhoton( energy = 1., level = 2. )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = IsotropicDiscretePhoton.from_string( self.chunk, 2625, 14, 2 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = IsotropicDiscretePhoton( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
