# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF13 import PartialCrossSection

class Test_ENDFtk_MF13_PartialCrossSection( unittest.TestCase ) :
    """Unit test for the PartialCrossSection class."""

    chunk = ( ' 0.000000+0 3.000000+0          2          1          1          2922813 18     \n'
              '          2          2                                            922813 18     \n'
              ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n' )

    invalid = ( ' 0.000000+0 3.000000+0          2          1          2          2922813 18     \n'
                '          2          2                                            922813 18     \n'
                ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922813 18     \n' )

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
            self.assertEqual( 1, chunk.NR )
            self.assertEqual( 1, len( chunk.interpolants ) )
            self.assertEqual( 1, len( chunk.boundaries ) )
            self.assertEqual( 2, chunk.interpolants[0] )
            self.assertEqual( 2, chunk.boundaries[0] )
            self.assertEqual( 2, len( chunk.E ) )
            self.assertEqual( 2, len( chunk.energies ) )
            self.assertEqual( 2, len( chunk.XS ) )
            self.assertEqual( 2, len( chunk.cross_sections ) )
            self.assertAlmostEqual( 1e-5, chunk.E[0] )
            self.assertAlmostEqual( 3e+7, chunk.E[1] )
            self.assertAlmostEqual( 1e-5, chunk.energies[0] )
            self.assertAlmostEqual( 3e+7, chunk.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, chunk.XS[0] )
            self.assertAlmostEqual( 1.487778e+1, chunk.XS[1] )
            self.assertAlmostEqual( 8.579050e+0, chunk.cross_sections[0] )
            self.assertAlmostEqual( 1.487778e+1, chunk.cross_sections[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk, chunk.to_string( 9228, 13, 18 ) )

        # the data is given explicitly
        chunk = PartialCrossSection( energy = 0.0, level = 3.0, lp = 2, lf = 1,
                                     boundaries = [ 2 ], interpolants = [ 2 ],
                                     energies = [ 1e-5, 3e+7 ],
                                     xs = [ 8.579050e+0, 1.487778e+1 ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = PartialCrossSection.from_string( self.chunk, 9228, 13, 18 )

        verify_chunk( self, chunk )

        # the data is copied
        copy = PartialCrossSection( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # wrong boundaries
        with self.assertRaises( Exception ) :

            chunk = PartialCrossSection( energy = 0.0, level = 3.0, lp = 2, lf = 1,
                                         boundaries = [ 2, 5 ], interpolants = [ 2 ],
                                         energies = [ 1e-5, 3e+7 ],
                                         xs = [ 8.579050e+0, 1.487778e+1 ] )

        with self.assertRaises( Exception ) :

            chunk = PartialCrossSection.from_string( self.invalid, 9228, 13, 18 )

if __name__ == '__main__' :

    unittest.main()
