scriptname = "FunkAnaGloss.tex"

script = open(scriptname,"r")
output = open("gloss.txt","w")

for line in script:
    if line.find("newglossaryentry") == 1:
        output.write(line)

