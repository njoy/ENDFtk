"""
MF5 - energy distributions of secondary particles
"""
from __future__ import annotations
import typing
from . import MT18
from . import MT455
__all__: list[str] = ['DistributionFunction', 'EffectiveTemperature', 'EvaporationSpectrum', 'File', 'GeneralEvaporationSpectrum', 'MT18', 'MT455', 'MadlandNixSpectrum', 'MaxwellianFissionSpectrum', 'OutgoingEnergyDistribution', 'Parameter', 'PartialDistribution', 'Probability', 'Section', 'TabulatedSpectrum', 'WattSpectrum']
class DistributionFunction:
    """
    MF5 section - a distribution function y = f(x)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> DistributionFunction:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], x: list[float], g: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            x               the x values
            g               the function values
        """
    @typing.overload
    def __init__(self, component: DistributionFunction) -> None:
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
    def G(self) -> ...:
        """
        The function values
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
    def X(self) -> ...:
        """
        The x values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
class EffectiveTemperature:
    """
    MF5 section - the effective temperature of an evaporation spectrum
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EffectiveTemperature:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], thetas: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            thetas          the theta values
        """
    @typing.overload
    def __init__(self, component: EffectiveTemperature) -> None:
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def thetas(self) -> ...:
        """
        The theta values
        """
class EvaporationSpectrum:
    """
    MF5 section - the evaporation spectrum (LF=9)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> EvaporationSpectrum:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], thetas: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            thetas          the theta values
        """
    @typing.overload
    def __init__(self, component: EvaporationSpectrum) -> None:
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
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def thetas(self) -> ...:
        """
        The theta values
        """
class File:
    """
    MF5 file - energy distributions of secondary particles
    """
    @staticmethod
    def from_string(file: str) -> File:
        """
        Read the file from a string
        
        An exception is raised if something goes wrong while reading the
        file
        
        Arguments:
            file    the string representing the file
        """
    def MT(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    @typing.overload
    def __init__(self, sections: list[Section]) -> None:
        """
        Initialise the file
        
        Arguments:
            self       the file
            sections   the sections to be put into the file
        """
    @typing.overload
    def __init__(self, file: File) -> None:
        """
        Initialise the file with another file
        
        Arguments:
            self    the file
            file    the file to be copied
        """
    def has_MT(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def has_section(self, mt: int) -> bool:
        """
        Return whether or not the file has a section with the given MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section
        """
    def section(self, mt: int) -> Section:
        """
        Return the section with the requested MT number
        
        Arguments:
            self    the file
            mt      the MT number of the section to be returned
        """
    def to_string(self, mat: int) -> str:
        """
        The string representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    def to_tree(self, mat: int) -> ...:
        """
        Return the ENDF tree representation of the file
        
        Arguments:
            self    the file
            mat     the MAT number to be used
        """
    @property
    def MF(self) -> int:
        """
        The MF number of the file
        """
    @property
    def MTs(self) -> ...:
        """
        The sections defined in the file
        """
    @property
    def file_number(self) -> int:
        """
        The MF number of the file
        """
    @property
    def sections(self) -> ...:
        """
        The sections defined in the file
        """
class GeneralEvaporationSpectrum:
    """
    MF5 section - the general evaporation spectrum (LF=5)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> GeneralEvaporationSpectrum:
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
    def __init__(self, temperature: EffectiveTemperature, distribution: DistributionFunction) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            temperature     the effective temperature
            distribution    the distribution function g(x)
        """
    @typing.overload
    def __init__(self, component: GeneralEvaporationSpectrum) -> None:
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
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def distribution_function(self) -> DistributionFunction:
        """
        The distribution function g(x)
        """
    @property
    def effective_temperature(self) -> EffectiveTemperature:
        """
        The effective temperature
        """
    @property
    def g(self) -> DistributionFunction:
        """
        The distribution function g(x)
        """
    @property
    def theta(self) -> EffectiveTemperature:
        """
        The effective temperature
        """
class MadlandNixSpectrum:
    """
    MF5 section - the Madland Nix fission neutron spectrum (LF=12)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> MadlandNixSpectrum:
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
    def __init__(self, efl: float, efh: float, boundaries: list[int], interpolants: list[int], energies: list[float], temperatures: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            efl             the light fission fragment kinetic energy
            efh             the heavy fission fragment kinetic energy
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            temperatures    the maximum temperature values
        """
    @typing.overload
    def __init__(self, component: MadlandNixSpectrum) -> None:
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
    def EFH(self) -> float:
        """
        The average kinetic energy of the average heavy fission fragment
        """
    @property
    def EFL(self) -> float:
        """
        The average kinetic energy of the average light fission fragment
        """
    @property
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
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
    def TM(self) -> ...:
        """
        The maximum temperature parameter values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def energies(self) -> ...:
        """
        The energy values
        """
    @property
    def heavy_fragment_energy(self) -> float:
        """
        The average kinetic energy of the average heavy fission fragment
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def light_fragment_energy(self) -> float:
        """
        The average kinetic energy of the average light fission fragment
        """
    @property
    def maximum_temperature_values(self) -> ...:
        """
        The maximum temperature parameter values
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
class MaxwellianFissionSpectrum:
    """
    MF5 section - the Maxwellian fission spectrum (LF=7)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> MaxwellianFissionSpectrum:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], thetas: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            thetas          the theta values
        """
    @typing.overload
    def __init__(self, component: MaxwellianFissionSpectrum) -> None:
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
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def thetas(self) -> ...:
        """
        The theta values
        """
class OutgoingEnergyDistribution:
    """
    MF5 section - outgoing energy distribution for a fixed value of E
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> OutgoingEnergyDistribution:
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
    def __init__(self, incident: float, boundaries: list[int], interpolants: list[int], energies: list[float], probabilities: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            incident         the incident energy value
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the outgoing energy values
            probabilities    the probability values
        """
    @typing.overload
    def __init__(self, component: OutgoingEnergyDistribution) -> None:
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
    def E(self) -> float:
        """
        The incident energy value
        """
    @property
    def EP(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def G(self) -> ...:
        """
        The distribution probabilities
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def incident_energy(self) -> float:
        """
        The incident energy value
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
    def outgoing_energies(self) -> ...:
        """
        The outgoing energy values
        """
    @property
    def probabilities(self) -> ...:
        """
        The distribution probabilities
        """
class Parameter:
    """
    MF5 section - a parameter function y = f(E)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> Parameter:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], energies: list[float], values: list[float]) -> None:
        """
        Initialise the component
        
        Arguments:
            self            the component
            boundaries      the interpolation range boundaries
            interpolants    the interpolation types for each range
            energies        the energy values
            values          the parameter values
        """
    @typing.overload
    def __init__(self, component: Parameter) -> None:
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
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def values(self) -> ...:
        """
        The parameter values
        """
class PartialDistribution:
    """
    MF5 section - a distribution subsection of an MF5 section
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> PartialDistribution:
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
    def __init__(self, probability: Probability, spectrum: TabulatedSpectrum | GeneralEvaporationSpectrum | MaxwellianFissionSpectrum | EvaporationSpectrum | WattSpectrum | MadlandNixSpectrum) -> None:
        """
        Initialise the component
        
        Arguments:
            self           the component
            probability    the probability
            spectrum       the spectrum
        """
    @typing.overload
    def __init__(self, component: PartialDistribution) -> None:
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
    def U(self) -> float:
        """
        The energy limit constant
        """
    @property
    def distribution(self) -> TabulatedSpectrum | GeneralEvaporationSpectrum | MaxwellianFissionSpectrum | EvaporationSpectrum | WattSpectrum | MadlandNixSpectrum:
        """
        The distribution
        """
    @property
    def energy_limit_constant(self) -> float:
        """
        The energy limit constant
        """
    @property
    def probability(self) -> Probability:
        """
        The probability
        """
class Probability:
    """
    MF5 section - probability for a given partial distribution
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> Probability:
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
    def __init__(self, lf: int, boundaries: list[int], interpolants: list[int], energies: list[float], probabilities: list[float], u: float = 0.0) -> None:
        """
        Initialise the component
        
        Arguments:
            self             the component
            lf               the type of the underlying distribution
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            energies         the energy values
            probabilities    the probability values
            u                the energy limit constant U (default = 0.0)
        """
    @typing.overload
    def __init__(self, component: Probability) -> None:
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
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
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
    def P(self) -> ...:
        """
        The probability values
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
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
    def probabilities(self) -> ...:
        """
        The probability values
        """
class Section:
    """
    MF5 section - energy distributions of secondary particles
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
    def __init__(self, mt: int, zaid: int, awr: float, partials: list[PartialDistribution]) -> None:
        """
        Initialise the section
        
        Arguments:
            self        the section
            mt          the MT number
            zaid        the ZA  identifier
            awr         the atomic mass ratio
            partials    the partial distributions (at least 1)
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
    def NK(self) -> int:
        """
        The number of subsections with partial distributions
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
    def number_partial_distributions(self) -> int:
        """
        The number of subsections with partial distributions
        """
    @property
    def partial_distributions(self) -> ...:
        """
        The partial distributions defined in this section
        """
    @property
    def section_number(self) -> int:
        """
        The MT number of the section
        """
    @property
    def target_identifier(self) -> int:
        """
        The ZA identifier for the section
        """
class TabulatedSpectrum:
    """
    MF5 section - arbitrary tabulated energy distribution (LF=1)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> TabulatedSpectrum:
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
    def __init__(self, boundaries: list[int], interpolants: list[int], distributions: list[OutgoingEnergyDistribution]) -> None:
        """
        Initialise the scattering radius
        
        Arguments:
            self             the component
            boundaries       the interpolation range boundaries
            interpolants     the interpolation types for each range
            distributions    the sequence of outgoing energy distributions
        """
    @typing.overload
    def __init__(self, component: TabulatedSpectrum) -> None:
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
    def INT(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
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
    def NE(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def NR(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def boundaries(self) -> ...:
        """
        The interpolation boundaries
        """
    @property
    def incident_energies(self) -> ...:
        """
        The incident energies
        """
    @property
    def interpolants(self) -> ...:
        """
        The interpolation type for each region
        """
    @property
    def number_incident_energies(self) -> int:
        """
        The number of incident energy values
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        The number of interpolation regions
        """
    @property
    def outgoing_distributions(self) -> ...:
        """
        The outgoing energy distributions (one for each incident energy)
        """
class WattSpectrum:
    """
    MF5 section - the Watt fission spectrum (LF=11)
    """
    @staticmethod
    def from_string(string: str, mat: int, mf: int, mt: int) -> WattSpectrum:
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
    def __init__(self, a: Parameter, b: Parameter) -> None:
        """
        Initialise the component
        
        Arguments:
            self    the component
            a       the parameter function a
            b       the parameter function b
        """
    @typing.overload
    def __init__(self, component: WattSpectrum) -> None:
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
    def LAW(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def LF(self) -> int:
        """
        The distribution type (the LF flag)
        """
    @property
    def NC(self) -> int:
        """
        The number of lines in this component
        """
    @property
    def a(self) -> Parameter:
        """
        The a parameter data
        """
    @property
    def b(self) -> Parameter:
        """
        The b parameter data
        """
