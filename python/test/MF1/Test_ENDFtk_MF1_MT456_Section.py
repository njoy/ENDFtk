# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT456 import Section
from ENDFtk.MF1 import PolynomialMultiplicity
from ENDFtk.MF1 import TabulatedMultiplicity
from ENDFtk.tree import Tape

class Test_ENDFtk_MF1_MT456_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_lnu1 = ( ' 9.223500+4 2.330248+2          0          1          0          09228 1456     \n'
                   ' 0.000000+0 0.000000+0          0          0          2          09228 1456     \n'
                   ' 2.436700+0 5.000000-2                                            9228 1456     \n' )

    chunk_lnu2 = ( ' 9.223500+4 2.330248+2          0          2          0          09228 1456     \n'
                   ' 0.000000+0 0.000000+0          0          0          1          49228 1456     \n'
                   '          4          2                                            9228 1456     \n'
                   ' 1.000000-5 2.436700+0 2.530000-2 2.436700+0 5.000000-2 2.436700+09228 1456     \n'
                   ' 2.000000+7 5.209845+0                                            9228 1456     \n' )

    invalid = ( ' 9.223500+4 2.330248+2          0          3          0          09228 1456     \n'
                ' 0.000000+0 0.000000+0          0          0          2          09228 1456     \n'
                ' 2.436700+0 5.000000-2                                            9228 1456     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 1  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 1  1     \n'

    def test_section( self ) :

        def verify_chunk_lnu1( self, chunk ) :

            # verify content
            self.assertEqual( 456, chunk.MT )
            self.assertEqual( 456, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LNU )
            self.assertEqual( 1, chunk.representation )

            self.assertEqual( 1, chunk.nubar.LNU )
            self.assertEqual( 1, chunk.nubar.representation )

            self.assertEqual( 2, chunk.nubar.NCO )
            self.assertEqual( 2, chunk.nubar.number_coefficients )
            self.assertEqual( 2, len( chunk.nubar.C ) )
            self.assertEqual( 2, len( chunk.nubar.coefficients ) )
            self.assertAlmostEqual( 2.4367, chunk.nubar.C[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.C[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.coefficients[0] )
            self.assertAlmostEqual( 5e-2, chunk.nubar.coefficients[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lnu1 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_lnu2( self, chunk ) :

            # verify content
            self.assertEqual( 456, chunk.MT )
            self.assertEqual( 456, chunk.section_number )
            self.assertAlmostEqual( 92235, chunk.ZA )
            self.assertAlmostEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LNU )
            self.assertEqual( 2, chunk.representation )

            self.assertEqual( 2, chunk.nubar.LNU )
            self.assertEqual( 2, chunk.nubar.representation )

            self.assertEqual( 4, chunk.nubar.NP )
            self.assertEqual( 1, chunk.nubar.NR )
            self.assertEqual( 1, len( chunk.nubar.interpolants ) )
            self.assertEqual( 1, len( chunk.nubar.boundaries ) )
            self.assertEqual( 2, chunk.nubar.interpolants[0] )
            self.assertEqual( 4, chunk.nubar.boundaries[0] )

            self.assertEqual( 4, len( chunk.nubar.E ) )
            self.assertEqual( 4, len( chunk.nubar.energies ) )
            self.assertEqual( 4, len( chunk.nubar.NU ) )
            self.assertEqual( 4, len( chunk.nubar.multiplicities ) )
            self.assertAlmostEqual( 1e-5, chunk.nubar.E[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.E[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.E[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.E[3] )
            self.assertAlmostEqual( 1e-5, chunk.nubar.energies[0] )
            self.assertAlmostEqual( 0.0253, chunk.nubar.energies[1] )
            self.assertAlmostEqual( 0.05, chunk.nubar.energies[2] )
            self.assertAlmostEqual( 2e+7, chunk.nubar.energies[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.NU[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.NU[3] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[0] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[1] )
            self.assertAlmostEqual( 2.4367, chunk.nubar.multiplicities[2] )
            self.assertAlmostEqual( 5.209845, chunk.nubar.multiplicities[3] )

            self.assertEqual( 5, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lnu2 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         multiplicity = PolynomialMultiplicity( [ 2.4367, 0.05 ] ) )

        verify_chunk_lnu1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lnu1 + self.valid_SEND )

        verify_chunk_lnu1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lnu1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 456 ).parse()

        verify_chunk_lnu1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lnu1( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         multiplicity =
                             TabulatedMultiplicity( [ 4 ], [ 2 ],
                                                    [ 1.00e-5, 2.53e-2, 5.00e-2, 2.00e+7 ],
                                                    [ 2.436700e+0, 2.436700e+0,
                                                       2.436700e+0, 5.209845e+0 ] ) )

        verify_chunk_lnu2( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lnu2 + self.valid_SEND )

        verify_chunk_lnu2( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lnu2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 456 ).parse()

        verify_chunk_lnu2( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lnu2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
