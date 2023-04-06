# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF32.MT151 import ReichMooreScatteringRadiusUncertainties

class Test_ENDFtk_MF32_MT151_ReichMooreScatteringRadiusUncertainties( unittest.TestCase ) :
    """Unit test for the ReichMooreScatteringRadiusUncertainties class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          4          0102532151     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      102532151     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1., chunk.DAP )
            self.assertAlmostEqual( 1., chunk.default_uncertainty )

            self.assertEqual( 3, len( chunk.DAPL ) )
            self.assertEqual( 3, len( chunk.uncertainties ) )

            self.assertAlmostEqual( 2., chunk.DAPL[0] )
            self.assertAlmostEqual( 3., chunk.DAPL[1] )
            self.assertAlmostEqual( 4., chunk.DAPL[2] )
            self.assertAlmostEqual( 2., chunk.uncertainties[0] )
            self.assertAlmostEqual( 3., chunk.uncertainties[1] )
            self.assertAlmostEqual( 4., chunk.uncertainties[2] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 1025, 32, 151 ) )

        # the data is given explicitly
        chunk = ReichMooreScatteringRadiusUncertainties(
                    dap = 1, uncertainties = [ 2., 3., 4. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReichMooreScatteringRadiusUncertainties.from_string( self.chunk, 1025, 32, 151 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ReichMooreScatteringRadiusUncertainties( chunk )

        verify_chunk( self, copy )

if __name__ == '__main__' :

    unittest.main()
