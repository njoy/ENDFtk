# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF5 import Section
from ENDFtk.MF5 import PartialDistribution
from ENDFtk.MF5 import MaxwellianFissionSpectrum
from ENDFtk.MF5 import Probability
from ENDFtk.tree import Tape

class Test_ENDFtk_MF5_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.223500+4 2.330250+2          0          0          1          09228 5 18     \n'
              '-3.000000+7 0.000000+0          0          7          1          29228 5 18     \n'
              '          2          2                                            9228 5 18     \n'
              ' 3.250000+6 1.000000+0 2.000000+7 1.000000+0                      9228 5 18     \n'
              ' 0.000000+0 0.000000+0          0          0          1          39228 5 18     \n'
              '          3          5                                            9228 5 18     \n'
              ' 3.250000+6 1.295500+6 1.500000+7 1.492300+6 2.000000+7 1.494470+69228 5 18     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 5  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 3  1     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )

            self.assertEqual( 92235, chunk.ZA )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.NK )
            self.assertEqual( 1, chunk.number_partial_distributions )

            partial = chunk.partial_distributions[0]
            self.assertAlmostEqual( -3e+7, partial.U )
            self.assertAlmostEqual( -3e+7, partial.energy_limit_constant )

            p = partial.probability

            self.assertEqual( 7, p.LF )
            self.assertEqual( 7, p.LAW )

            self.assertEqual( 2, p.NP )
            self.assertEqual( 1, p.NR )
            self.assertEqual( 1, len( p.interpolants ) )
            self.assertEqual( 1, len( p.boundaries ) )
            self.assertEqual( 2, p.interpolants[0] )
            self.assertEqual( 2, p.boundaries[0] )
            self.assertEqual( 2, len( p.E ) )
            self.assertEqual( 2, len( p.energies ) )
            self.assertEqual( 2, len( p.P ) )
            self.assertEqual( 2, len( p.probabilities ) )
            self.assertAlmostEqual( 3.25e+6, p.E[0] )
            self.assertAlmostEqual( 2e+7, p.E[1] )
            self.assertAlmostEqual( 3.25e+6, p.energies[0] )
            self.assertAlmostEqual( 2e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = partial.distribution

            self.assertEqual( True, isinstance( d, MaxwellianFissionSpectrum ) )

            self.assertEqual( 7, d.LF )
            self.assertEqual( 7, d.LAW )

            self.assertEqual( 3, d.NP )
            self.assertEqual( 1, d.NR )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 5, d.interpolants[0] )
            self.assertEqual( 3, d.boundaries[0] )
            self.assertEqual( 3, len( d.E ) )
            self.assertEqual( 3, len( d.energies ) )
            self.assertEqual( 3, len( d.thetas ) )
            self.assertAlmostEqual( 3.25e+6, d.E[0] )
            self.assertAlmostEqual( 1.5e+7, d.E[1] )
            self.assertAlmostEqual( 2e+7, d.E[2] )
            self.assertAlmostEqual( 3.25e+6, d.energies[0] )
            self.assertAlmostEqual( 1.5e+7, d.energies[1] )
            self.assertAlmostEqual( 2e+7, d.energies[2] )
            self.assertAlmostEqual( 1.2955e+6, d.thetas[0] )
            self.assertAlmostEqual( 1.4923e+6, d.thetas[1] )
            self.assertAlmostEqual( 1.49447e+6, d.thetas[2] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9228, 5 ) )

        # the data is given explicitly
        chunk = Section( mt = 18, zaid = 92235, awr = 2.330250e+2,
                         partials = [ PartialDistribution(
                                        Probability( 7, [ 2 ], [ 2 ],
                                                     [ 3.25e+6, 2e+7 ], [ 1., 1. ], -3e+7 ),
                                        MaxwellianFissionSpectrum(
                                          [ 3 ], [ 5 ],
                                          [ 3.25e+6, 1.5e+7, 2e+7 ],
                                          [ 1.2955e+6, 1.4923e+6, 1.49447e+6 ] ) ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 5 ).section( 18 ).parse()

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
