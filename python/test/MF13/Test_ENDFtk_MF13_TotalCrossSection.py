# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF13 import TotalCrossSection

class Test_ENDFtk_MF13_TotalCrossSection( unittest.TestCase ) :
    """Unit test for the TotalCrossSection class."""

    chunk = ( ' 0.000000+0 0.000000+0          0          0          1          2922813 18     \n'
              '          2          5                                            922813 18     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      922813 18     \n' )

    invalid = ( ' 0.000000+0 0.000000+0          0          0          2          2922813 18     \n'
                '          2          2                                            922813 18     \n'
                ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 2, chunk.NP )
            self.assertEqual( 2, chunk.number_points )
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, chunk.number_interpolation_regions )
            self.assertEqual( 1, len( chunk.INT ) )
            self.assertEqual( 1, len( chunk.NBT ) )
            self.assertEqual( 5, chunk.INT[0] )
            self.assertEqual( 2, chunk.NBT[0] )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 5, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.XS ) )
            self.assertEqual( 2, len( chunk.cross_sections ) )
            self.assertAlmostEqual( 1., chunk.E[0] )
            self.assertAlmostEqual( 3., chunk.E[1] )
            self.assertAlmostEqual( 1., chunk.energies[0] )
            self.assertAlmostEqual( 3., chunk.energies[1] )
            self.assertAlmostEqual( 2., chunk.XS[0] )
            self.assertAlmostEqual( 4., chunk.XS[1] )
            self.assertAlmostEqual( 2., chunk.cross_sections[0] )
            self.assertAlmostEqual( 4., chunk.cross_sections[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 13, 18 ) )

        # the data is given explicitly
        chunk = TotalCrossSection( boundaries = [ 2 ], interpolants = [ 5 ],
                                   energies = [ 1., 3. ], xs = [ 2., 4. ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = TotalCrossSection.from_string( self.chunk, 9228, 13, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = TotalCrossSection( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = TotalCrossSection( boundaries = [ 2 ], interpolants = [ 5, 2 ],
                                       energies = [ 1., 3. ], xs = [ 2., 4. ] )

        with self.assertRaises( Exception ) :

            chunk = TotalCrossSection.from_string( self.invalid, 9228, 13, 18 )

if __name__ == '__main__' :

    unittest.main()
