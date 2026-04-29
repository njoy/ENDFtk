"""
MT457 - radioactive decay data
"""
from __future__ import annotations
import pybind11_stubgen.typing_ext
import typing
__all__: list[str] = ['AverageDecayEnergies', 'ContinuousSpectrum', 'DecayMode', 'DecayModes', 'DecaySpectrum', 'DiscreteSpectrum', 'Section']
class AverageDecayEnergies:
    """
    MF8 MT457 section - half life information and average decay energies for
                        radiation types
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> AverageDecayEnergies:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, halflife: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], energies: list[typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]]) -> None:
        """
        Initialise the component
        
        Arguments:
            self        the component
            halflife    the half life and its associated uncertainty
            energies    the decay energies and uncertainties for the various
                        radiation types (either 3 or 17 pairs)
        """
    @typing.overload
    def __init__(self) -> None:
        """
        Initialise the component for a stable nuclide
        
        Arguments:
            self            the component
        """
    @typing.overload
    def __init__(self, component: AverageDecayEnergies) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The decay energies and their uncertainties
        """
    @property
    def EEM(self) -> ...:
        """
        The decay energy and uncertainty electromagnetic radiation
        """
    @property
    def EHP(self) -> ...:
        """
        The decay energy and uncertainty for heavy particle decay
        """
    @property
    def ELP(self) -> ...:
        """
        The decay energy and uncertainty for light particle decay
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NCE(self) -> int:
        """
        The number of decay energies
        """
    @property
    def T(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The half life and its uncertainty
        """
    @property
    def decay_energies(self) -> ...:
        """
        The decay energies and their uncertainties
        """
    @property
    def electromagnetic_decay_energy(self) -> ...:
        """
        The decay energy and uncertainty electromagnetic radiation
        """
    @property
    def half_life(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The half life and its uncertainty
        """
    @property
    def heavy_particle_decay_energy(self) -> ...:
        """
        The decay energy and uncertainty for heavy particle decay
        """
    @property
    def light_particle_decay_energy(self) -> ...:
        """
        The decay energy and uncertainty for light particle decay
        """
    @property
    def number_decay_energies(self) -> int:
        """
        The number of decay energies
        """
class ContinuousSpectrum:
    """
    MF8 MT457 section - continuous decay spectrum
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> ContinuousSpectrum:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, chain: float, boundaries: list[int], interpolants: list[int], energies: list[float], spectrum: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            chain           the ENDF decay chain
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            spectrum        the spectral values
        """
    @typing.overload
    def __init__(self, component: ContinuousSpectrum) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def E(self) -> ...:
        """
        The energy values
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def NBT(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NP(self) -> int:
        """
        The number of points
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def RP(self) -> ...:
        """
        The spectral values
        """
    @property
    def RTYP(self) -> float:
        """
        The decay chain
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def decay_chain(self) -> float:
        """
        The decay chain
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def number_points(self) -> int:
        """
        The number of points
        """
    @property
    def spectral_values(self) -> ...:
        """
        The spectral values
        """
class DecayMode:
    """
    MF8 MT457 section - a single ENDF decay mode
    """
    @typing.overload
    def __init__(self, chain: float, state: float, q: float, dq: float, ratio: float, dratio: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            chain     the decay chain
            state     the final isomeric state
            q         the Q value
            dq        the uncertainty on the Q value
            ratio     the branching ratio value
            dratio    the uncertainty on the branching ratio value
        """
    @typing.overload
    def __init__(self, component: DecayMode) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    @property
    def BR(self) -> ...:
        """
        The branching ratio and its uncertainty
        """
    @property
    def Q(self) -> ...:
        """
        The Q value and its uncertainty
        """
    @property
    def RFS(self) -> float:
        """
        The final isomeric state
        """
    @property
    def RTYP(self) -> float:
        """
        The decay chain
        """
    @property
    def branching_ratio(self) -> ...:
        """
        The branching ratio and its uncertainty
        """
    @property
    def decay_chain(self) -> float:
        """
        The decay chain
        """
    @property
    def final_isomeric_state(self) -> float:
        """
        The final isomeric state
        """
    @property
    def q_value(self) -> ...:
        """
        The Q value and its uncertainty
        """
class DecayModes:
    """
    MF8 MT457 section - decay modes and branching ratio information
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DecayModes:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, spin: float, parity: float, modes: list[DecayMode]) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            spin      the spin of the nuclide
            parity    the parity (used if spin is zero)
            modes     the decay decay modes
        """
    @typing.overload
    def __init__(self, spin: float, parity: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self      the component
            spin      the spin of the nuclide
            parity    the parity (used if spin is zero)
        """
    @typing.overload
    def __init__(self, component: DecayModes) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NDK(self) -> int:
        """
        The number of decay modes
        """
    @property
    def PAR(self) -> float:
        """
        The target parity
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def decay_modes(self) -> list[DecayMode]:
        """
        The decay mode information
        """
    @property
    def number_decay_modes(self) -> int:
        """
        The number of decay modes
        """
    @property
    def parity(self) -> float:
        """
        The target parity
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
class DecaySpectrum:
    """
    MF8 MT457 section - spectrum information for a specific decay particle type
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DecaySpectrum:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, type: float, dnorm: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], dspectra: list[DiscreteSpectrum]) -> None:
        """
        Initialise the component for discrete spectra only (LCON=0)
        
        Arguments:
            self        the component
            type        the particle type for which data is given
            dnorm       the discrete normalisation factor and its uncertainty
            energy      the average decay energy and its uncertainty
            dspectra    the discrete spectra
        """
    @typing.overload
    def __init__(self, type: float, cnorm: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], cspectrum: ContinuousSpectrum) -> None:
        """
        Initialise the component for a continuous spectrum only (LCON=1)
        
        Arguments:
            self         the component
            type         the particle type for which spectral data is given
            cnorm        the continuous normalisation factor and its uncertainty
            energy       the average decay energy and its uncertainty
            cspectrum    the continuous spectrum
        """
    @typing.overload
    def __init__(self, type: float, dnorm: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], cnorm: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], dspectra: list[DiscreteSpectrum], cspectrum: ContinuousSpectrum) -> None:
        """
        Initialise the component for discrete and continuous spectra (LCON=2)
        
        Arguments:
            self         the component
            type         the particle type for which spectral data is given
            dnorm        the spectra normalisation factor and its uncertainty
            cnorm        the continuous normalisation factor and its uncertainty
            energy       the average decay energy and its uncertainty
            dspectra     the discrete spectra
            cspectrum    the continuous spectrum
        """
    @typing.overload
    def __init__(self, component: DecaySpectrum) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ERAV(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The average decay energy and its uncertainty
        """
    @property
    def FC(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The continuous normalisation factor and its uncertainty
        """
    @property
    def FD(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The discrete normalisation factor and its uncertainty
        """
    @property
    def LCON(self) -> int:
        """
        The spectral type flag
        """
    @property
    def LCOV(self) -> int:
        """
        The covariance data flag
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NER(self) -> int:
        """
        The number of discrete decay spectra
        """
    @property
    def STYP(self) -> float:
        """
        The radiation type STYP for which spectral data is given
        """
    @property
    def average_decay_energy(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The average decay energy and its uncertainty
        """
    @property
    def continuous_normalisation_factor(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The continuous normalisation factor and its uncertainty
        """
    @property
    def continuous_spectrum(self) -> ContinuousSpectrum | None:
        """
        The continuous spectrum, if it is defined
        """
    @property
    def covariance_flag(self) -> int:
        """
        The covariance data flag
        """
    @property
    def discrete_normalisation_factor(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The discrete normalisation factor and its uncertainty
        """
    @property
    def discrete_spectra(self) -> ...:
        """
        The discrete spectra, if any are defined
        """
    @property
    def number_discrete_spectra(self) -> int:
        """
        The number of discrete decay spectra
        """
    @property
    def radiation_type(self) -> float:
        """
        The radiation type STYP for which spectral data is given
        """
    @property
    def spectral_type_flag(self) -> int:
        """
        The spectral type flag
        """
class DiscreteSpectrum:
    """
    MF8 MT457 section - discrete spectrum information
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DiscreteSpectrum:
        """
        Read the component from a string
        
        An exception is raised if something goes wrong while reading the
        component
        
        Arguments:
            string    the string representing the component
            mat       the MAT number of the section
            mf        the MF number of the section
            mt        the MT number of the section
        """
    @typing.overload
    def __init__(self, chain: float, energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], intensity: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], type: float) -> None:
        """
        Initialise the component
        
        Arguments:
            self         the component
            chain        the ENDF decay chain
            energy       the energy and uncertainty
            intensity    the relative intensity and uncertainty
            type         the transition type
        """
    @typing.overload
    def __init__(self, chain: float, energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], intensity: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], type: float, ris: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]) -> None:
        """
        Initialise the component
        
        Arguments:
            self         the component
            chain        the ENDF decay chain
            energy       the energy and uncertainty
            intensity    the relative intensity and uncertainty
            type         the transition type
            ris          internal pair formation coefficient or positron intensity
        """
    @typing.overload
    def __init__(self, chain: float, energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], intensity: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], type: float, ris: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], ricc: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]) -> None:
        """
        Initialise the component
        
        Arguments:
            self         the component
            chain        the ENDF decay chain
            energy       the energy and uncertainty
            intensity    the relative intensity and uncertainty
            type         the transition type
            ris          internal pair formation coefficient or positron intensity
            ricc         the total internal conversion coefficient
        """
    @typing.overload
    def __init__(self, chain: float, energy: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], intensity: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], type: float, ris: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], ricc: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], rick: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)], ricl: typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]) -> None:
        """
        Initialise the component
        
        Arguments:
            self         the component
            chain        the ENDF decay chain
            energy       the energy and uncertainty
            intensity    the relative intensity and uncertainty
            type         the transition type
            ris          internal pair formation coefficient or positron intensity
            ricc         the total internal conversion coefficient
            rick         the K shell internal conversion coefficient
            ricl         the L shell internal conversion coefficient
        """
    @typing.overload
    def __init__(self, component: DiscreteSpectrum) -> None:
        """
        Copy the component
        
        Arguments:
            self         the component
            component    the component to be copied
        """
    def to_string(self, mat: int, mf: int, mt: int) -> str:
        """
        Return the string representation of the component
        
        Arguments:
            self    the component
            mat     the MAT number to be used
            mf      the MF number to be used
            mt      the MT number to be used
        """
    @property
    def ER(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The discrete energy value and uncertainty
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def NT(self) -> int:
        """
        The number of entries
        """
    @property
    def RI(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The relative intensity and uncertainty
        """
    @property
    def RICC(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The total internal conversion coefficient value and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def RICK(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The K shell internal conversion coefficient  and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def RICL(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The L shell internal conversion coefficient  and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def RIS(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The RIS value and its uncertainty, the internal pair formation
        coefficient (STYP=0.0) or the positron intensity (STYP=2.0)
        """
    @property
    def RTYP(self) -> float:
        """
        The decay chain responsible for this spectrum
        """
    @property
    def TYPE(self) -> float:
        """
        The transition type for beta and electron capture
        """
    @property
    def decay_chain(self) -> float:
        """
        The decay chain responsible for this spectrum
        """
    @property
    def discrete_energy(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The discrete energy value and uncertainty
        """
    @property
    def internal_conversion_coefficient_k_shell(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The K shell internal conversion coefficient  and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def internal_conversion_coefficient_l_shell(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The L shell internal conversion coefficient  and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def internal_pair_formation_coefficient(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The RIS value and its uncertainty, the internal pair formation
        coefficient (STYP=0.0) or the positron intensity (STYP=2.0)
        """
    @property
    def relative_intensity(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The relative intensity and uncertainty
        """
    @property
    def total_internal_conversion_coefficient(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The total internal conversion coefficient value and its uncertainty
        (STYP=0.0 only)
        """
    @property
    def type(self) -> float:
        """
        The transition type for beta and electron capture
        """
class Section:
    """
    MF8 MT457 section - radioactive decay data
    """
    @staticmethod
    def from_string(section: str) -> Section:
        """
        Read the section from a string
        
        An exception is raised if something goes wrong while reading the
        section
        
        Arguments:
            section    the string representing the section
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, lis: int, liso: int, spin: float, parity: float) -> None:
        """
        Initialise the section for a stable isotope
        
        Arguments:
            self      the section
            zaid      the material ZAID value
            awr       the atomic weight ratio
            lis       the excited level number
            liso      the isomeric state number
            spin      the nuclide spin
            parity    the nuclide parity
        """
    @typing.overload
    def __init__(self, zaid: float, awr: float, lis: int, liso: int, energies: AverageDecayEnergies, modes: DecayModes, spectra: list[DecaySpectrum]) -> None:
        """
        Initialise the section for a radioactive isotope
        
        Arguments:
            self        the section
            zaid        the material ZAID value
            awr         the atomic weight ratio
            lis         the excited level number
            liso        the isomeric state number
            energies    the average decay energies
            modes       the decay modes
            spectra     the decay spectra
        """
    @typing.overload
    def __init__(self, section: Section) -> None:
        """
        Initialise the section with another section
        
        Arguments:
            self       the section
            section    the section to be copied
        """
    def to_string(self, mat: int, mf: int) -> str:
        """
        Return the string representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
            mf      the MF number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the section
        
        Arguments:
            self    the section
            mat     the MAT number to be used
        """
    @property
    def AWR(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def LIS(self) -> int:
        """
        The excited state number
        """
    @property
    def LISO(self) -> int:
        """
        The isomeric state number
        """
    @property
    def MT(self) -> int:
        """
        The MT number of the section
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this section
        """
    @property
    def NSP(self) -> int:
        """
        The number of decay spectra
        """
    @property
    def NST(self) -> bool:
        """
        The stability flag
        """
    @property
    def PAR(self) -> float:
        """
        The target parity
        """
    @property
    def SPI(self) -> float:
        """
        The target spin
        """
    @property
    def T(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The half life and its uncertainty
        """
    @property
    def ZA(self) -> int:
        """
        The ZA identifier for the section
        """
    @property
    def atomic_weight_ratio(self) -> float:
        """
        The atomic weight ratio for the section
        """
    @property
    def average_decay_energies(self) -> AverageDecayEnergies:
        """
        The half life and decay energy information
        """
    @property
    def decay_modes(self) -> DecayModes:
        """
        The spin, parity and decay mode information
        """
    @property
    def decay_spectra(self) -> ...:
        """
        The particle spectra
        """
    @property
    def excited_state(self) -> int:
        """
        The excited state number
        """
    @property
    def half_life(self) -> typing.Annotated[list[float], pybind11_stubgen.typing_ext.FixedSize(2)]:
        """
        The half life and its uncertainty
        """
    @property
    def is_stable(self) -> bool:
        """
        The stability flag
        """
    @property
    def isomeric_state(self) -> int:
        """
        The isomeric state number
        """
    @property
    def number_decay_spectra(self) -> int:
        """
        The number of decay spectra
        """
    @property
    def parity(self) -> float:
        """
        The target parity
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def spin(self) -> float:
        """
        The target spin
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
