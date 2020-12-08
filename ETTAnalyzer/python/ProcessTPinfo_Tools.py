########################################################################################################################
# Abraham Tishelman-Charny                                                                                             #
# 7 December 2020                                                                                                      #
#                                                                                                                      #
# The purpose of this module is to provide a class and methods for a TPInfoProcess object to be used by the            #
# ProcessTPinfo module.                                                                                                #                                                                                                          
########################################################################################################################

import os 
import pandas as pd 
from matplotlib import pyplot as plt 
import numpy as np 

class TPInfoProcess:

    def __init__(self, inputFile, EB_DOF_File, EE_DOF_File, headerFile, outLoc):
        self.inputFile = inputFile 
        self.updatedFileName = "%s_WithHeader.txt"%(self.inputFile.replace(".txt",""))
        self.EB_DOF_File = EB_DOF_File
        self.EE_DOF_File = EE_DOF_File
        self.headerFile = headerFile 
        self.outLoc = outLoc 

    def AddHeader(self):
        updatedFileName = "TPinfoWithHeader.txt"
        log_in = open(self.inputFile)
        log_out = open(self.updatedFileName, 'w')
        header_ = open(self.headerFile).readline()
        log_out.write(header_)
        for iline in log_in:
            log_out.write(iline)        
        log_out.close()
        self.inputFile = self.updatedFileName 

    def CreateDataframe(self):
        TPinfo_DF = pd.read_csv(self.inputFile, sep=" ")
        return TPinfo_DF 

    def PlotRecoAs(self, TPinfo_DF):
        recoA = ( TPinfo_DF["wd0"] * TPinfo_DF["d0"] ) + ( TPinfo_DF["wd1"] * TPinfo_DF["d1"] ) + ( TPinfo_DF["wd2"] * TPinfo_DF["d2"] ) + ( TPinfo_DF["wd3"] * TPinfo_DF["d3"] ) + ( TPinfo_DF["wd4"] * TPinfo_DF["d4"] )
        TPinfo_DF["recoA"] = recoA
        evenRecoAs = TPinfo_DF.loc[TPinfo_DF['Filter'] == "EVEN", "recoA"]
        oddRecoAs = TPinfo_DF.loc[TPinfo_DF['Filter'] == "ODD", "recoA"]

        TPinfo_DF = TPinfo_DF[(TPinfo_DF.d3 > TPinfo_DF.d0)] 
        TPinfo_DF = TPinfo_DF[(TPinfo_DF.d3 > TPinfo_DF.d1)] 
        TPinfo_DF = TPinfo_DF[(TPinfo_DF.d3 > TPinfo_DF.d2)] 
        TPinfo_DF = TPinfo_DF[(TPinfo_DF.d3 > TPinfo_DF.d4)] 
        evenDigis = TPinfo_DF.loc[TPinfo_DF['Filter'] == "EVEN" ] # find 125 ns peaked events 
        # evenDigis = TPinfo_DF.loc[TPinfo_DF['Filter'] == "EVEN" and (TPinfo_DF['d3'] > TPinfo_DF['d2']) and (TPinfo_DF['d3'] > TPinfo_DF['d4'])] # find 125 ns peaked events 

        digiAverages = []
        for i in range(0,5):
            exec("d%s = evenDigis['d%s'].to_numpy()"%(i,i))
            exec("d%s_avg = d%s.mean()"%(i,i))
            exec("digiAverages.append(d%s_avg)"%(i))
        digis = np.stack((d0, d1, d2, d3, d4), axis=1)
        print"digis:",digis

        # plt.scatter([50, 75, 100, 125, 150], digiAverages, label = "Digi averages")
        plt.plot(digis.T, label = "Digis")
        # plt.legend()
        plt.savefig("%s/Digis.png"%(self.outLoc))
        plt.close() 

        plt.hist(oddRecoAs,
                label = "ODD",
                )
        plt.legend()
        plt.savefig("%s/OddFilterAmplitudes.png"%(self.outLoc))

        plt.close()

        plt.hist(evenRecoAs,
                label = "EVEN" 
                )

        plt.legend()
        plt.savefig("%s/EvenFilterAmplitudes.png"%(self.outLoc))        

    ##-- This is too slow 
    # def AddDOFs(self, TPinfo_DF):
        # print"Adding DOFs to DF"
        # EB_DF = pd.read_csv(self.EB_DOF_File, sep=",")
        # EE_DF = pd.read_csv(self.EE_DOF_File, sep=",")

        # DOF_one_column = ["DOF1"]
        # DOF_two_column = ["DOF2"]
        # DOF_three_column = ["DOF3"]

        # for index, row in TPinfo_DF.iterrows():
        #     # print"row:",row
        #     # print"stripid:",row['stripid']
        #     stripid = row['stripid']
        #     DOF1, DOF2, DOF3 = FindStripDOFs(EB_DF,EE_DF,stripid)
        #     print"DOF1, DOF2, DOF3:"
        #     print DOF1 
        #     print DOF2 
        #     print DOF3 
        #     if index == 3: break 
        

##-- Non-Class Functions 
def CheckMakeOutLocation(outLoc_):
    if(not os.path.exists(outLoc_)):
        print"Creating output directory: %s"%(outLoc_)
        beforeOutLoc = "%s/../"%(outLoc_)
        os.system('mkdir %s'%(outLoc_))
        os.system('cp %s/index.php %s'%(beforeOutLoc,outLoc_))  

# def FindStripDOFs(EB_DF, EE_DF, stripid):
#     # First check EB info 
#     for EBindex, EBrow in EB_DF.iterrows():
#         if EBrow['stripid'] == stripid:
#             print"Found strip ID:",stripid
#             DOF1 = EBrow['iphi']
#             DOF2 = EBrow['ieta']
#             DOF3 = 0 # iz = 0 for EB 
#             break 
#     for EEindex, EErow in EE_DF.iterrows():
#         if EErow['stripid'] == stripid:
#             print"Found strip ID:",stripid 
#             DOF1 = EErow['ix']
#             DOF2 = EErow['iy']
#             DOF3 = EErow['side']               
#             break 

#     return DOF1, DOF2, DOF3 