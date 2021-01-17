from run import Collector, multirun, ProcessData, Parameters
from tables import open_file, Filters
import os
from string import Template
import numpy as np
import shutil

GPS_TEMPLATE=Template(
"""/gps/particle gamma
/gps/position 0.0 0.0 20.0 millimeter
/gps/direction 0 0 -1
/gps/ene/mono ${energy} MeV
/run/beamOn ${number}

"""
)



def generator():
    energy = np.logspace(-1, 2, num=200, endpoint=True)
    for i in range(energy.size):
        yield ProcessData(
            "sim/sim{}".format(str(i).rjust(4,"0")),
            Parameters(gps={"energy": energy[i],
                            "number": int(1e6)}),
            "../../../geant4-bgo.exe",
            GPS_TEMPLATE
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