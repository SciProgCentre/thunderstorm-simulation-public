from run import Collector, multirun, ProcessData, Parameters
from string import Template
import numpy as np

SETTINGS_TEMPLATE = Template(
"""/npm/thunderstorm/size 15 millimeter
/npm/thunderstorm/length ${length} millimeter
/npm/thunderstorm/material ${material}
"""
)

GPS_TEMPLATE = Template(
    """/gps/particle gamma
    /gps/position 0.0 0.0 ${position} millimeter
    /gps/direction 0 0 -1
    /gps/ene/type Lin
    /gps/ene/min ${left_energy} MeV
    /gps/ene/max ${right_energy} MeV
    /gps/ene/intercept 1
    /run/beamOn ${number}
    """
)


def energy_bound(start=0.1, resolution=0.1):
    def error(energy):
        return 1 / (np.sqrt(energy / resolution ** 2))

    result = [start]
    energy = start
    while (energy < 100):
        width = error(energy) * energy
        energy = energy + 2 * width
        result.append(energy)
    result[-1] = 100
    return result


def generator():
    energy = energy_bound()
    length = 15
    pos = length * 1.5 / 2
    for i in range(len(energy) - 1):
        yield ProcessData(
            "sim/sim{}".format(str(i).rjust(4, "0")),
            Parameters(
                gps={
                    "left_energy": energy[i],
                    "right_energy": energy[i + 1],
                    "number": int(1e6),
                    "position": pos
                },
                settings={
                    "length": length,
                    "material" : "NPM_YSO"
                }
            ),

            "../../../geant4-bgo.exe",
            GPS_TEMPLATE,
            SETTINGS_TEMPLATE
        )


def main():
    collector = Collector(True)
    try:
        multirun(generator, collector)
    finally:
        collector.close()
    return 0


if __name__ == '__main__':
    main()
