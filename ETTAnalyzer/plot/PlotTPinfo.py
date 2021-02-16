# Abraham Tishelman-Charny 
# 10 February 2020
#
# The purpose of this python module is to plot TPinfo from emulator printouts 
#
# Example Commands:
#
# python PlotTPinfo.py --vars ET --tog --doNorm
# python PlotTPinfo.py --tog --vars ET --sev Zero 
# python PlotTPinfo.py  --vars ETdiff --sev Zero

import pandas as pd 
import numpy as np 
from matplotlib import pyplot as plt 
import os 
import argparse

parser = argparse.ArgumentParser()

parser.add_argument("--ind",action="store_true")
parser.add_argument("--tog",action="store_true")
parser.add_argument("--doNorm",action="store_true")
parser.add_argument("--vars", type=str, default="BX")
parser.add_argument("--sev", type=str, default="Zero")
parser.add_argument("--strip", action="store_true")

args = parser.parse_args()

ol = "/eos/user/a/atishelm/www/EcalL1Optimization/Emulator/HighEnergy/"
# vars = ["ET", "FG", "sFGVB", "TTF"]
# vars = ["ET"]

vars = [var for var in args.vars.split(',')]

Direc = 'outputs/TCPoutput'
Direc = "outputs/Sev%s"%(args.sev)
files = ["%s/%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

# print"files;",files 

VarRangeDict = {
    ##-- min, max, nbins, ymin, ymax 
    "ET" : [0, 128, 128, 10.**-1, 10.**7], 
    "StripET" : [0, 128, 128, 10.**-1, 10.**7], 
    "ETdiff" : [0, 128, 128, 10.**-1, 10.**7],
    "FG" : [0, 2, 2, 10.**-1, 10.**7],
    "sFGVB" : [0, 2, 2, 10.**-1, 10.**7],
    "TTF" : [0, 10, 10, 10.**-1, 10.**7]
}

if(args.strip):
    var = 'ET'
    fileVar = 'StripET'
    xmin, xmax, nbins, ymin, ymax = VarRangeDict[var]
    bins = np.linspace(xmin, xmax, nbins + 1)    
    fig, ax = plt.subplots()
    # for sev in ["Zero"]:
    for sev in ["Zero","Three","Four"]:
        Direc = "outputs/Sev%sStrip"%(sev)
        files = ["%s/%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

        for f_i, file in enumerate(files): ## BX Strip c0 c1 c2 c3 c4 w0 w1 w2 w3 w4 d0 d1 d2 d3 d4 arrow outputString StripET Filter
            label = file.split('/')[-1].split('.')[0] 
            config = file.split('_')[-2]
            print"Reading file",file 
            print"config:",config
            df = pd.read_csv("%s"%(file),sep = ' ')
            # exec()
            if(config == "Run2"):
                print"Setting Run2 arrays"
                Run2_stripET = np.array(df['StripET'])
                Run2_Filter = np.array(df['Filter'])
            elif(config == "Config1"):
                print"Setting Config1 arrays"
                Config1_stripET = np.array(df['StripET'])
                Config1_Filter = np.array(df['Filter'])

        # Run2_EVEN_FILTER = (Run2_Filter == "EVEN")
        # Run2_ODD_FILTER = (Run2_Filter == "ODD")
        # Run2_stripET_EVEN = Run2_stripET[Run2_EVEN_FILTER]
        # Run2_stripET_EVEN = Run2_stripET[Run2_EVEN_FILTER]
        Config1_EVEN_FILTER = (Config1_Filter == "EVEN")
        Config1_ODD_FILTER = (Config1_Filter == "ODD")
        Config1_stripET_EVEN = Config1_stripET[Config1_EVEN_FILTER]
        Config1_stripET_ODD = Config1_stripET[Config1_ODD_FILTER]

        Config1_ODDgtEVEN_FILTER = (Config1_stripET_ODD > Config1_stripET_EVEN)
        Config1_zeroed_evenvalues = Config1_stripET_EVEN[Config1_ODDgtEVEN_FILTER]
        Config1_zeroed_evenvalues = Config1_zeroed_evenvalues[Config1_zeroed_evenvalues > 32] ##-- only look at strip ETs above 16 (ADC?)

        plt.hist(Config1_zeroed_evenvalues, bins = bins, weights=np.ones(len(Config1_zeroed_evenvalues)) / len(Config1_zeroed_evenvalues), histtype = 'step', label = 'Severity = %s'%(sev))
    plt.ylim(10**-5, 2)
    plt.yscale('log')
    plt.title("Zeroed Strip Energies")
    plt.xlabel("Strip ET")
    plt.ylabel("Normalized Entries [A.U.]")
    plt.legend()
    plt.grid(axis = 'y')
    plt.savefig("%s/AllSeverities_Config1ZeroedEvenValues_gt32.png"%(ol))
    plt.close()

##-- Plot Separately 
if(args.ind):
    for f_i, file in enumerate(files):
        label = file.split('/')[-1].split('.')[0] 
        print"Plotting file",file 
        df = pd.read_csv("%s"%(file),sep = ' ')
        for var in vars: 
            print"Plotting",var 
            values = [int(val.replace("%s="%(var),'').replace(",","")) for val in df[var]]
            values = np.array(values)
            xmin, xmax, nbins, ymin, ymax = VarRangeDict[var]
            bins = np.linspace(xmin, xmax, nbins + 1)
            fig, ax = plt.subplots() 
            Nentries = np.size(values)
            avg = np.mean(values)
            minval, maxval = np.min(values), np.max(values)
            print"min, max:",minval, maxval 
            plt.hist(values,histtype='step', bins = bins, label = '%s_%s'%(var,label))
            plt.text(0.5, 0.8, 
                    label, 
                    fontsize = 15,
                    horizontalalignment='center', 
                    verticalalignment='center', 
                    transform = ax.transAxes)
            plt.text(0.5, 0.7, 
                    'Entries = %s'%(Nentries), 
                    fontsize = 15,
                    horizontalalignment='center', 
                    verticalalignment='center', 
                    transform = ax.transAxes)
            plt.text(0.5, 0.6,
                    'Average = %.5f'%(avg), 
                    fontsize = 15,
                    horizontalalignment='center', 
                    verticalalignment='center', 
                    transform = ax.transAxes)          
            plt.legend()
            plt.yscale('log')
            plt.ylim(ymin,ymax)        
            plt.xlim(xmin,xmax)
            # ax.tick_params(axis="x", direction="in")
            # ax.tick_params(axis="y", direction="in")
            # ax.xaxis.set_ticks_position('both')    
            # ax.yaxis.set_ticks_position('both')  
            if(var == "ET"): 
                plt.vlines([16], ymin, ymax, linestyles='solid', colors='midnightblue')
                plt.grid(True, axis='y')
            # plt.grid(True, axis='y')   
            if(var == "ET"): 
                plt.xlabel("ET [GeV]")
            else: 
                plt.xlabel(var)
            plt.title(var)
            plt.ylabel("Entries [A.U.]")            
            plt.savefig("%s/%s_%s.png"%(ol,var,label))
            plt.savefig("%s/%s_%s.pdf"%(ol,var,label))
            plt.close()

if(args.vars=='ETdiff'):
    # fig, ax = plt.subplots() 
    # var = 'Run2-Config1'
    var = 'ETdiff'
    fileVar = 'ET'
    # fileVar = 'ET'
    # fig, ax = plt.subplots()
    fig, ax = plt.subplots()
    bins = np.linspace(0, 1.1, 34)
    for sev in ["Zero","Three","Four"]:
        Direc = "outputs/Sev%s"%(sev)
        files = ["%s/%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

        for f_i, file in enumerate(files):
            label = file.split('/')[-1].split('.')[0] 
            print"Reading file",file 
            df = pd.read_csv("%s"%(file),sep = ' ')
            values = np.array([int(val.replace("%s="%(fileVar),'').replace(",","")) for val in df[fileVar]])
            exec("values_%s = np.array(values)"%(f_i))
            if(f_i == 1):
                ##-- Config 1 , get FG flag per TP 
                FG = np.array([int(val.replace("%s="%('FG'),'').replace(",","")) for val in df['FG']])
            # values = np.array(values)
        # diff = np.subtract(values_0, values_1)
        MASK = values_0 > 32 
        values_0 = values_0[MASK] ##-- only look at diffs when Run 2 ET > 32 ADC 
        values_1 = values_1[MASK] ##-- only look at diffs when Run 2 ET > 32 ADC 
        ratio = np.true_divide(values_1, values_0)
        # ratio = ratio[values_0 > 32] ##-- only look at diffs when Run 2 ET > 32 ADC 
        # Config1_lessthan_Run2 = np.array([val!=0 for val in diff])
        # mask = np.logical(diff!=0)
        # FG_when_1lt2 = FG[diff>0]
        # BOOL_MASK = diff != 0 
        # Config1_lessthan_Run2 = diff[BOOL_MASK]
        # diff =  
        xmin, xmax, nbins, ymin, ymax = VarRangeDict[var]
        bins = np.linspace(xmin, xmax, nbins + 1)
        # Nentries = np.size(values)
        # avg = np.mean(values)
        # minval, maxval = np.min(diff), np.max(diff)
        minval, maxval = np.min(ratio), np.max(ratio)
        print"min, max:",minval, maxval 
        # fig, ax = plt.subplots()
        bins = np.linspace(0, 1.1, 34) ##-- Hardcoded bins, no way this can possibly cause any problems in the future :) 
        # bins = np.linspace(0, 1.1, 34)
        plt.hist(ratio, histtype='step', bins = bins, weights=np.ones(len(ratio)) / len(ratio), density=False, label = 'Severity %s'%(sev)) 
        ## weights=np.ones(len(data)) / len(data) and density=False. ##-- To get sum of integral = 1         
        # plt.legend()
        # if(args.doNorm):
            # ymin = 10**-8
            # ymax = 2*10.**0 
        # plt.yscale('log')
        # plt.ylim(ymin,ymax)        
        # plt.xlim(xmin,xmax)
        # plt.xlim(0, 1.1)
        # plt.ylim(0,1)
        # plt.title(var)
        # plt.xlabel("")
        # plt.ylabel("Entries [A.U.]")
        # if(args.doNorm): 
        #     plt.savefig("%s/%sratio_Sev-%s_ETgt32_Together_Normed.png"%(ol,var,sev))
        #     plt.savefig("%s/%sratio_Sev-%s_ETgt32_Together_Normed.pdf"%(ol,var,sev))
        # else: 
        #     plt.savefig("%s/%sratio_Sev-%s_ETgt32_Together.png"%(ol,var,sev))
        #     plt.savefig("%s/%sratio_Sev-%s_ETgt32_Together.pdf"%(ol,var,sev))            
        # plt.close()   

    plt.xlim(0, 1.1)
    plt.ylim(10.**-3,2)
    plt.title("Ratio of Config 1 ET / Run 2 ET")
    plt.xlabel("Config1 ET / Run2 ET")
    plt.ylabel("Entries [A.U.]")
    plt.yscale('log')
    plt.legend(loc='upper left')
    if(args.doNorm): 
        plt.savefig("%s/%sratio_Sev-ALL_ETgt32_Together_Normed.png"%(ol,var))
        plt.savefig("%s/%sratio_Sev-ALL_ETgt32_Together_Normed.pdf"%(ol,var))
    else: 
        plt.savefig("%s/%sratio_Sev-ALL_ETgt32_Together.png"%(ol,var))
        plt.savefig("%s/%sratio_Sev-ALL_ETgt32_Together.pdf"%(ol,var))            
    plt.close()  

        # plt.hist(FG_when_1lt2, bins = [0,1,2], density = True, histtype='step', label="Severity %s"%(sev))


    # plt.ylim(0,1)
    # plt.legend(loc = 'upper left')
    # plt.title("FG when config 1 ET less than Run 2 ET")
    # plt.ylabel("Entries [A.U.]")
    # plt.xlabel("FG")
    # plt.savefig("%s/FGwhenC1ltRun2_AllSeverities.png"%(ol))

        ##-- Plot difference in ET vs. config 1 FG 
        # yedges = [0,1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,22,24,26,28,30,40,50,60,70,80,90,100,120,140,160,180,200,255]
        # yedges = [0,1,2]
        # xedges = [0,1,2]
        # # H, xedges, yedges = np.histogram2d(FG, diff, bins=(xedges, yedges))
        # H, xedges, yedges = np.histogram2d(FG, Config1_lessthan_Run2, bins=(xedges, yedges))
        # H = H.T

        # fig, ax = plt.subplots()
        # X, Y = np.meshgrid(xedges, yedges)
        # ax.pcolormesh(X, Y, H)    
        # # plt.hist2d(FG, diff, bins = 100)
        # plt.xlabel("FG bit")
        # plt.ylabel("Run2 ET - Config1 ET")
        # plt.savefig("%s/diffVsFG_Sev%s.png"%(ol, args.sev)) 

# ##-- Plot Together
# if(args.tog):

#     for var in vars: 
#         print"Plotting",var,"Together"
#         fig, ax = plt.subplots() 

#         for sev in ["Zero","Three","Four"]:
#             sevLabelDict = {
#                 "Zero" : 0,
#                 "Three" : 3,
#                 "Four" : 4
#             }
#             sevLabel = sevLabelDict[sev]
#             Direc = "outputs/Sev%s"%(sev)
#             files = ["%s/%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

#             for f_i, file in enumerate(files):
#                 label = file.split('/')[-1].split('.')[0] 
#                 if("Run2" not in file): continue 
#                 print"Plotting file",file 
#                 df = pd.read_csv("%s"%(file),sep = ' ')
#                 values = [int(val.replace("%s="%(var),'').replace(",","")) for val in df[var]]
#                 values = np.array(values)
#                 xmin, xmax, nbins, ymin, ymax = VarRangeDict[var]
#                 bins = np.linspace(xmin, xmax, nbins + 1)
#                 Nentries = np.size(values)
#                 avg = np.mean(values)
#                 minval, maxval = np.min(values), np.max(values)
#                 print"min, max:",minval, maxval 
#                 if(var=="ET"): 
#                     values = np.true_divide(values, 2.)  
#                     bins = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,40,50,60,80,100,150,250,256]
#                 plt.hist(values,histtype='step', bins = bins, weights=np.ones(len(values)) / len(values), density=False, label = 'Sev = %s'%(sevLabel))         
#         plt.legend()
#         if(args.doNorm):
#             ymin = 10**-7
#             ymax = 2*10.**0 
#         plt.yscale('log')
#         plt.ylim(ymin,ymax)        
#         plt.xlim(xmin,xmax)
#         if(var == "ET"): 
#             plt.vlines([16], ymin, ymax, linestyles='solid', colors='midnightblue')
#             plt.grid(True, axis='y')
#         # ax.tick_params(axis="x", direction="in")
#         # ax.tick_params(axis="y", direction="in")    
#         # ax.xaxis.set_ticks_position('both')    
#         # ax.yaxis.set_ticks_position('both')    
            
#         plt.title(var)
#         if(var == "ET"): 
#             plt.xlabel("ET [GeV]")
#         else: 
#             plt.xlabel(var)        
#         plt.ylabel("Entries [A.U.]")
#         if(args.doNorm): 
#             plt.savefig("%s/%s_AllSevs_Normed.png"%(ol,var))
#             plt.savefig("%s/%s_AllSevs_Normed.pdf"%(ol,var))
#         else: 
#             plt.savefig("%s/%s_AllSevs.png"%(ol,var))
#             plt.savefig("%s/%s_AllSevs.pdf"%(ol,var))            
#         plt.close()

##-- Plot Together
if(args.tog):

    for var in vars: 
        print"Plotting",var,"Together"
        fig, ax = plt.subplots() 

        for sev in ["Zero","Three","Four"]:
            sevLabelDict = {
                "Zero" : 0,
                "Three" : 3,
                "Four" : 4
            }
            sevLabel = sevLabelDict[sev]
            Direc = "outputs/Sev%s"%(sev)
            files = ["%s/%s"%(Direc, f) for f in os.listdir(Direc) if os.path.isfile(os.path.join(Direc, f))]

            for f_i, file in enumerate(files):
                label = file.split('/')[-1].split('.')[0] 
                config = label.split('_')[-2]
                # if("Run2" not in file): continue 
                print"Plotting file",file 
                df = pd.read_csv("%s"%(file),sep = ' ')
                values = [int(val.replace("%s="%(var),'').replace(",","")) for val in df[var]]
                values = np.array(values)
                xmin, xmax, nbins, ymin, ymax = VarRangeDict[var]
                bins = np.linspace(xmin, xmax, nbins + 1)
                Nentries = np.size(values)
                avg = np.mean(values)
                minval, maxval = np.min(values), np.max(values)
                print"min, max:",minval, maxval 
                if(var=="ET"): 
                    values = np.true_divide(values, 2.)  
                    bins = [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32,40,50,60,80,100,150,250,256]
                plt.hist(values,histtype='step', bins = bins, weights=np.ones(len(values)) / len(values), density=False, label = 'Sev = %s, Config = %s'%(sevLabel, config))         
            plt.legend()
            if(args.doNorm):
                ymin = 10**-7
                ymax = 2*10.**0 
            plt.yscale('log')
            plt.ylim(ymin,ymax)        
            plt.xlim(xmin,xmax)
            if(var == "ET"): 
                plt.vlines([16], ymin, ymax, linestyles='solid', colors='midnightblue')
                plt.grid(True, axis='y')
            # ax.tick_params(axis="x", direction="in")
            # ax.tick_params(axis="y", direction="in")    
            # ax.xaxis.set_ticks_position('both')    
            # ax.yaxis.set_ticks_position('both')    
            
            plt.title(var)
            if(var == "ET"): 
                plt.xlabel("ET [GeV]")
            else: 
                plt.xlabel(var)        
            plt.ylabel("Entries [A.U.]")
            if(args.doNorm): 
                plt.savefig("%s/%s_Sev-%s_Normed.png"%(ol,var,sevLabel))
                plt.savefig("%s/%s_Sev-%s_Normed.pdf"%(ol,var,sevLabel))
            else: 
                plt.savefig("%s/%s_Sev-%s.png"%(ol,var,sevLabel))
                plt.savefig("%s/%s_Sev-%s.pdf"%(ol,var,sevLabel))            
            plt.close()

print"DONE" 
