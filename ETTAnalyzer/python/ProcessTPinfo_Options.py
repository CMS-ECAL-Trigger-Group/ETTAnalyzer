import argparse 

def GetOptions():
    parser = argparse.ArgumentParser()

    ##-- Misc
    parser.add_argument('--outLoc', type=str, default="", help="Output location for plots", required=False)
    # parser.add_argument('--boolFlag', action="store_true", default=False, help="", required=False)

    args = parser.parse_args()
    return args