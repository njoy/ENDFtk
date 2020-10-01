# standard imports
import unittest

# third party imports

# local imports
from ENDFtk import Section_3
from ENDFtk import DirectoryRecord

class TestSection_3( unittest.TestCase ) :
    """Unit test for the Section_3 class."""

    chunk = ( ' 1.001000+3 9.991673-1          0          0          0          0 125 3102     \n'
              ' 2.224648+6 3.224648+6          0          0          2          6 125 3102     \n'
              '          3          5          6          2                       125 3102     \n'
              ' 1.000000-5 1.672869+1 2.000000-5 1.182897+1 7.500000+5 3.347392-5 125 3102     \n'
              ' 1.900000+7 2.751761-5 1.950000+7 2.731301-5 2.000000+7 2.710792-5 125 3102     \n' )

    valid_SEND = '                                                                   125 3  0     \n'
    invalid_SEND = '                                                                   125 3  1     \n'

    def verify_chunk( self, chunk ) :

        # verify content
        self.assertEqual( 102, chunk.MT )
        self.assertEqual( 1001, chunk.ZA )
        self.assertAlmostEqual( 0.9991673, chunk.AWR )
        self.assertAlmostEqual( 0.9991673, chunk.atomic_weight_ratio )
        self.assertEqual( 0, chunk.LR )
        self.assertEqual( 0, chunk.complex_breakup )
        self.assertAlmostEqual( 2.224648e+6, chunk.QM )
        self.assertAlmostEqual( 2.224648e+6, chunk.mass_difference_qvalue )
        self.assertAlmostEqual( 3.224648e+6, chunk.QI )
        self.assertAlmostEqual( 3.224648e+6, chunk.reaction_qvalue )

        self.assertEqual( 6, chunk.NP )
        self.assertEqual( 2, chunk.NR )
        self.assertEqual( 2, len( chunk.interpolants ) )
        self.assertEqual( 2, len( chunk.boundaries ) )
        self.assertEqual( 5, chunk.interpolants[0] );
        self.assertEqual( 2, chunk.interpolants[1] );
        self.assertEqual( 3, chunk.boundaries[0] );
        self.assertEqual( 6, chunk.boundaries[1] );
        self.assertEqual( 6, len( chunk.energies ) )
        self.assertEqual( 6, len( chunk.cross_sections ) )
        self.assertAlmostEqual( 1e-5, chunk.energies[0] )
        self.assertAlmostEqual( 2e-5, chunk.energies[1] )
        self.assertAlmostEqual( 7.5e+5, chunk.energies[2] )
        self.assertAlmostEqual( 1.9e+7, chunk.energies[3] )
        self.assertAlmostEqual( 1.95e+7, chunk.energies[4] )
        self.assertAlmostEqual( 2e+7, chunk.energies[5] )
        self.assertAlmostEqual( 1.672869e+1, chunk.cross_sections[0] )
        self.assertAlmostEqual( 1.182897e+1, chunk.cross_sections[1] )
        self.assertAlmostEqual( 3.347392e-5, chunk.cross_sections[2] )
        self.assertAlmostEqual( 2.751761e-5, chunk.cross_sections[3] )
        self.assertAlmostEqual( 2.731301e-5, chunk.cross_sections[4] )
        self.assertAlmostEqual( 2.710792e-5, chunk.cross_sections[5] )

        self.assertEqual( 5, chunk.NC )

        # verify string
        self.assertEqual( self.chunk + self.valid_SEND,
                          chunk.to_string( 125, 3 ) )

    def test_constructors( self ) :

        # the data is given explicitly
        chunk = Section_3( mt = 102,  zaid = 1001, lr = 0, awr = 0.9991673,
                           qm = 2.224648e+6, qi = 3.224648e+6,
                           interpolants = [ 5, 2 ], boundaries = [ 3, 6 ],
                           energies = [ 1e-5, 2e-5, 7.5e+5,
                                        1.9e+7, 1.95e+7, 2e+7 ],
                           xs = [ 1.672869e+1, 1.182897e+1, 3.347392e-5,
                                  2.751761e-5, 2.731301e-5, 2.710792e-5 ] )

        self.verify_chunk( chunk )

        # the data is read from a string
        chunk = Section_3.from_string( self.chunk + self.valid_SEND )

        self.verify_chunk( chunk )

        # the data is retrieved from a tree element
        # TODO
        #
        # self.verify_chunk( chunk )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            Section_3.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
