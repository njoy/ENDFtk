# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF6.LAW5 import NuclearPlusInterference

class Test_ENDFtk_MF6_LAW5_NuclearPlusInterference( unittest.TestCase ) :
    """Unit test for the NuclearPlusInterference class."""

    chunk = ( ' 0.000000+0 1.000000-5         12          0          6          39228 6  5     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    invalid = ( ' 0.000000+0 1.000000-5         12          0          6          49228 6  5     \n'
                ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0 5.000000+0 6.000000+09228 6  5     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 1e-5, chunk.E )
            self.assertAlmostEqual( 1e-5, chunk.incident_energy )

            self.assertEqual( 12, chunk.LTP )
            self.assertEqual( 6, chunk.NW )
            self.assertEqual( 3, chunk.NL )
            self.assertEqual( 3, len( chunk.MU ) )
            self.assertEqual( 3, len( chunk.cosines ) )
            self.assertAlmostEqual( 1., chunk.MU[0] )
            self.assertAlmostEqual( 3., chunk.MU[1] )
            self.assertAlmostEqual( 5., chunk.MU[2] )
            self.assertAlmostEqual( 1., chunk.cosines[0] )
            self.assertAlmostEqual( 3., chunk.cosines[1] )
            self.assertAlmostEqual( 5., chunk.cosines[2] )
            self.assertAlmostEqual( 3, len( chunk.PNI ) )
            self.assertAlmostEqual( 3, len( chunk.probabilities ) )
            self.assertAlmostEqual( 2., chunk.PNI[0] )
            self.assertAlmostEqual( 4., chunk.PNI[1] )
            self.assertAlmostEqual( 6., chunk.PNI[2] )
            self.assertAlmostEqual( 2., chunk.probabilities[0] )
            self.assertAlmostEqual( 4., chunk.probabilities[1] )
            self.assertAlmostEqual( 6., chunk.probabilities[2] )

            self.assertEqual( 2, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 6, 5 ) )

        # the data is given explicitly
        chunk = NuclearPlusInterference( energy = 1e-5, ltp = 12,
                                         cosines = [ 1, 3, 5 ],
                                         probabilities = [ 2, 4, 6 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = NuclearPlusInterference.from_string( self.chunk, 9228, 6, 5 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = NuclearPlusInterference( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = NuclearPlusInterference( energy = 1e-5, ltp = 12,
                                             cosines = [ 1, 3 ],
                                             probabilities = [ 2, 4, 6 ] )

        with self.assertRaises( Exception ) :

            chunk = NuclearPlusInterference.from_string( self.invalid, 9228, 6, 5 )

if __name__ == '__main__' :

    unittest.main()
