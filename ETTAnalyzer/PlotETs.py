import pandas as pd 
import numpy as np 
from matplotlib import pyplot as plt 

ol = "/eos/user/a/atishelm/www/EcalL1Optimization/Emulator/"


##-- Separate 
fig, ax = plt.subplots()
# for f_i, file in enumerate(["log_Run2_ET.txt","test2_ETs.txt"]):
for f_i, file in enumerate(["FinalCheck_Run2_ETs.txt","FinalCheck_Config1_ETs_final.txt"]):
    if f_i == 0: label = "Run2"
    else: label = "Config1"

    df = pd.read_csv(file)
    ETs = []
    for ic,column in enumerate(df):
        if(ic==0): columnName = column 
    Energies = [float(ET[6:]) for ET in df[columnName]]
    ETs = np.array(Energies)
    Nentries = np.size(ETs)
    avg = np.mean(ETs)

    # xmin, xmax, nbins = min(ETs), max(ETs), int(max(ETs) - min(ETs))
    xmin, xmax, nbins = 0, 15, 15 
    # xmin, xmax, nbins = 0, 2, 2
    bins = np.linspace(xmin, xmax, nbins + 1)
    print("Plotting...")
    print ETs
    # fig, ax = plt.subplots()
    plt.hist(ETs, histtype = 'step', bins = bins, label = label)
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
     
    # plt.text(0.5, 0.8,
            # 'TP Energy',
            # fontsize = 20,
            # horizontalalignment='center', 
            # verticalalignment='center', 
            # transform = ax.transAxes)             

    plt.legend()
    plt.xlabel("ET")
    plt.ylabel("Entries")
    plt.yscale('log')
    ymin, ymax = 0.1, 10000. 
    plt.ylim(ymin,ymax)
    plt.savefig("%s/%s_%s"%(ol,label,"ETs.png"))
    plt.close()

##-- Together
fig, ax = plt.subplots()
for f_i, file in enumerate(["FinalCheck_Run2_ETs.txt","FinalCheck_Config1_ETs_final.txt"]):
    if f_i == 0: label = "Run2"
    else: label = "Config1"

    df = pd.read_csv(file)
    ETs = []
    for ic,column in enumerate(df):
        if(ic==0): columnName = column 
    Energies = [float(ET[6:]) for ET in df[columnName]]
    ETs = np.array(Energies)
    Nentries = np.size(ETs)
    avg = np.mean(ETs)

    # xmin, xmax, nbins = min(ETs), max(ETs), int(max(ETs) - min(ETs))
    xmin, xmax, nbins = 0, 15, 15 
    # xmin, xmax, nbins = 0, 2, 2
    bins = np.linspace(xmin, xmax, nbins + 1)
    print("Plotting...")
    print ETs
    # fig, ax = plt.subplots()
    plt.hist(ETs, histtype = 'step', bins = bins, label = label)
    # plt.text(0.5, 0.8, 
    #         label, 
    #         fontsize = 15,
    #         horizontalalignment='center', 
    #         verticalalignment='center', 
    #         transform = ax.transAxes)
    # plt.text(0.5, 0.7, 
    #         'Entries = %s'%(Nentries), 
    #         fontsize = 15,
    #         horizontalalignment='center', 
    #         verticalalignment='center', 
    #         transform = ax.transAxes)
    # plt.text(0.5, 0.6,
    #         'Average = %.5f'%(avg), 
    #         fontsize = 15,
    #         horizontalalignment='center', 
    #         verticalalignment='center', 
    #         transform = ax.transAxes)  
     
plt.text(0.5, 0.8,
        'TP Energy',
        fontsize = 20,
        horizontalalignment='center', 
        verticalalignment='center', 
        transform = ax.transAxes)             

plt.legend()
plt.xlabel("ET")
plt.ylabel("Entries")
plt.yscale('log')
ymin, ymax = 0.1, 10000. 
plt.ylim(ymin,ymax)
plt.savefig("%s/%s"%(ol,"Compare_ETs.png"))

print("DONE")