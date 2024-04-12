# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF12 import PartialMultiplicity

class Test_ENDFtk_MF12_PartialMultiplicity( unittest.TestCase ) :
    """Unit test for the PartialMultiplicity class."""

    chunk = ( ' 0.000000+0 3.000000+0          2          1          1          2922812 18     \n'
              '          2          2                                            922812 18     \n'
              ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n' )

    invalid = ( ' 0.000000+0 3.000000+0          2          1          2          2922812 18     \n'
                '          2          2                                            922812 18     \n'
                ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 0.0, chunk.EG )
            self.assertAlmostEqual( 0.0, chunk.photon_or_binding_energy )
            self.assertAlmostEqual( 3.0, chunk.ES )
            self.assertAlmostEqual( 3.0, chunk.level_energy )
            self.assertEqual( 2, chunk.LP )
            self.assertEqual( 2, chunk.primary_photon_flag )
            self.assertEqual( 1, chunk.LF )
            self.assertEqual( 1, chunk.LAW )
            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 2, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 2, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.Y ) )
            self.assertEqual( 2, len( chunk.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 3e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 3e+7, chunk.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, chunk.Y[0] )
            self.assertAlmostEqual( 1.487778e+1, chunk.Y[1] )
            self.assertAlmostEqual( 8.579050e+0, chunk.multiplicities[0] )
            self.assertAlmostEqual( 1.487778e+1, chunk.multiplicities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 12, 18 ) )

        # the data is given explicitly
        chunk = PartialMultiplicity( energy = 0.0, level = 3.0, lp = 2, lf = 1,
                                     boundaries = [ 2 ], interpolants = [ 2 ],
                                     energies = [ 1e-5, 3e+7 ],
                                     multiplicities = [ 8.579050e+0, 1.487778e+1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = PartialMultiplicity.from_string( self.chunk, 9228, 12, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = PartialMultiplicity( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = PartialMultiplicity( energy = 0.0, level = 3.0, lp = 2, lf = 1,
                                         boundaries = [ 2, 5 ], interpolants = [ 2 ],
                                         energies = [ 1e-5, 3e+7 ],
                                         multiplicities = [ 8.579050e+0, 1.487778e+1 ] )

        with self.assertRaises( Exception ) :

            chunk = PartialMultiplicity.from_string( self.invalid, 9228, 12, 18 )

if __name__ == '__main__' :

    unittest.main()
