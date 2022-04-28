#!/usr/bin/env python
# coding: utf-8

"""
11 April 2022
Abraham Tishelman-Charny 

The purpose of this module is to analyze 2021 beam splash data to investigate ECAL double weights

Example usage: 

python3 plot/PlotBeamSplashes.py --TPMode Tagging --Weights 0p5 --year 2022 --beam one 
python3 plot/PlotBeamSplashes.py --TPMode KillNTag --Weights 0p5 --year 2022 --beam two

"""

import uproot 
from matplotlib import pyplot as plt 
import numpy as np 
import awkward as ak
import matplotlib.colors as colors
import argparse 
import os 

from Plotter_Tools import Add_CMS_Header, GetPathDict

parser = argparse.ArgumentParser()
# parser.add_argument("--inFile", type = str, required = True, help = "Input file, should be ETTAnalyzer output file")
parser.add_argument("--TPMode", type = str, required = True, help = "TPMode during re-emulation (Killing, Tagging, or TagNKill)")
parser.add_argument("--Weights", type = str, required = True, help = "Weights during re-emulation (deltamin 0p5, or 2p5)")
# parser.add_argument("--Event", type = int, required = True, help = "Event number to run over")
parser.add_argument("--lowEvents", action = "store_true", help = "Run over fewer events")
parser.add_argument("--verbose", action = "store_true", help = "Print out more things")
parser.add_argument("--year", type = str, help = "Year of beam splashes")
parser.add_argument("--beamNumber", type = str, help = "Beam number (one or two)")
args = parser.parse_args()

f_path_dict = GetPathDict()
f_path = f_path_dict[args.Weights][args.TPMode][args.beamNumber]
verbose = args.verbose

f = uproot.open(f_path)
t = f["tuplizer/ETTAnalyzerTree"]

# extra info if the user wants it 
if(verbose):
    print("Available branches:")
    print(t.keys())
    print("CMS Event numbers:")
    print(t['evtNb'].array())

"""
Ratio plot 
"""

bins = np.linspace(-30, 30, 30)
isWide = 0
TTF_clean = 1 
flatten = 1
log = 0
plotRatio = 0

event = -1 

if(plotRatio):

    ##-- Overlay two plots and plot ratio 
    fig, axarr = plt.subplots(2, 
                                sharex=True, 
                                gridspec_kw={
                                    'hspace': 0.15,
    #                                     'height_ratios': (0.8,0.2)
                                    'height_ratios': (0.7,0.3)
                                    }
                                )          

    fig.set_dpi(100)
    fig.set_size_inches(8, 6)

    upper = axarr[0] ##-- Upper axis. Will contain two distributions, one for each CMSSW config 
    lower = axarr[1] ##-- Lower axis. Will contain ratio of two upper distributions 
    upper.ticklabel_format(style='plain') ##-- Remove scientific notation
    #             lower.ticklabel_format(style='plain') ##-- Remove scientific notation            
    upper.grid(True)        
    lower.grid(True)        

    #         fig, ax = plt.subplots()

    v = "time"
    variable_values = t[v].array()

    # If looking at a single event
    Event_index = -1 
    if(event != -1):
        Event_index = np.where(t['evtNb'].array() == event)[0][0]
    #     evtNb_vals_tagged = evtNb_vals[MASK]
    #     evtNb_vals_tagged = evtNb_vals_tagged[tagged_filter]
    #     evtNb_vals_all = evtNb_vals[MASK]
    #     event_mask_all = [val == event for val in evtNb_vals_all]
    #     event_mask_tagged = [val == event for val in evtNb_vals_tagged]
    #     variable_values = variable_values[event_mask_all]
    #     variable_values_tagged = variable_values[event_mask_tagged]

    if(TTF_clean):
        TTF_values = t["ttFlag"].array()

    if(flatten): 
        if(Event_index == -1):
            variable_values = ak.flatten(variable_values)
        else:
            variable_values = variable_values[Event_index]
        
        if(TTF_clean):
            if(Event_index == -1): TTF_values = ak.flatten(TTF_values)
            else: TTF_values = TTF_values[Event_index]
            
    if(TTF_clean):
        TTF4_Mask = [val != 4 for val in TTF_values]
        MASK = np.logical_and(True, TTF4_Mask)
        variable_values = variable_values[MASK]
        
        # Data_FGbit_vals = t["FineGrainBit"].array() # if you want to check tagging in data 
        Data_FGbit_vals = t["rawTPEmulFineGrainBit3"].array() # if you want to check tagging in emulator 
        if(Event_index == -1):
            Data_FGbit_vals = ak.flatten(Data_FGbit_vals)
        else: 
            Data_FGbit_vals = Data_FGbit_vals[Event_index]
        Data_FGbit_vals = Data_FGbit_vals[MASK]
        
    tagged = [val == 1 for val in Data_FGbit_vals]
    tagged_filter = np.logical_and(True, tagged)
    variable_values_tagged = variable_values[tagged_filter]

        
    # convert values from awkward to numpy array
    vals_all = []
    vals_all = np.append(vals_all, np.array(variable_values))
    vals_tagged = []
    vals_tagged = np.append(vals_tagged, np.array(variable_values_tagged))

    binVals_all, edges = np.histogram(vals_all, bins = bins) ##-- Make numpy histogram to get histogram height values in order to avoid drawing on pyplot artist
    binVals_tagged, edges = np.histogram(vals_tagged, bins = bins) ##-- Make numpy histogram to get histogram height values in order to avoid drawing on pyplot artist

    upper.hist(bins[:-1], weights = binVals_all, bins = bins, label = "All")
    upper.hist(bins[:-1], weights = binVals_tagged, bins = bins, label = "Tagged")
    # upper.set_yscale('log')    

    ##-- Take ratio 
    print("Taking ratio...")
    binvalues1_a = np.array(binVals_all, dtype = float)
    binvalues2_a = np.array(binVals_tagged, dtype = float)          
    bin_centers = [ (((float(bins[i+1]) - float(bins[i])) / 2.) + float(bins[i])) for i in range(0, len(bins)-1)]

    ##-- Ratio plot lines 
    # lower.plot([bins[0],bins[-1]],[1,1],linestyle=':', color = 'black')

    zero_errors = [0 for entry in bin_centers]
    ratio = np.true_divide(binvalues2_a , binvalues1_a, out = np.zeros_like(binvalues1_a), where = binvalues1_a != 0)    

    lower.errorbar(bin_centers, ratio, xerr = zero_errors , yerr = zero_errors, marker = '.', color = 'black', ls = '')     

    textstr = "\n".join([
        "Event = %s"%(str(event)),
    #     r"%s"%(energy_label)
        #"%s matched TPs"%(TP_type),
    #             r"Ratio MostlyZeroed$\geq$32 ADC: %s"%(round(Fraction_Tagged_32to256, 4)),
    #             r"Ratio MostlyZeroed$<$32 ADC: %s"%(round(Fraction_Tagged_1to32, 4))
    ])

    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)
    text_x, text_y = 0.025, 0.95
    if(event != -1):    
        fig.text(text_x, text_y, textstr, transform=upper.transAxes, fontsize=20,
                verticalalignment='top', bbox=props)  

    plt.gcf().subplots_adjust(bottom=0.1)
    plt.gcf().subplots_adjust(left=0.1)
    lower.set_xlabel("Rec hit time (ns)", fontsize = 15)
    upper.set_ylabel("Entries", fontsize = 15)

    upperRightText = "Beam Splash 2021"
    xmin = 0.115
    Add_CMS_Header(plt, isWide, upper, upperRightText, xmin)
    yLabel = "Entries"
    upper.set_ylabel(yLabel, fontsize = 20)
    lower.set_ylabel("Ratio", fontsize = 20)
    plt.yticks(fontsize=15)
    plt.xticks(fontsize=15)

    if(log):
        upper.set_yscale('log')
        upper_ymin, upper_ymax = upper.get_ylim()
        upper.set_ylim(upper_ymin, upper_ymax * 100.)    
        upper.legend(fontsize = 20, ncol = 2)
        plt.yticks(fontsize=15)
        plt.xticks(fontsize=15)    

    else:
        upper.legend(fontsize = 20)

    upper.tick_params(axis = 'y', labelsize = 12)    
    lower.set_ylim(0, 1)
    # plt.show()
    OUT_DIRECTORY_RATIO = "/eos/user/a/atishelm/www/EcalL1Optimization/BeamSplash%s_Reemulation_DeltaMin%sWeights_beam%s/%s_Mode/"%(args.year, args.Weights, args.beamNumber, args.TPMode)
    plt.savefig("%s/TaggedTimesRatio.png"%(OUT_DIRECTORY_RATIO))
    plt.savefig("%s/TaggedTimesRatio.pdf"%(OUT_DIRECTORY_RATIO))
    plt.close()  

"""
Variable plots 
"""

variables = [
    "twrADC", "twrEmul3ADC", "time", "rawTPEmulFineGrainBit3", "FineGrainBit"
]

DATA_VARIABLES = []
EMU_VARIABLES = []

events = t['evtNb'].array()
runNumbers = t['runNb'].array()
lowEvents = args.lowEvents

N_events = len(events)
for v_to_plot in variables:
    print("v_to_plot:",v_to_plot)
    OUT_DIRECTORY = "/eos/user/a/atishelm/www/EcalL1Optimization/BeamSplash%s_Reemulation_DeltaMin%sWeights_beam%s/%s_Mode/%s/"%(args.year, args.Weights, args.beamNumber, args.TPMode, v_to_plot)
    if(not os.path.isdir(OUT_DIRECTORY)):
        cmd = "mkdir -p %s"%(OUT_DIRECTORY)
        print("$ %s"%(cmd))
        os.system(cmd)
        cmd_cp = "cp /eos/user/a/atishelm/www/EcalL1Optimization/index.php %s"%(OUT_DIRECTORY)
        cmd_cp_2 = "cp /eos/user/a/atishelm/www/EcalL1Optimization/index.php %s/../"%(OUT_DIRECTORY)
        print("$ %s"%(cmd_cp))
        os.system(cmd_cp)
        os.system(cmd_cp_2)
    for ievent, event in enumerate(events):
        runNumber = runNumbers[ievent]
        if(ievent%20==0): print("On event %s / %s: %s"%(ievent, N_events, event))
        if((ievent==1) and (lowEvents)): 
            print("Leaving early")
            break 

        # event = args.Event 
        apply_tagged_filter = 0 

        # Get vals from tree
        ieta_vals = t["ieta"].array()
        iphi_vals = t["iphi"].array()
        time_vals = t["time"].array()
        TTF_values = t["ttFlag"].array()
        Data_FGbit_vals = t["FineGrainBit"].array()
        Data_EmulFGbit_vals = t["rawTPEmulFineGrainBit3"].array()

        exec("v_to_plot_vals = t['%s'].array()"%(v_to_plot))

        # flatten to look at all events, or pick out single event 

        Event_index = -1 
        if(event != -1):
            Event_index = np.where(t['evtNb'].array() == event)[0][0]
            ieta_vals = ieta_vals[Event_index]
            iphi_vals = iphi_vals[Event_index]
            time_vals = time_vals[Event_index]
            TTF_values = TTF_values[Event_index]
            Data_FGbit_vals = Data_FGbit_vals[Event_index]    
            Data_EmulFGbit_vals = Data_EmulFGbit_vals[Event_index]
            v_to_plot_vals = v_to_plot_vals[Event_index]
        else:
            ieta_vals = ak.flatten(ieta_vals)
            iphi_vals = ak.flatten(iphi_vals)
            time_vals = ak.flatten(time_vals)
            TTF_values = ak.flatten(TTF_values)
            Data_FGbit_vals = ak.flatten(Data_FGbit_vals)
            Data_EmulFGbit_vals = ak.flatten(Data_EmulFGbit_vals)
            v_to_plot_vals = ak.flatten(v_to_plot_vals)

        # remove TTs with ttflag 4 

        # Define mask 
        TTF4_notFour = [val != 4 for val in TTF_values]
        TTF4_Mask = np.logical_and(True, TTF4_notFour)
        time_notNull = [val != -999 for val in time_vals]
        time_Mask = np.logical_and(True, time_notNull)

        full_mask = np.logical_and(TTF4_Mask, time_Mask)

        # apply mask 
        Data_FGbit_vals = Data_FGbit_vals[full_mask]
        Data_EmulFGbit_vals = Data_EmulFGbit_vals[full_mask]
        ieta_vals = ieta_vals[full_mask]
        iphi_vals = iphi_vals[full_mask]
        time_vals = time_vals[full_mask]
        v_to_plot_vals = v_to_plot_vals[full_mask]

        # choose tagged definition based on if you're plotting data or emulated quantities 

        # tagged = [val == 1 for val in Data_FGbit_vals] # tagged in data 
        tagged = [val == 1 for val in Data_EmulFGbit_vals] # tagged in emulator 
        tagged_filter = np.logical_and(True, tagged)

        if(apply_tagged_filter):
            ieta_vals_tagged = ieta_vals[tagged_filter]
            iphi_vals_tagged = iphi_vals[tagged_filter]
            time_vals_tagged = time_vals[tagged_filter]
            v_to_plot_vals_tagged = v_to_plot_vals[tagged_filter]
            
        else:
            ieta_vals_tagged = ieta_vals
            iphi_vals_tagged = iphi_vals
            time_vals_tagged = time_vals    
            v_to_plot_vals_tagged = v_to_plot_vals

        # Convert awkward array to numpy array for plotting
        ieta_vals_tagged_a = []
        ieta_vals_tagged_a = np.append(ieta_vals_tagged_a, np.array(ieta_vals_tagged))

        iphi_vals_tagged_a = []
        iphi_vals_tagged_a = np.append(iphi_vals_tagged_a, np.array(iphi_vals_tagged))

        time_vals_tagged_a = []
        time_vals_tagged_a = np.append(time_vals_tagged_a, np.array(time_vals_tagged))

        v_to_plot_vals_a = []
        v_to_plot_vals_a = np.append(v_to_plot_vals_a, np.array(v_to_plot_vals_tagged))

        # Make the plot 
        fig, ax = plt.subplots()

        fig.set_dpi(100)
        # fig.set_size_inches(8, 6)
        # fig.set_size_inches(8, 16)

        # print("ieta_vals_tagged_a:",ieta_vals_tagged_a)

        # ieta_vals_tagged_a
        ieta_vals_tagged_a = [x if x<0 else x-1 for x in ieta_vals_tagged_a]
        # [x+1 if x >= 45 else x+5 for x in l]

        ### redefine positive ietas just to remove middle column of ieta = 0 

        ieta_bins = np.linspace(-17, 17, 35)
        iphi_bins = np.linspace(1, 73, 73)

        # ieta_bins = np.linspace(-17, 18, 36)
        # iphi_bins = np.linspace(1, 74, 74)

        # print("v_to_plot_vals_a:",v_to_plot_vals_a.tolist())

        if(v_to_plot == "twrADC" or v_to_plot == "twrEmul3ADC"):
            zLabel = "Tower ET [ADC]"
            vmin, vmax = 0, 256
            plt.hist2d(iphi_vals_tagged_a, 
                    ieta_vals_tagged_a, 
                    weights = v_to_plot_vals_a,
                    bins = (iphi_bins, ieta_bins), 
                    cmap = plt.cm.jet,
                    vmin = vmin,
                    vmax = vmax,
                    cmin = 1
                    )    
            
        elif(v_to_plot == "time"):
            zLabel = "Rec hit time (ns)"
            vmin, vmax = -25, 10
            norm = colors.TwoSlopeNorm(vmin=vmin, vcenter=0, vmax=vmax)
        #     plt.hist2d(ieta_vals_tagged_a, 
        #                iphi_vals_tagged_a, 
            plt.hist2d(iphi_vals_tagged_a, 
                    ieta_vals_tagged_a, 
            #            weights = time_vals_tagged_a,
                    weights = v_to_plot_vals_a,
        #                bins = (ieta_bins, iphi_bins), 
                    bins = (iphi_bins, ieta_bins), 
                    cmap=plt.cm.bwr,
                    vmin = vmin,
                    vmax = vmax,
                    norm = norm
            #            cmin = 1
                    )    

        elif(v_to_plot == "FineGrainBit" or v_to_plot == "rawTPEmulFineGrainBit3"):
            zLabel = v_to_plot
            vmin, vmax = 0, 2
        #     plt.hist2d(ieta_vals_tagged_a, 
        #                iphi_vals_tagged_a, 
            plt.hist2d(iphi_vals_tagged_a, 
                    ieta_vals_tagged_a, 
                    weights = v_to_plot_vals_a,
        #                bins = (ieta_bins, iphi_bins), 
                    bins = (iphi_bins, ieta_bins), 
                    cmap = plt.cm.jet,
                    vmin = vmin,
                    vmax = vmax,
                    cmin = 1
                    )      
            
        if(v_to_plot != "FineGrainBit" and v_to_plot != "rawTPEmulFineGrainBit3"):
            plt.colorbar().set_label(zLabel, fontsize = 20, labelpad = 11)

        # norm = colors.TwoSlopeNorm(vmin=vmin, vcenter=0, vmax=vmax)
        # plt.pcolor(X, Y, Z, vmin=vmin, vmax=vmax, norm=norm)   

        # plt.colorbar.set_label("Rec hit time (ns)")

        # plt.ylabel(r'Trigger Tower $\phi$ index', fontsize = 22)
        # plt.xlabel(r'Trigger Tower $\eta$ index', fontsize = 22)

        plt.ylabel(r'Trigger Tower $\eta$ index', fontsize = 22)
        plt.xlabel(r'Trigger Tower $\phi$ index', fontsize = 22)

        upperRightText = "Beam Splash 2021"
        # upperRightText = ""
        # xmin = 0.15
        # Add_CMS_Header(plt, isWide, ax, upperRightText, xmin)
        plt.grid()
        # plt.show()

        plt.xticks(fontsize = 18)
        plt.yticks(fontsize = 18)

        if(v_to_plot == "FineGrainBit"):
        #     xmin = 0.12
            xmin = 0.05
            plt.text(
                0.06, 0.9, u"Towers flagged",
                fontsize=20, fontweight='bold',
                horizontalalignment='left',
                verticalalignment='bottom',
                transform=ax.transAxes
            )    
            Add_CMS_Header(plt, isWide, ax, upperRightText, xmin)
            EB_LABEL_COLOR = "black"
            fig.set_size_inches(16, 8) # time 
        else:
            xmin = 0.06
            EB_LABEL_COLOR = "w"
        #     xmin = 0.15
            fig.set_size_inches(17.5, 8) # time 
            
        Add_CMS_Header(plt, isWide, ax, upperRightText, xmin)

        EB_LABEL_XMIN = 0.06

        plt.text(
        #     EB_LABEL_XMIN, 0.89, u"ECAL Barrel",
            EB_LABEL_XMIN, 0.95, u"ECAL Barrel",
            fontsize=20, fontweight='bold',
            horizontalalignment='left',
            verticalalignment='bottom',
            transform=ax.transAxes, color = EB_LABEL_COLOR
        )     

        fig.tight_layout()
        plt.savefig("%s/BeamSplash%s_%s_Run%s_Event%s.png"%(OUT_DIRECTORY, args.year, v_to_plot, runNumber, event))
        plt.savefig("%s/BeamSplash%s_%s_Run%s_Event%s.pdf"%(OUT_DIRECTORY, args.year, v_to_plot, runNumber, event))
        plt.close()
print("DONE")
