# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT460 import DiscretePhotons
from ENDFtk.MF1.MT460 import DiscretePhotonMultiplicity

class Test_ENDFtk_MF1_MT460_DiscretePhotons( unittest.TestCase ) :
    """Unit test for the DiscretePhotons class."""

    chunk = ( ' 1.000000-1 0.000000+0          1          0          1          29228 1460     \n'
              '          2          4                                            9228 1460     \n'
              ' 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n'
              ' 2.000000-1 0.000000+0          2          0          1          39228 1460     \n'
              '          3          2                                            9228 1460     \n'
              ' 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 1, chunk.LO )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 2, chunk.NG )
            self.assertEqual( 2, chunk.number_discrete_photons )

            self.assertEqual( 2, len( chunk.photons ) )

            self.assertAlmostEqual( 0.1, chunk.photons[0].E )
            self.assertEqual( 1, chunk.photons[0].index )
            self.assertEqual( 1, chunk.photons[0].NR )
            self.assertEqual( 1, chunk.photons[0].number_interpolation_regions )
            self.assertEqual( 2, chunk.photons[0].NP )
            self.assertEqual( 2, chunk.photons[0].number_points )
            self.assertEqual( 1, len( chunk.photons[0].INT ) )
            self.assertEqual( 1, len( chunk.photons[0].NBT ) )
            self.assertEqual( 4, chunk.photons[0].INT[0] )
            self.assertEqual( 2, chunk.photons[0].NBT[0] )
            self.assertEqual( 1, len( chunk.photons[0].interpolants ) )
            self.assertEqual( 1, len( chunk.photons[0].boundaries ) )
            self.assertEqual( 4, chunk.photons[0].interpolants[0] )
            self.assertEqual( 2, chunk.photons[0].boundaries[0] )
            self.assertEqual( 2, len( chunk.photons[0].time ) )
            self.assertEqual( 2, len( chunk.photons[0].multiplicities ) )
            self.assertAlmostEqual( 0., chunk.photons[0].time[0] )
            self.assertAlmostEqual( 4., chunk.photons[0].time[1] )
            self.assertAlmostEqual( 4.877451e-1, chunk.photons[0].multiplicities[0] )
            self.assertAlmostEqual( 1.715686e-1, chunk.photons[0].multiplicities[1] )

            self.assertAlmostEqual( 0.2, chunk.photons[1].E )
            self.assertEqual( 2, chunk.photons[1].index )
            self.assertEqual( 1, chunk.photons[1].NR )
            self.assertEqual( 1, chunk.photons[1].number_interpolation_regions )
            self.assertEqual( 3, chunk.photons[1].NP )
            self.assertEqual( 3, chunk.photons[1].number_points )
            self.assertEqual( 1, len( chunk.photons[1].INT ) )
            self.assertEqual( 1, len( chunk.photons[1].NBT ) )
            self.assertEqual( 2, chunk.photons[1].INT[0] )
            self.assertEqual( 3, chunk.photons[1].NBT[0] )
            self.assertEqual( 1, len( chunk.photons[1].interpolants ) )
            self.assertEqual( 1, len( chunk.photons[1].boundaries ) )
            self.assertEqual( 2, chunk.photons[1].interpolants[0] )
            self.assertEqual( 3, chunk.photons[1].boundaries[0] )
            self.assertEqual( 3, len( chunk.photons[1].time ) )
            self.assertEqual( 3, len( chunk.photons[1].multiplicities ) )
            self.assertAlmostEqual( 0., chunk.photons[1].time[0] )
            self.assertAlmostEqual( 5., chunk.photons[1].time[1] )
            self.assertAlmostEqual( 9., chunk.photons[1].time[2] )
            self.assertAlmostEqual( 1.691176e-1, chunk.photons[1].multiplicities[0] )
            self.assertAlmostEqual( 2.450980e-3, chunk.photons[1].multiplicities[1] )
            self.assertAlmostEqual( 1.691176e-1, chunk.photons[1].multiplicities[2] )

            self.assertEqual( 6, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 1, 460 ) )

        # the data is given explicitly
        chunk = DiscretePhotons(
                  photons = [ DiscretePhotonMultiplicity( 0.1, 1, [ 2 ], [ 4 ], [ 0., 4. ],
                                                          [ 4.877451e-1, 1.715686e-1 ] ),
                              DiscretePhotonMultiplicity( 0.2, 2, [ 3 ], [ 2 ], [ 0., 5., 9 ],
                                                          [ 1.691176e-1, 2.450980e-3, 1.691176e-1 ] ) ] )

        verify_chunk( self, chunk )

        # the data is copied
        copy = DiscretePhotons( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = DiscretePhotons( constants = [] )

        with self.assertRaises( Exception ) :

            chunk = DiscretePhotons.from_string( self.invalidNNF, 9228, 1, 460 )

if __name__ == '__main__' :

    unittest.main()
