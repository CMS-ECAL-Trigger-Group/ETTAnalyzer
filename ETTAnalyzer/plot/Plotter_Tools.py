"""
12 April 2022
Abraham Tishelman-Charny 

The purpose of this module is to provide tools for the BeamSplashes_2021 module 
"""

##-- CMS header 
def Add_CMS_Header(plt, isWide, ax, upperRightText, xmin):
    ##-- Upper left plot text
    ##-- CMS 
    plt.text(
        # 0.05, 0.9, u"CMS $\it{Preliminary}$",
        0., 1., u"CMS ",
        fontsize=20, fontweight='bold',
        horizontalalignment='left',
        verticalalignment='bottom',
        transform=ax.transAxes
    )

    prelim_x = xmin
    
#     if(isWide):
#         prelim_x = 0.08
#     else:
#         prelim_x = 0.115
#         prelim_x = 0.135
    
    ##-- Preliminary 
    plt.text(
#         prelim_x, 0.998, u"$\it{Simulation}$ $\it{Preliminary}$",
        prelim_x, 0.998, u"$\it{Preliminary}$",
#         prelim_x, 0.998, u"$\it{Work}$ $\it{In}$ $\it{Progress}$",
        fontsize=19,
        horizontalalignment='left',
        verticalalignment='bottom',
        transform=ax.transAxes
    )    

    ##-- Lumi 
    plt.text(
#         1., 1., r"%s fb$^{-1}$ (13 TeV)"%(lumi),
#         1., 1., "(13 TeV)",
#         1., 1., "(14 TeV)",
        1., 1., upperRightText,
        fontsize=16, horizontalalignment='right', 
        verticalalignment='bottom', 
        transform=ax.transAxes
    )  


def GetPathDict():
    MAIN_DIREC = "/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/ETTAnalyzerOutput/ReEmulation/"

    f_path_dict = {

        "0p5" : {
            "Tagging" : "%s/ETTAnalyzer_output_TPModeTagging_Weights0p5.root"%(MAIN_DIREC),
            "Killing" : "%s/ETTAnalyzer_output_TPModeKilling_Weights0p5.root"%(MAIN_DIREC),
            "KillNTag" : "%s/ETTAnalyzer_output_TPModeKillNTag_Weights0p5.root"%(MAIN_DIREC)
        },

        "2p5" : {
            "Tagging" : "%s/ETTAnalyzer_output_TPModeTagging_Weights2p5.root"%(MAIN_DIREC),
            "Killing" : "%s/ETTAnalyzer_output_TPModeKilling_Weights2p5.root"%(MAIN_DIREC),
            "KillNTag" : "%s/ETTAnalyzer_output_TPModeKillNTag_Weights2p5.root"%(MAIN_DIREC)
        },

    }    

    # f_path_dict = {

    #     "0p5" : {
    #         "Tagging" : "/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/ETTAnalyzerOutput/ReEmulation/2021Splashes_Run_346050_ReEmulated0p5primeweights_TaggingMode.root",
    #         "Killing" : "",
    #         "TagAndKill" : ""
    #     },

    #     "2p5" : {
    #         "Tagging" : "/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/ETTAnalyzerOutput/ReEmulation/2021Splashes_Run_346050_ReEmulated2p5primeweightsTaggingMode.root",
    #         "Killing" : "/eos/cms/store/group/dpg_ecal/alca_ecalcalib/Trigger/2021BeamSplashes/ETTAnalyzerOutput/ReEmulation/2021Splashes_Run_346050_ReEmulated2p5primeweights_KillingMode.root",
    #         "TagAndKill" : ""
    #     }

    # }    

    return f_path_dict