import os, sys
from dataclasses import dataclass
from multiprocessing import Pool
import subprocess
from typing import Optional
from string import Template
import shutil
import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.INFO)

SETTINGS_NAME = "settings.mac"
RUN_NAME = "run.mac"

@dataclass
class Parameters:
    gps : Optional[dict] = None
    settings : Optional[dict] = None

    def get_gps_text(self, template: Template) -> str:
        if self.gps is None or template is None:
            return "\n"
        else:
            return template.substitute(self.gps)

    def get_settings_text(self, template: Template) -> str:
        if self.settings is None or template is None:
            return "\n"
        else:
            return template.substitute(self.settings)

@dataclass
class ProcessData:
    path : str
    parameters: Parameters
    command: str
    template_gps: Optional[Template] = None
    template_settings :  Optional[Template] = None


def run(data: ProcessData):
    command = data.command + " " +SETTINGS_NAME + " " + RUN_NAME
    os.makedirs(data.path, exist_ok=True)
    pwd = os.getcwd()
    os.chdir(data.path)
    with open(SETTINGS_NAME, "w") as fout:
        fout.write(data.parameters.get_settings_text(data.template_settings))
    with open(RUN_NAME, "w") as fout:
        fout.write(data.parameters.get_gps_text(data.template_gps))
    logger.addHandler(
        logging.FileHandler("run.log")
    )
    logger.info(command)
    proc = subprocess.Popen(command, shell=True,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            encoding='utf-8')
    out, err = proc.communicate()
    logger.info(out)
    logger.info(err)
    proc.wait()
    os.chdir(pwd)
    return data

def multirun(generator, collector):
    with Pool() as p:
        for result in p.imap_unordered(run, generator()):
            collector(result)