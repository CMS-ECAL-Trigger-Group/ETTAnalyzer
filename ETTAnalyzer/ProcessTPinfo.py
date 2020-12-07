########################################################################################################################
# Abraham Tishelman-Charny                                                                                             #
# 7 December 2020                                                                                                      #
#                                                                                                                      #
# The purpose of this module is to organize and plot TP info from the ETTAnalyzer                                      #
#                                                                                                                      #
# Example Usage:                                                                                                       #
#                                                                                                                      #
# python ProcessTPinfo.py --outLoc /eos/user/a/atishelm/www/EcalL1Optimization/TPinfo                                              
########################################################################################################################

from python.ProcessTPinfo_Tools import * 
from python.ProcessTPinfo_Options import * 
import pandas as pd 
import subprocess

##-- Get User input Args
args = GetOptions() 

if __name__ == '__main__':

    ##-- Set output location and create directory if it doesn't exist, copying index file as well 
    ##-- Note: <outLoc>/../ must exist 
    outLoc = args.outLoc  
    CheckMakeOutLocation(outLoc)

    inputFile = "TPinfo.txt"
    EB_DOF_File = "parameters/DOF_EB_2018.csv"
    EE_DOF_File = "parameters/DOF_EE_2018.csv"
    headerFile = "HeaderNoRLE.txt"

    TPinfo = TPInfoProcess(inputFile,EB_DOF_File,EE_DOF_File,headerFile,outLoc)
    TPinfo.AddHeader()
    TPinfo_DF = TPinfo.CreateDataframe()
    TPinfo.PlotRecoAs(TPinfo_DF)