import re

def write2outputfrom2 (startword,endword,inputfile, outputfile):
    i = 0 
    j = 0
    for line in inputfile:
        j = j+1
        if i == 0:
            if line.find(startword) != -1:
                outputfile.write(line)
                i = 1
        elif line.find(endword) == -1:
            outputfile.write(line)
        else:
            outputfile.write("\n")
            break

scriptname = "FunkAnaSkriptSS2017.tex"
#keyword1 = "definition"
keyword1 = "thm"
modus = "thm"

outputname = "flashcards." + keyword1 + ".tex"

keyword2 = "lemma"
keyword3 = "cor"
#keyword4 = cor*
numberofkeywords = 3 #starting counting by 0

Listofkeywords = []
for i in range(1,numberofkeywords+1):
    Listofkeywords.append(locals()['keyword'+str(i)])     

script = open(scriptname,"r")
output = open(outputname,"w")

output.write("\\documentclass[a6paper,10pt,print,grid=both]{kartei}\n\n")

headerselection = [("language settings","pdf page settings"),("more features for","marginnote"),("math environments","nothm"),("Macros","tables and lists")]

for x in headerselection:
    write2outputfrom2(x[0],x[1],script,output)

output.write("\n")
output.write("%%Neudefinition der Karten\n")
output.write("\\antwort{}\n")
output.write("\\renewcommand{\\theCardID}{}\n")
output.write("\setheadsepline{0pt}[\color{black}]\n")
output.write("\\renewcommand{\\fachstil}{\\textsc}\n")
output.write("\\renewcommand{\kommentarstil}{\\textsc}\n\n")

todos = ['r','o','y','g']
for x in todos:
    output.write("\\renewcommand{\\todo"+x+"}{}\n")
output.write("\n")

if modus != "thm":
    for keyword in Listofkeywords:
        output.write("\\newenvironment{"+keyword+"}[1][]{\\begin{karte}["+keyword+"]{#1}}{\end{karte}}\n\n")
else:
    for keyword in Listofkeywords:
        output.write("\\newenvironment{"+keyword+"}[2][]{\\begin{karte}[#1]{#2}}{\end{karte}}\n\n")

output.write("\\small\n\n")

i = 0
for keyword in Listofkeywords:
    script.seek(0)
    line = script.readline()
    script.seek(0)
    while line.find("\\end{document}") == -1:
        line=script.readline()
        if line.find("\\begin{"+keyword+"}") != -1:
            i = 1
            output.write(line)
            # Braucht man um den Satz nach vorne zu holen
            if modus == "thm":    
                output.write("{")
        elif line.find("\\end{"+keyword+"}") != -1:
            i = 0
            # Braucht man um den Satz nach vorne zu holen
            if modus == "thm":    
                output.write("} Beweis \n")
            output.write(line)
            output.write("\n")
        elif i == 1:
            output.write(line)

output.write("\n \\end{document}")
