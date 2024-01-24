# standard imports
import unittest

# third party imports

# local imports
from ENDFtk.MF1.MT460 import Section
from ENDFtk.MF1.MT460 import ContinuousPhotons
from ENDFtk.MF1.MT460 import DiscretePhotonMultiplicity
from ENDFtk.MF1.MT460 import DiscretePhotons
from ENDFtk.tree import Tape

class Test_ENDFtk_MF1_MT460_Section( unittest.TestCase ) :
    """Unit test for the Section class."""

    chunk_lo1 = ( ' 9.223500+4 2.330248+2          1          0          2          09228 1460     \n'
                  ' 1.000000-1 0.000000+0          1          0          1          29228 1460     \n'
                  '          2          4                                            9228 1460     \n'
                  ' 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n'
                  ' 2.000000-1 0.000000+0          2          0          1          39228 1460     \n'
                  '          3          2                                            9228 1460     \n'
                  ' 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n' )

    chunk_lo2 = ( ' 9.223500+4 2.330248+2          2          0          0          09228 1460     \n'
                  ' 0.000000+0 0.000000+0          0          0          6          09228 1460     \n'
                  ' 1.333600-2 3.273900-2 1.207800-1 3.027800-1 8.494900-1 2.853000+09228 1460     \n' )

    invalid_lo = ( ' 9.223500+4 2.330248+2          0          0          2          09228 1460     \n'
                   ' 1.000000-1 0.000000+0          1          0          1          29228 1460     \n'
                   '          2          4                                            9228 1460     \n'
                   ' 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n'
                   ' 2.000000-1 0.000000+0          2          0          1          39228 1460     \n'
                   '          3          2                                            9228 1460     \n'
                   ' 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n' )

    invalid_ng = ( ' 9.223500+4 2.330248+2          1          0          0          09228 1460     \n'
                   ' 1.000000-1 0.000000+0          1          0          1          29228 1460     \n'
                   '          2          4                                            9228 1460     \n'
                   ' 0.000000+0 4.877451-1 4.000000+0 1.715686-1                      9228 1460     \n'
                   ' 2.000000-1 0.000000+0          2          0          1          29228 1460     \n'
                   '          2          4                                            9228 1460     \n'
                   ' 0.000000+0 1.691176-1 5.000000+0 2.450980-3 9.000000+0 1.691176-19228 1460     \n' )

    valid_TPID = 'Just a tape identifier                                                          \n'
    valid_SEND = '                                                                  9228 1  0     \n'
    valid_FEND = '                                                                  9228 0  0     \n'
    valid_MEND = '                                                                     0 0  0     \n'
    valid_TEND = '                                                                    -1 0  0     \n'
    invalid_SEND = '                                                                  9228 1  1     \n'

    def test_section( self ) :

        def verify_chunk_lo1( self, chunk ) :

            # verify content
            self.assertEqual( 460, chunk.MT )
            self.assertEqual( 460, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertAlmostEqual( 233.0248, chunk.AWR )
            self.assertAlmostEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 1, chunk.LO )
            self.assertEqual( 1, chunk.representation )
            self.assertEqual( 2, chunk.NG )
            self.assertEqual( 2, chunk.number_discrete_photons )

            photons = chunk.delayed_photons

            self.assertEqual( 1, photons.LO )
            self.assertEqual( 1, photons.representation )
            self.assertEqual( 2, photons.NG )
            self.assertEqual( 2, photons.number_discrete_photons )

            self.assertEqual( 2, len( photons.photons ) )

            self.assertAlmostEqual( 0.1, photons.photons[0].E )
            self.assertEqual( 1, photons.photons[0].index )
            self.assertEqual( 1, photons.photons[0].NR )
            self.assertEqual( 2, photons.photons[0].NP )
            self.assertEqual( 1, len( photons.photons[0].interpolants ) )
            self.assertEqual( 1, len( photons.photons[0].boundaries ) )
            self.assertEqual( 4, photons.photons[0].interpolants[0] )
            self.assertEqual( 2, photons.photons[0].boundaries[0] )
            self.assertEqual( 2, len( photons.photons[0].time ) )
            self.assertEqual( 2, len( photons.photons[0].multiplicities ) )
            self.assertAlmostEqual( 0., photons.photons[0].time[0] )
            self.assertAlmostEqual( 4., photons.photons[0].time[1] )
            self.assertAlmostEqual( 4.877451e-1, photons.photons[0].multiplicities[0] )
            self.assertAlmostEqual( 1.715686e-1, photons.photons[0].multiplicities[1] )

            self.assertAlmostEqual( 0.2, photons.photons[1].E )
            self.assertEqual( 2, photons.photons[1].index )
            self.assertEqual( 1, photons.photons[1].NR )
            self.assertEqual( 3, photons.photons[1].NP )
            self.assertEqual( 1, len( photons.photons[1].interpolants ) )
            self.assertEqual( 1, len( photons.photons[1].boundaries ) )
            self.assertEqual( 2, photons.photons[1].interpolants[0] )
            self.assertEqual( 3, photons.photons[1].boundaries[0] )
            self.assertEqual( 3, len( photons.photons[1].time ) )
            self.assertEqual( 3, len( photons.photons[1].multiplicities ) )
            self.assertAlmostEqual( 0., photons.photons[1].time[0] )
            self.assertAlmostEqual( 5., photons.photons[1].time[1] )
            self.assertAlmostEqual( 9., photons.photons[1].time[2] )
            self.assertAlmostEqual( 1.691176e-1, photons.photons[1].multiplicities[0] )
            self.assertAlmostEqual( 2.450980e-3, photons.photons[1].multiplicities[1] )
            self.assertAlmostEqual( 1.691176e-1, photons.photons[1].multiplicities[2] )

            self.assertEqual( 7, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lo1 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        def verify_chunk_lo2( self, chunk ) :

            # verify content
            self.assertEqual( 460, chunk.MT )
            self.assertEqual( 460, chunk.section_number )
            self.assertEqual( 92235, chunk.ZA )
            self.assertEqual( 92235, chunk.target_identifier )
            self.assertEqual( 233.0248, chunk.AWR )
            self.assertEqual( 233.0248, chunk.atomic_weight_ratio )
            self.assertEqual( 2, chunk.LO )
            self.assertEqual( 2, chunk.representation )
            self.assertEqual( 0, chunk.NG )
            self.assertEqual( 0, chunk.number_discrete_photons )

            photons = chunk.delayed_photons

            self.assertEqual( 2, photons.LO )
            self.assertEqual( 2, photons.representation )
            self.assertEqual( 0, photons.NG )
            self.assertEqual( 0, photons.number_discrete_photons )
            self.assertEqual( 6, photons.NNF )
            self.assertEqual( 6, photons.number_precursors )

            self.assertEqual( 6, len( photons.lambdas ) )
            self.assertEqual( 6, len( photons.decay_constants ) )
            self.assertAlmostEqual( 0.013336, photons.lambdas[0] )
            self.assertAlmostEqual( 0.032739, photons.lambdas[1] )
            self.assertAlmostEqual( 0.12078, photons.lambdas[2] )
            self.assertAlmostEqual( 0.30278, photons.lambdas[3] )
            self.assertAlmostEqual( 0.84949, photons.lambdas[4] )
            self.assertAlmostEqual( 2.853000, photons.lambdas[5] )
            self.assertAlmostEqual( 0.013336, photons.decay_constants[0] )
            self.assertAlmostEqual( 0.032739, photons.decay_constants[1] )
            self.assertAlmostEqual( 0.12078, photons.decay_constants[2] )
            self.assertAlmostEqual( 0.30278, photons.decay_constants[3] )
            self.assertAlmostEqual( 0.84949, photons.decay_constants[4] )
            self.assertAlmostEqual( 2.853000, photons.decay_constants[5] )

            self.assertEqual( 3, chunk.NC )

            # verify string
            self.assertEqual( self.chunk_lo2 + self.valid_SEND,
                              chunk.to_string( 9228, 1 ) )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         photons = DiscretePhotons(
                                     [ DiscretePhotonMultiplicity( 0.1, 1, [ 2 ], [ 4 ], [ 0., 4. ],
                                                                   [ 4.877451e-1, 1.715686e-1 ] ),
                                       DiscretePhotonMultiplicity( 0.2, 2, [ 3 ], [ 2 ], [ 0., 5., 9 ],
                                                                   [ 1.691176e-1, 2.450980e-3, 1.691176e-1 ] ) ] ) )

        verify_chunk_lo1( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lo1 + self.valid_SEND )

        verify_chunk_lo1( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lo1 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 460 ).parse()

        verify_chunk_lo1( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lo1( self, copy )

        # the data is given explicitly
        chunk = Section( zaid = 92235, awr = 233.0248,
                         photons = ContinuousPhotons( [ 1.333600e-2, 3.273900e-2,
                                                        1.207800e-1, 3.027800e-1,
                                                        8.494900e-1, 2.853000e+0 ] ) )

        verify_chunk_lo2( self, chunk )

        # the data is read from a string
        chunk = Section.from_string( self.chunk_lo2 + self.valid_SEND )

        verify_chunk_lo2( self, chunk )

        # the data is retrieved from a tree element and parsed
        tape = Tape.from_string( self.valid_TPID + self.chunk_lo2 +
                                 self.valid_SEND + self.valid_FEND +
                                 self.valid_MEND + self.valid_TEND )
        chunk = tape.material( 9228 ).file( 1 ).section( 460 ).parse()

        verify_chunk_lo2( self, chunk )

        # the data is copied
        copy = Section( chunk )

        verify_chunk_lo2( self, copy )

    def test_failures( self ) :

        print( '\n' )

        # illegal SEND
        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.chunk + self.invalid_SEND )

        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid_lo + self.valid_SEND )

        with self.assertRaises( Exception ) :

            chunk = Section.from_string( self.invalid_ng + self.valid_SEND )

if __name__ == '__main__' :

    unittest.main()
