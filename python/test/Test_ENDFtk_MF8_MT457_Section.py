# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF8.MT457 import Section
from ENDFtk.tree import Tape

class Test_ENDFtk_MF8_MT457_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk = ( ' 9.524200+4 2.399801+2          2          1          0          23580 8457     \n'
              ' 4.449622+9 6.311520+7          0          0          6          03580 8457     \n'
              ' 4.008322+4 4.128931+3 5.373671+3 3.660206+2 2.441003+4 6.191754+23580 8457     \n'
              ' 5.000000+0-1.000000+0          0          0         18          33580 8457     \n'
              ' 4.000000+0 0.000000+0 5.637120+6 2.549510+2 4.590000-3 1.200000-43580 8457     \n'
              ' 3.000000+0 0.000000+0 4.860000+4 5.000000+1 9.954100-1 1.200000-43580 8457     \n'
              ' 6.000000+0 0.000000+0 1.884000+8 3.700000+6 1.60000-10 6.00000-113580 8457     \n'
              ' 0.000000+0 0.000000+0          0          0          6          23580 8457     \n'
              ' 1.000000+0 0.000000+0 2.107044+2 1.576284+1 0.000000+0 0.000000+03580 8457     \n'
              ' 4.863000+4 5.000000+1          0          0         12          03580 8457     \n'
              ' 3.000000+0 0.000000+0 1.420112-6 2.85306-10 0.000000+0 0.000000+03580 8457     \n'
              ' 7.010000+5 1.106180-2 0.000000+0 0.000000+0 3.315735+5 5.608008+33580 8457     \n'
              ' 4.935000+4 2.000000+1          0          0         12          03580 8457     \n'
              ' 4.000000+0 0.000000+0 1.335690-3 5.409179-5 0.000000+0 0.000000+03580 8457     \n'
              ' 8.209999-1 0.000000+0 0.000000+0 0.000000+0 6.160000-1 8.999999-33580 8457     \n'
              ' 0.000000+0 1.000000+0          1          0          6          03580 8457     \n'
              ' 0.000000+0 0.000000+0 3.107044+2 4.576284+1 5.000000-1 2.500000-13580 8457     \n'
              ' 4.000000+0 0.000000+0          0          0          1          33580 8457     \n'
              '          3          1                                            3580 8457     \n'
              ' 0.000000+0 6.133200-7 5.000000+5 6.133300-7 7.300000+6 6.02040-173580 8457     \n' )

    # TODO add more tests for MF7 MT4

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  3580 8  0     \n'
    valid_FEND = '                                                                  3580 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  3580 8457     \n'

    def test_section( self ) :

        def verify_chunk( self, chunk ) :

            # verify content
            self.assertEqual( 457, chunk.MT )
            self.assertEqual( 457, chunk.section_number )

            self.assertAlmostEqual( 9.524200e+4, chunk.ZA )
            self.assertAlmostEqual( 2.399801e+2, chunk.AWR )
            self.assertAlmostEqual( 2.399801e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LIS )
            self.assertEqual( 2, chunk.excited_state )
            self.assertEqual( 1, chunk.LISO )
            self.assertEqual( 1, chunk.isomeric_state )
            self.assertEqual( False, chunk.NST )
            self.assertEqual( False, chunk.is_stable )
            self.assertAlmostEqual( 5.0, chunk.spin )
            self.assertAlmostEqual( -1., chunk.parity )
            self.assertAlmostEqual( 4.449622e+9, chunk.T[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.T[1] )
            self.assertAlmostEqual( 4.449622e+9, chunk.half_life[0] )
            self.assertAlmostEqual( 6.311520e+7, chunk.half_life[1] )

            energies = chunk.average_decay_energies
            self.assertAlmostEqual( 4.449622e+9, energies.T[0] )
            self.assertAlmostEqual( 6.311520e+7, energies.T[1] )
            self.assertAlmostEqual( 4.449622e+9, energies.half_life[0] )
            self.assertAlmostEqual( 6.311520e+7, energies.half_life[1] )

            self.assertEqual( 3, energies.NCE )
            self.assertEqual( 3, energies.number_decay_energies )
            self.assertEqual( 3, len( energies.E ) )
            self.assertEqual( 3, len( energies.decay_energies ) )
            self.assertAlmostEqual( 4.008322e+4, energies.E[0][0] )
            self.assertAlmostEqual( 4.128931e+3, energies.E[0][1] )
            self.assertAlmostEqual( 5.373671e+3, energies.E[1][0] )
            self.assertAlmostEqual( 3.660206e+2, energies.E[1][1] )
            self.assertAlmostEqual( 2.441003e+4, energies.E[2][0] )
            self.assertAlmostEqual( 6.191754e+2, energies.E[2][1] )
            self.assertAlmostEqual( 4.008322e+4, energies.decay_energies[0][0] )
            self.assertAlmostEqual( 4.128931e+3, energies.decay_energies[0][1] )
            self.assertAlmostEqual( 5.373671e+3, energies.decay_energies[1][0] )
            self.assertAlmostEqual( 3.660206e+2, energies.decay_energies[1][1] )
            self.assertAlmostEqual( 2.441003e+4, energies.decay_energies[2][0] )
            self.assertAlmostEqual( 6.191754e+2, energies.decay_energies[2][1] )

            self.assertAlmostEqual( 4.008322e+4, energies.ELP[0] )
            self.assertAlmostEqual( 4.128931e+3, energies.ELP[1] )
            self.assertAlmostEqual( 4.008322e+4, energies.light_particle_decay_energy[0] )
            self.assertAlmostEqual( 4.128931e+3, energies.light_particle_decay_energy[1] )
            self.assertAlmostEqual( 5.373671e+3, energies.EEM[0] )
            self.assertAlmostEqual( 3.660206e+2, energies.EEM[1] )
            self.assertAlmostEqual( 5.373671e+3, energies.electromagnetic_decay_energy[0] )
            self.assertAlmostEqual( 3.660206e+2, energies.electromagnetic_decay_energy[1] )
            self.assertAlmostEqual( 2.441003e+4, energies.EHP[0] )
            self.assertAlmostEqual( 6.191754e+2, energies.EHP[1] )
            self.assertAlmostEqual( 2.441003e+4, energies.heavy_particle_decay_energy[0] )
            self.assertAlmostEqual( 6.191754e+2, energies.heavy_particle_decay_energy[1] )

            self.assertEqual( 20, chunk.NC )

            # verify string
            self.assertEqual( self.chunk + self.valid_SEND,
                              chunk.to_string( 3580, 8 ) )

        # the data is given explicitly
        #chunk = Section( zaid = 127., awr = 8.934780e+0, lasym = 0, lat = 1,
        #                 constants = ScatteringLawConstants( 0, 1.976285e+2, 5.000001e+0, 0, 8.934780e+0, 1 ),
        #                 law = AnalyticalFunctions(),
        #                 principal = EffectiveTemperature( [ 3 ], [ 2 ],
        #                                                   [ 293.6, 600., 1200. ],
        #                                                   [ 5.332083e+2, 7.354726e+2, 1.270678e+3 ] ) )

        #verify_chunk( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk + self.valid_SEND )

        verify_chunk( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 3580 ).file( 8 ).section( 457 ).parse()

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
