#!/usr/bin/python3
import subprocess as proc
from tkinter import *
from tkinter.scrolledtext import ScrolledText
from bot.bot import Bot
import readline
import signal
import sys

class chat_if_g(Frame):
    def __init__(self, tk_instance=Tk(), bot=Bot("db/yo.db", "db/yo.db"), user="seiji"):
        super().__init__(tk_instance)
        self.tk_instance = tk_instance

        self.tk_instance.protocol("WM_DELETE_WINDOW", lambda: self.shutdown())
        self.tk_instance.resizable(0,0)

        self.user = user
        self.bot = bot
        self.chat_id = 0

        self.proc_timeout = 5

        self.pack()
        self.createWidgets()
        self.MESSAGE_BOX.focus()

        self.tk_instance.after(10, self.get_bot_messages)
        self.mainloop()

    def shutdown(self):
        self.bot.shutdown()
        self.tk_instance.destroy()

    def handle_command(self, command):
        command = command.split()

        shell_usr = 'shell'

        if len(command) < 1:
            return True

        # Parse command
        if command[0] == "x":
            self.shutdown()
            return False

        elif command[0] == "help": # Show help page
            self.talk (shell_usr, "This the help page! So helpful, don't you think?")

        elif command[0] == "set_user": # Changes current user
            if len(command) < 2:
                self.talk (shell_usr, "Usage: set_user <user>")
            else:
                self.talk (shell_usr, "User set to " + command[1])
                self.user = command[1]

        else: # If no matching command exists, try to run on shell
            self.talk (shell_usr, "Handling command on shell: " + command[0])
            try:
                self.talk (shell_usr, "\n" + proc.check_output(command,
                    timeout=self.proc_timeout).decode('utf-8'))
            except FileNotFoundError:
                self.talk (shell_usr, "Command '"  + command[0] + "' not found!")
            except proc.TimeoutExpired:
                self.talk (shell_usr, "Command took too long to execute!")
        return True

    def createWidgets(self):
        self.CHAT_VIEWER = ScrolledText(self)
        self.CHAT_VIEWER.config(state=DISABLED)
        self.CHAT_VIEWER.pack(expand=True)
        self.CHAT_VIEWER.insert(END, "This is a test\n")

        self.MESSAGE_BOX = Entry(self)
        self.MESSAGE_BOX.pack(expand=True, fill=X, side=LEFT)
        self.MESSAGE_BOX.bind("<Return>", lambda x: self.send_message())

        self.SEND_BUTTON = Button(self, text="SEND", command=self.send_message)
        self.SEND_BUTTON.pack(side=RIGHT)

    def get_bot_messages(self):
        while self.bot.has_chat(self.chat_id):
            self.talk('Bot', self.bot.pop_chat(self.chat_id))
        self.tk_instance.after(10, self.get_bot_messages)
        
    def send_message(self):
        message = self.MESSAGE_BOX.get()
        command = ''

        if len(message) < 1:
            return

        if message[0] == ':':
            command = message[1:]
            message = ''

        if command == '':
            self.bot.push_chat(0, [self.user], self.user, message)
            self.talk(self.user, message)
        else:
            if not self.handle_command(command):
                return
        
        self.MESSAGE_BOX.delete(0, END)

    def talk(self, sender, message):
        self.CHAT_VIEWER.config(state=NORMAL)
        self.CHAT_VIEWER.insert(END, sender + " > " + message + "\n")
        self.CHAT_VIEWER.see("end")
        self.CHAT_VIEWER.config(state=DISABLED)

teste = chat_if_g()
