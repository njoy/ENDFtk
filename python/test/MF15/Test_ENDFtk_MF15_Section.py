# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF15 import Section
from ENDFtk.MF15 import Probability
from ENDFtk.MF15 import PartialDistribution
from ENDFtk.MF15 import OutgoingEnergyDistribution
from ENDFtk.MF15 import TabulatedSpectrum
from ENDFtk.tree import Tape

class Test_ENDFtk_MF15_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.223500+4 2.330250+2          0          0          1          0922815 18     \n'
              ' 0.000000+0 0.000000+0          0          1          1          2922815 18     \n'
              '          2          2                                            922815 18     \n'
              ' 1.000000-5 1.000000+0 3.000000+7 1.000000+0                      922815 18     \n'
              ' 0.000000+0 0.000000+0          0          0          1          2922815 18     \n'
              '          2          4                                            922815 18     \n'
              ' 0.000000+0 1.000000-5          0          0          1          3922815 18     \n'
              '          3          2                                            922815 18     \n'
              ' 0.000000+0 0.000000+0 1.000000+5 1.757570-9 3.000000+7 1.843350-9922815 18     \n'
              ' 0.000000+0 3.000000+7          0          0          1          4922815 18     \n'
              '          4          2                                            922815 18     \n'
              ' 0.000000+0 0.000000+0 1.000000+1 1.733405-9 1.100000+1 1.818010-9922815 18     \n'
              ' 3.000000+7 1.898849-9                                            922815 18     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  922815  0     \n'
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

            p = partial.probability

            self.assertEqual( 1, p.LF )
            self.assertEqual( 1, p.LAW )

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
            self.assertAlmostEqual( 1e-5, p.E[0] )
            self.assertAlmostEqual( 3e+7, p.E[1] )
            self.assertAlmostEqual( 1e-5, p.energies[0] )
            self.assertAlmostEqual( 3e+7, p.energies[1] )
            self.assertAlmostEqual( 1., p.P[0] )
            self.assertAlmostEqual( 1., p.P[1] )
            self.assertAlmostEqual( 1., p.probabilities[0] )
            self.assertAlmostEqual( 1., p.probabilities[1] )

            d = partial.distribution

            self.assertEqual( True, isinstance( d, TabulatedSpectrum ) )

            self.assertEqual( 1, d.LF )
            self.assertEqual( 1, d.LAW )

            self.assertEqual( 1, d.NR )
            self.assertEqual( 2, d.NE )
            self.assertEqual( 1, len( d.boundaries ) )
            self.assertEqual( 2, d.boundaries[0] )
            self.assertEqual( 1, len( d.interpolants ) )
            self.assertEqual( 4, d.interpolants[0] )

            self.assertEqual( 2, len( d.incident_energies ) )
            self.assertAlmostEqual( 1e-5, d.incident_energies[0] )
            self.assertAlmostEqual( 3e+7, d.incident_energies[1] )

            value = d.outgoing_distributions[0]
            self.assertAlmostEqual( 1e-5, value.E )
            self.assertAlmostEqual( 1e-5, value.incident_energy )
            self.assertEqual( 3, value.NP )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 3, value.boundaries[0] )
            self.assertEqual( 3, len( value.EP ) )
            self.assertEqual( 3, len( value.outgoing_energies ) )
            self.assertEqual( 3, len( value.G ) )
            self.assertEqual( 3, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 1e+5, value.EP[1] )
            self.assertAlmostEqual( 3e+7, value.EP[2] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 1e+5, value.outgoing_energies[1] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[2] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.757570e-9, value.G[1] )
            self.assertAlmostEqual( 1.843350e-9, value.G[2] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.757570e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.843350e-9, value.probabilities[2] )

            value = d.outgoing_distributions[1]
            self.assertAlmostEqual( 3e+7, value.E )
            self.assertAlmostEqual( 3e+7, value.incident_energy )
            self.assertEqual( 4, value.NP )
            self.assertEqual( 1, value.NR )
            self.assertEqual( 1, len( value.interpolants ) )
            self.assertEqual( 1, len( value.boundaries ) )
            self.assertEqual( 2, value.interpolants[0] )
            self.assertEqual( 4, value.boundaries[0] )
            self.assertEqual( 4, len( value.EP ) )
            self.assertEqual( 4, len( value.outgoing_energies ) )
            self.assertEqual( 4, len( value.G ) )
            self.assertEqual( 4, len( value.probabilities ) )
            self.assertAlmostEqual( 0.0, value.EP[0] )
            self.assertAlmostEqual( 10., value.EP[1] )
            self.assertAlmostEqual( 11., value.EP[2] )
            self.assertAlmostEqual( 3e+7, value.EP[3] )
            self.assertAlmostEqual( 0.0, value.outgoing_energies[0] )
            self.assertAlmostEqual( 10., value.outgoing_energies[1] )
            self.assertAlmostEqual( 11., value.outgoing_energies[2] )
            self.assertAlmostEqual( 3e+7, value.outgoing_energies[3] )
            self.assertAlmostEqual( 0., value.G[0] )
            self.assertAlmostEqual( 1.733405e-9, value.G[1] )
            self.assertAlmostEqual( 1.818010e-9, value.G[2] )
            self.assertAlmostEqual( 1.898849e-9, value.G[3] )
            self.assertAlmostEqual( 0., value.probabilities[0] )
            self.assertAlmostEqual( 1.733405e-9, value.probabilities[1] )
            self.assertAlmostEqual( 1.818010e-9, value.probabilities[2] )
            self.assertAlmostEqual( 1.898849e-9, value.probabilities[3] )

            self.assertEqual( 13, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 9228, 15 ) )

        # the data is given explicitly
        chunk = Section( mt = 18, zaid = 92235, awr = 2.330250e+2,
                         partials = [ PartialDistribution(
                                        Probability( [ 2 ], [ 2 ],
                                                     [ 1e-5, 3e+7 ], [ 1., 1. ] ),
                                        TabulatedSpectrum( [ 2 ], [ 4 ],
                                                           [ OutgoingEnergyDistribution(
                                                                 1e-5, [ 3 ], [ 2 ],
                                                                 [ 0.0, 1e+5, 3e+7 ],
                                                                 [ 0.0, 1.757570e-9, 1.843350e-9 ] ),
                                                             OutgoingEnergyDistribution(
                                                                 3e+7, [ 4 ], [ 2 ],
                                                                 [ 0.0, 10., 11., 3e+7 ],
                                                                 [ 0.0, 1.733405e-9, 1.818010e-9,
                                                                   1.898849e-9 ] ) ] ) ) ] )

        verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 15 ).section( 18 ).parse()

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
