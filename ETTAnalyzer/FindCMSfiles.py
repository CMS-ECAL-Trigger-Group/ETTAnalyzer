import os 

##-- want a text file with a line for each file in datasets:
## /ZeroBias/Run2018C-v1/RAW#162eb239-00fd-4f18-a0ba-58e02f83a1c0
## /ZeroBias/Run2018C-v1/RAW#88bfc4ee-4270-48d6-8127-a86a15ba3094
## /ZeroBias/Run2018C-v1/RAW#e0cfe3d4-0e42-4448-9a4f-6a421c827a99

##-- Corresponding to all of the zerobias files in runs:
##-- 320038-40 and 320061-65

# /ZeroBias/Run2018C-v1/RAW#0a6d726b-89e4-4788-9a28-c4b0e35624cb
# /ZeroBias/Run2018C-v1/RAW#3edccfe4-a9d0-40e1-91d9-479e27bff58f
# /ZeroBias/Run2018C-v1/RAW#51fdc41d-55c7-4a0e-84e3-1ce04a362fc1
# /ZeroBias/Run2018C-v1/RAW#b4e1aae6-a3cc-4f22-934d-5ba98d7cd14a
# /ZeroBias/Run2018C-v1/RAW#f35c0a4f-018a-498d-961e-14b8267a36a2
# /ZeroBias/Run2018C-v1/RAW#7f502fc1-1ab8-4ff3-b466-53a940940cbe
# /ZeroBias/Run2018C-v1/RAW#f243d23a-3995-4377-b73b-37a18a38fe96
# /ZeroBias/Run2018C-v1/RAW#417eb58d-3b07-4e4d-ab25-334a97049e0b

# runs = [320038, 320039, 320040, 320061, 320062, 320063, 320064, 320065]

##-- Total recorded luminosity: 6.421370797 fb-1 
blocks = [  "#162eb239-00fd-4f18-a0ba-58e02f83a1c0",
            "#88bfc4ee-4270-48d6-8127-a86a15ba3094",
            "#e0cfe3d4-0e42-4448-9a4f-6a421c827a99",

            "#0a6d726b-89e4-4788-9a28-c4b0e35624cb",
            "#3edccfe4-a9d0-40e1-91d9-479e27bff58f",
            "#51fdc41d-55c7-4a0e-84e3-1ce04a362fc1",
            "#b4e1aae6-a3cc-4f22-934d-5ba98d7cd14a",
            "#f35c0a4f-018a-498d-961e-14b8267a36a2",
            "#7f502fc1-1ab8-4ff3-b466-53a940940cbe",
            "#f243d23a-3995-4377-b73b-37a18a38fe96",
            "#417eb58d-3b07-4e4d-ab25-334a97049e0b"
]

allRuns = [] 

for i, block in enumerate(blocks):
    print("On block:",block)
    # COMMAND = "dasgoclient --query='file dataset=/ZeroBias/Run2018C-v1/RAW run=%s' >> Files_Run_%s.txt"%(run, run)
    os.system("rm Files_Block_%s.txt"%(i))
    os.system("rm Runs_Block_%s.txt"%(i))
    # COMMAND = "dasgoclient --query='file block=/ZeroBias/Run2018C-v1/RAW%s' >> Files_Block_%s.txt"%(block, i)
    COMMAND = "dasgoclient --query='run block=/ZeroBias/Run2018C-v1/RAW%s' >> Runs_Block_%s.txt"%(block, i)
    os.system(COMMAND)

    text_file_path = "Runs_Block_%s.txt"%(i)
    with open(text_file_path) as f: 
        content = f.readlines()
        content = [x.strip() for x in content] 
        # print("content:",content)
        for blockRuns in content:
            print("blockRuns:",blockRuns)
            v = eval(blockRuns)
            # exec("theseRuns = blockRuns")
            for val in v:
                allRuns.append(val)
            # allRuns.append(file)     

print(allRuns)

totalLumi = 0.

numRuns = len(allRuns)
for run_i, run in enumerate(allRuns):
    print("On run %s of %s"%(run_i+1, numRuns))
    os.system("rm tmp_file.txt")
    command = "brilcalc lumi -c web -r %s -u /fb >> tmp_file.txt"%(run)
    os.system(command)

    with open("tmp_file.txt") as f: 
        content = f.readlines()
        content = [x.strip() for x in content] 
        # print("content:",content)
        for line in content:
            if str(run) in line:
                # print("line:",line)
                vals = line.split()
                lumi = float(vals[-2])
                totalLumi += lumi 
                # print("")
                # print("vals[-2]",vals[-2])

print("totalLumi:",totalLumi)
