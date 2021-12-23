import tkinter as tk
from tkinter import *
from tkinter import filedialog, Text
import os
from tkinter.font import Font
from tkinter.messagebox import *
import time
from subprocess import Popen, PIPE


image1=''
main = Tk()
dir_path = os.path.dirname(os.path.realpath(__file__))
cwd = os.getcwd()
print(cwd)
os.chdir(dir_path)
main.bold_font = Font(family="Helvetica", size=14, weight="bold")
main.title("Compiler")
main.minsize(1300, 670)
main.maxsize(1300, 670)
main.labelFrame = Label(main, text = "Welcome to Notebook", font=('Impact', -20), bg='#000', fg='#000')
main.labelFrame.place(relx = 0.5,
                   rely = 0.2,
                   anchor = 'center')
main.configure(background='#dfdddd')
main.labelFrame.configure(background='#dfdddd')

def executeme():
    yourfile=filedialog.askopenfilenames(title = "Select your file")
    for i in yourfile:
        commands = f'''cd {dir_path}
        set Path=C:\\MinGW\\bin;%PATH%
        gcc -o 180104042.exe 180104042.c
        "{dir_path}\\180104042.exe" 2 "{i}"
        ''' #you can use " " for 1 line of commands or '''  ''' for several lines
        #Single quotation marks won't do in that case. You have to add quotation marks around each path and also enclose the whole command in quotation marks:
    process = Popen("cmd.exe", shell=False, universal_newlines=True, stdin=PIPE, stdout=PIPE, stderr=PIPE)

    out, err = process.communicate(commands)
    Label(main, text = str(out), font=('Impact', -15),borderwidth=1, relief="raised", fg='#000').grid(column= 0, row = 1)
    print(out)

def signinme():
    third_face_recognition.testme()



def execute():
        main.showoriginal = Button(main, text = "Execute",command = executeme)
        main.showoriginal.configure(background='#df4759',font=('Impact', -20),fg='#fff')
        main.showoriginal.place(relx = 0.37,
                           rely = 0.5,
                           anchor = 'center')

def signin():
        main.showoriginal = Button(main, text = "Sign-in",command = signinme)
        main.showoriginal.configure(background='#42ba96',font=('Impact', -20),fg='#fff')
        main.showoriginal.place(relx = 0.63,
                           rely = 0.5,
                           anchor = 'center')

execute()
signin()
main.mainloop()
