# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF9 import Section
from ENDFtk.MF9 import Multiplicity
from ENDFtk.tree import Tape

class Test_ENDFtk_MF9_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.524100+4 2.389860+2          0          0          2          09543 9102     \n'
              ' 5.537755+6 5.537755+6      95242          0          1          29543 9102     \n'
              '          2          3                                            9543 9102     \n'
              ' 1.000000-5 9.000000-1 3.000000+7 5.200000-1                      9543 9102     \n'
              ' 5.537755+6 5.489125+6      95242          2          1          29543 9102     \n'
              '          2          3                                            9543 9102     \n'
              ' 1.000000-5 1.000000-1 3.000000+7 4.800000-1                      9543 9102     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9543 9  0     \n'
    valid_FEND = '                                                                  9543 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9543 9  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 102, chunk.MT )
            self.assertEqual( 95241, chunk.ZA )
            self.assertAlmostEqual( 2.389860e+2, chunk.AWR )
            self.assertAlmostEqual( 2.389860e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 0, chunk.LIS )
            self.assertEqual( 0, chunk.excited_level )

            self.assertEqual( 2, len( chunk.multiplicities ) )

            multiplicity = chunk.multiplicities[0]
            self.assertAlmostEqual( 5.537755e+6, multiplicity.QM )
            self.assertAlmostEqual( 5.537755e+6, multiplicity.mass_difference_qvalue )
            self.assertAlmostEqual( 5.537755e+6, multiplicity.QI )
            self.assertAlmostEqual( 5.537755e+6, multiplicity.reaction_qvalue )
            self.assertEqual( 95242, multiplicity.IZAP )
            self.assertEqual( 95242, multiplicity.product_identifier )
            self.assertEqual( 0, multiplicity.LFS )
            self.assertEqual( 0, multiplicity.excited_level )
            self.assertEqual( 2, multiplicity.NP )
            self.assertEqual( 1, multiplicity.NR )
            self.assertEqual( 1, len( multiplicity.interpolants ) )
            self.assertEqual( 1, len( multiplicity.boundaries ) )
            self.assertEqual( 3, multiplicity.interpolants[0] )
            self.assertEqual( 2, multiplicity.boundaries[0] )
            self.assertEqual( 2, len( multiplicity.energies ) )
            self.assertEqual( 2, len( multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1e-5, multiplicity.energies[0] )
            self.assertAlmostEqual( 3e+7, multiplicity.energies[1] )
            self.assertAlmostEqual( 0.9, multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 0.52, multiplicity.multiplicities[1] )

            multiplicity = chunk.multiplicities[1]
            self.assertAlmostEqual( 5.537755e+6, multiplicity.QM )
            self.assertAlmostEqual( 5.537755e+6, multiplicity.mass_difference_qvalue )
            self.assertAlmostEqual( 5.489125e+6, multiplicity.QI )
            self.assertAlmostEqual( 5.489125e+6, multiplicity.reaction_qvalue )
            self.assertEqual( 95242, multiplicity.IZAP )
            self.assertEqual( 95242, multiplicity.product_identifier )
            self.assertEqual( 2, multiplicity.LFS )
            self.assertEqual( 2, multiplicity.excited_level )
            self.assertEqual( 2, multiplicity.NP )
            self.assertEqual( 1, multiplicity.NR )
            self.assertEqual( 1, len( multiplicity.interpolants ) )
            self.assertEqual( 1, len( multiplicity.boundaries ) )
            self.assertEqual( 3, multiplicity.interpolants[0] )
            self.assertEqual( 2, multiplicity.boundaries[0] )
            self.assertEqual( 2, len( multiplicity.energies ) )
            self.assertEqual( 2, len( multiplicity.multiplicities ) )
            self.assertAlmostEqual( 1e-5, multiplicity.energies[0] )
            self.assertAlmostEqual( 3e+7, multiplicity.energies[1] )
            self.assertAlmostEqual( 0.1, multiplicity.multiplicities[0] )
            self.assertAlmostEqual( 0.48, multiplicity.multiplicities[1] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9543, 9 ) )

        # the data is given explicitly
        chunk = Section( mt = 102, zaid = 95241, lis = 0, awr = 2.389860e+2,
                         multiplicities = [
                             Multiplicity( 5.537755e+6, 5.537755e+6, 95242, 0,
                                           [ 2 ], [ 3 ], [ 1e-5, 3e+7 ], [ 0.9, 0.52 ] ),
                             Multiplicity( 5.537755e+6, 5.489125e+6, 95242, 2,
                                           [ 2 ], [ 3 ], [ 1e-5, 3e+7 ], [ 0.1, 0.48 ] ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9543 ).file( 9 ).section( 102 ).parse()

        verify_chunk( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
