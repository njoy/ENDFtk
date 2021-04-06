# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF12 import Section
from ENDFtk.MF12 import PartialMultiplicity
from ENDFtk.MF12 import Multiplicities
from ENDFtk.MF12 import TransitionProbabilities
from ENDFtk.tree import Tape

class Test_ENDFtk_MF12_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_lo1 = ( ' 9.223500+4 2.330250+2          1          0          1          0922812 18     \n'
                  ' 0.000000+0 0.000000+0          0          1          1          2922812 18     \n'
                  '          2          2                                            922812 18     \n'
                  ' 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      922812 18     \n' )

    chunk_lo2lg1 = ( ' 9.223500+4 2.330250+2          2          1          4          0922812 51     \n'
                     ' 5.170900+4 0.000000+0          0          0          4          2922812 51     \n'
                     ' 1.304000+4 2.709000-1 7.700000+1 7.291000-1                      922812 51     \n' )

    chunk_lo2lg2 = ( ' 9.223500+4 2.330250+2          2          2          4          0922812 51     \n'
                     ' 5.170900+4 0.000000+0          0          0          6          2922812 51     \n'
                     ' 1.304000+4 2.709000-1 3.215434-3 7.700000+1 7.291000-1 3.144654-3922812 51     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  922812  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  922812  1     \n'

    def test_section( self ) :

        def verify_chunk_lo1( self, chunk ) :

            # verify content
            self.assertEqual( 18, chunk.MT )
            self.assertEqual( 18, chunk.section_number )

            self.assertAlmostEqual( 92235., chunk.ZA )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LO )
            self.assertEqual( 1, chunk.representation )

            data = chunk.photon_production
            self.assertEqual( True, isinstance( data, Multiplicities ) )

            self.assertEqual( None, data.total_multiplicity )
            self.assertEqual( 1, len( data.photon_partial_multiplicities ) )

            self.assertEqual( 1, data.NK )
            self.assertEqual( 1, data.number_photons )
            self.assertEqual( 1, data.LO )
            self.assertEqual( 1, data.representation )

            partial = data.photon_partial_multiplicities[0];
            self.assertAlmostEqual( 0.0, partial.EG )
            self.assertAlmostEqual( 0.0, partial.photon_or_binding_energy )
            self.assertAlmostEqual( 0.0, partial.ES )
            self.assertAlmostEqual( 0.0, partial.level_energy )
            self.assertEqual( 0, partial.LP )
            self.assertEqual( 0, partial.primary_photon_flag )
            self.assertEqual( 1, partial.LF )
            self.assertEqual( 1, partial.LAW )
            self.assertEqual( 2, partial.NP )
            self.assertEqual( 1, partial.NR )
            self.assertEqual( 1, len( partial.interpolants ) )
            self.assertEqual( 1, len( partial.boundaries ) )
            self.assertEqual( 2, partial.interpolants[0] )
            self.assertEqual( 2, partial.boundaries[0] )
            self.assertEqual( 2, len( partial.energies ) )
            self.assertEqual( 2, len( partial.multiplicities ) )
            self.assertAlmostEqual( 1e-5, partial.energies[0] )
            self.assertAlmostEqual( 3e+7, partial.energies[1] )
            self.assertAlmostEqual( 8.579050e+0, partial.multiplicities[0] )
            self.assertAlmostEqual( 1.487778e+1, partial.multiplicities[1] )

            self.assertEqual( 4, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lo1 + self.valid_SEND,
                              chunk.to_string( 9228, 12 ) )

        def verify_chunk_lo2lg1( self, chunk ) :

            # verify content
            self.assertEqual( 51, chunk.MT )
            self.assertEqual( 51, chunk.section_number )

            self.assertAlmostEqual( 92235., chunk.ZA )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )

            data = chunk.photon_production
            self.assertEqual( True, isinstance( data, TransitionProbabilities ) )
            self.assertEqual( 2, data.LO )
            self.assertEqual( 2, data.representation )

            self.assertAlmostEqual( 5.170900e+4, data.ES )
            self.assertAlmostEqual( 5.170900e+4, data.highest_energy_level )
            self.assertEqual( 1, data.LG )
            self.assertEqual( 1, data.transition_type )
            self.assertEqual( 2, data.NT )
            self.assertEqual( 2, data.number_transitions )

            self.assertEqual( 2, len( data.E ) )
            self.assertEqual( 2, len( data.energies ) )
            self.assertEqual( 2, len( data.TP ) )
            self.assertEqual( 2, len( data.transition_probabilities ) )
            self.assertEqual( 2, len( data.GP ) )
            self.assertEqual( 2, len( data.conditional_probabilities ) )
            self.assertAlmostEqual( 1.304000e+4, data.E[0] )
            self.assertAlmostEqual( 7.700000e+1, data.E[1] )
            self.assertAlmostEqual( 1.304000e+4, data.energies[0] )
            self.assertAlmostEqual( 7.700000e+1, data.energies[1] )
            self.assertAlmostEqual( 2.709000e-1, data.TP[0] )
            self.assertAlmostEqual( 7.291000e-1, data.TP[1] )
            self.assertAlmostEqual( 2.709000e-1, data.transition_probabilities[0] )
            self.assertAlmostEqual( 7.291000e-1, data.transition_probabilities[1] )
            self.assertAlmostEqual( 1.0, data.GP[0] )
            self.assertAlmostEqual( 1.0, data.GP[1] )
            self.assertAlmostEqual( 1.0, data.conditional_probabilities[0] )
            self.assertAlmostEqual( 1.0, data.conditional_probabilities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lo2lg1 + self.valid_SEND,
                              chunk.to_string( 9228, 12 ) )

        def verify_chunk_lo2lg2( self, chunk ) :

            # verify content
            self.assertEqual( 51, chunk.MT )
            self.assertEqual( 51, chunk.section_number )

            self.assertAlmostEqual( 92235., chunk.ZA )
            self.assertAlmostEqual( 2.330250e+2, chunk.AWR )
            self.assertAlmostEqual( 2.330250e+2, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )

            data = chunk.photon_production
            self.assertEqual( True, isinstance( data, TransitionProbabilities ) )
            self.assertEqual( 2, data.LO )
            self.assertEqual( 2, data.representation )

            self.assertAlmostEqual( 5.170900e+4, data.ES )
            self.assertAlmostEqual( 5.170900e+4, data.highest_energy_level )
            self.assertEqual( 2, data.LG )
            self.assertEqual( 2, data.transition_type )
            self.assertEqual( 2, data.NT )
            self.assertEqual( 2, data.number_transitions )

            self.assertEqual( 2, len( data.E ) )
            self.assertEqual( 2, len( data.energies ) )
            self.assertEqual( 2, len( data.TP ) )
            self.assertEqual( 2, len( data.transition_probabilities ) )
            self.assertEqual( 2, len( data.GP ) )
            self.assertEqual( 2, len( data.conditional_probabilities ) )
            self.assertAlmostEqual( 1.304000e+4, data.E[0] )
            self.assertAlmostEqual( 7.700000e+1, data.E[1] )
            self.assertAlmostEqual( 1.304000e+4, data.energies[0] )
            self.assertAlmostEqual( 7.700000e+1, data.energies[1] )
            self.assertAlmostEqual( 2.709000e-1, data.TP[0] )
            self.assertAlmostEqual( 7.291000e-1, data.TP[1] )
            self.assertAlmostEqual( 2.709000e-1, data.transition_probabilities[0] )
            self.assertAlmostEqual( 7.291000e-1, data.transition_probabilities[1] )
            self.assertAlmostEqual( 3.215434e-3, data.GP[0] )
            self.assertAlmostEqual( 3.144654e-3, data.GP[1] )
            self.assertAlmostEqual( 3.215434e-3, data.conditional_probabilities[0] )
            self.assertAlmostEqual( 3.144654e-3, data.conditional_probabilities[1] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lo2lg2 + self.valid_SEND,
                              chunk.to_string( 9228, 12 ) )

        # the data is given explicitly
        chunk = Section( mt = 18, zaid = 92235., awr = 2.330250e+2,
                         production =
                           Multiplicities(
                             PartialMultiplicity( 0.0, 0.0, 0, 1,
                                                  [ 2 ], [ 2 ],
                                                  [ 1e-5, 3e+7 ],
                                                  [ 8.579050e+0, 1.487778e+1 ] ) ) )

        verify_chunk_lo1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lo1 + self.valid_SEND )

        verify_chunk_lo1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lo1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 12 ).section( 18 ).parse()

        verify_chunk_lo1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lo1( self, copy )

        # the data is given explicitly
        chunk = Section( mt = 51, zaid = 92235., awr = 2.330250e+2,
                         production = TransitionProbabilities( 5.170900e+4,
                                                               [ 1.304000e+4, 7.700000e+1 ],
                                                               [ 2.709000e-1, 7.291000e-1 ] ) )

        verify_chunk_lo2lg1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lo2lg1 + self.valid_SEND )

        verify_chunk_lo2lg1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lo2lg1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 12 ).section( 51 ).parse()

        verify_chunk_lo2lg1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lo2lg1( self, copy )

        # the data is given explicitly
        chunk = Section( mt = 51, zaid = 92235., awr = 2.330250e+2,
                         production = TransitionProbabilities( 5.170900e+4,
                                                               [ 1.304000e+4, 7.700000e+1 ],
                                                               [ 2.709000e-1, 7.291000e-1 ],
                                                               [ 3.215434e-3, 3.144654e-3 ] ) )

        verify_chunk_lo2lg2( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lo2lg2 + self.valid_SEND )

        verify_chunk_lo2lg2( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lo2lg2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 12 ).section( 51 ).parse()

        verify_chunk_lo2lg2( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lo2lg2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_lo1 + self.invalid_SEND )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_lo2lg1 + self.invalid_SEND )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk_lo2lg2 + self.invalid_SEND )

if __name__ == '__main__' :

    unittest.main()
