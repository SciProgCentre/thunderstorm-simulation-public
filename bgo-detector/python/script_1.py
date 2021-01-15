from run import multirun, ProcessData, Parameters
from tables import open_file, Filters
import os
from string import Template
import numpy as np

GPS_TEMPLATE=Template(
"""/gps/particle gamma
/gps/position 0.0 0.0 20.0 millimeter
/gps/direction 0 0 -1
/gps/ene/mono ${energy} MeV
/run/beamOn ${number}

"""
)

class Collector:

    def __init__(self):
        self.h5file = open_file("result.hdf5", "w", filters=Filters(complevel=3, fletcher32=True))

    def __call__(self, process_data: ProcessData):
        name = os.path.split(process_data.path)[-1]
        print(name)
        group = self.h5file.create_group(self.h5file.root, name)
        data = np.loadtxt(os.path.join(process_data.path, "deposit.txt"))
        array = self.h5file.create_array(group, "deposit", obj=data)
        gps = process_data.parameters.gps
        array.attrs["number"] = gps["number"]
        array.attrs["energy"] = gps["energy"]
        array.flush()

    def close(self):
        self.h5file.close()

def generator():
    energy = np.logspace(-1, 2, num=200, endpoint=True)
    for i in range(energy.size):
        yield ProcessData(
            "sim/sim{}".format(str(i).rjust(4,"0")),
            Parameters(gps={"energy": energy[i],
                            "number": int(1e9)}),
            "../../../geant4-bgo.exe",
            GPS_TEMPLATE
        )

def main():
    collector = Collector()
    try:
        multirun(generator, collector)
    finally:
        collector.close()
    return 0

if __name__ == '__main__':
    main()