# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT460 import DiscretePhotonMultiplicity

class Test_ENDFtk_MF1_MT460_DiscretePhotonMultiplicity( unittest.TestCase ) :
    """Unit test for the DiscretePhotonMultiplicity class."""

    chunk = ( ' 1.000000-1 0.000000+0          1          0          1          29228 1460     \n'
              '          2          4                                            9228 1460     \n'
              ' 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.1, chunk.E )
            self.assertAlmostEqual( 0.1, chunk.energy )
            self.assertEqual( 1, chunk.LPH )
            self.assertEqual( 1, chunk.index )

            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 2, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 4, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 4, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.time ) )
            self.assertEqual( 2, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 0., chunk.time[0] )
            self.assertAlmostEqual( 4., chunk.time[1] )
            self.assertAlmostEqual( 4.877451e-1, chunk.multiplicities[0] )
            self.assertAlmostEqual( 1.715686e-1, chunk.multiplicities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 460 ) )

        # the data is given explicitly
        chunk = DiscretePhotonMultiplicity( energy = 0.1, lph = 1,
                                boundaries = [ 2 ], interpolants = [ 4 ],
                                time = [ 0., 4. ], multiplicities = [ 4.877451e-1, 1.715686e-1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = DiscretePhotonMultiplicity.from_string( self.chunk, 9228, 1, 460 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DiscretePhotonMultiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = DiscretePhotonMultiplicity( energy = 0.1, lph = 1,
                                    boundaries = [ 3 ], interpolants = [ 4 ],
                                    time = [ 0., 4. ], multiplicities = [ 4.877451e-1, 1.715686e-1 ] )

if __name__ == '__main__' :

    unittest.main()
