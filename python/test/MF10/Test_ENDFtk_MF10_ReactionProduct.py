# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF10 import ReactionProduct

class Test_ENDFtk_MF10_ReactionProduct( unittest.TestCase ) :
    """Unit test for the ReactionProduct class."""

    chunk = ( ' 2.224648+6 3.224648+6      95242          2          1          2953410102     \n'
              '          2          5                                            953410102     \n'
              ' 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      953410102     \n' )

    invalid = ( ' 2.224648+6 3.224648+6      95242          2          2          2953410102     \n'
                '          2          2                                            953410102     \n'
                ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      953410102     \n' )

    def test_component( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertAlmostEqual( 2.224648e+6, chunk.QM )
            self.assertAlmostEqual( 2.224648e+6, chunk.mass_difference_qvalue )
            self.assertAlmostEqual( 3.224648e+6, chunk.QI )
            self.assertAlmostEqual( 3.224648e+6, chunk.reaction_qvalue )
            self.assertEqual( 95242, chunk.IZAP )
            self.assertEqual( 95242, chunk.product_identifier )
            self.assertEqual( 2, chunk.LFS )
            self.assertEqual( 2, chunk.excited_level )

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
            self.assertEqual( self.chunk, chunk.to_string( 9534, 10, 102 ) )

        # the data is given explicitly
        chunk = ReactionProduct( qm = 2.224648e+6, qi = 3.224648e+6,
                                 izap = 95242, lfs = 2,
                                 boundaries = [ 2 ],
                                 interpolants = [ 5 ],
                                 energies = [ 1., 3. ],
                                 xs = [ 2., 4. ] )

        verify_chunk( self, chunk )

        # the data is given explicitly
        chunk = ReactionProduct( qm = 2.224648e+6, qi = 3.224648e+6,
                                 izap = 95242, lfs = 2,
                                 energies = [ 1., 3. ],
                                 xs = [ 2., 4. ],
                                 interpolant = 5 )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = ReactionProduct.from_string( self.chunk, 9534, 10, 102 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = ReactionProduct( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = ReactionProduct( qm = 2.224648e+6, qi = 3.224648e+6,
                                            izap = 95242, lfs = 2,
                                            boundaries = [ 2 ], interpolants = [ 5, 2 ],
                                            energies = [ 1., 3. ], xs = [ 2., 4. ] )

        with self.assertRaises( Exception ) :

            chunk = ReactionProduct.from_string( self.invalid, 9534, 10, 102 )

if __name__ == '__main__' :

    unittest.main()
