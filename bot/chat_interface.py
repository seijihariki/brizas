#!/usr/bin/python3
import subprocess as proc
from bot import Bot
import readline
import signal
import sys

user = "seiji"
prompt = ":user: > "
proc_timeout = 5

bot = Bot("yo.db", "yo.db") 

running_state = True

# Parses and executes commands
def handle_command(command):
    command = command.split()

    if len(command) < 1:
        return True

    # Parse command
    if command[0] == "exit": # Exits and shutdowns bot
        return False

    elif command[0] == "help": # Show help page
        print ("This the help page! So helpful, don't you think?")
    
    elif command[0] == "set_user": # Changes current user
        if len(command) < 2:
            print ("Usage: set_user <user>")
        else:
            print ("User set to " + command[1])
            global user
            user = command[1]
    
    else: # If no matching command exists, try to run on shell
        print ("Handling command on shell: " + command[0])
        try:
            proc.call(command, timeout=proc_timeout)
        except FileNotFoundError:
            print ("Command '"  + command[0] + "' not found!")
        except proc.TimeoutExpired:
            print ("Command took too long to execute!")

    return True

def make_prompt():
    return prompt.replace(':user:', user)

def shutdown_bot(signal = None, frame = None):
    if signal is not None:
        print()
    print("Now exiting...")
    bot.shutdown()
    sys.exit(0)

def main ():
    # Adding signal handlers...

    signal.signal(signal.SIGINT, shutdown_bot)

    # Wait for input...
    while running_state:
        text = input(make_prompt())
        command = ''

        if len(text) < 1:
            continue

        if text[0] == ':':
            command = text[1:]
            text = ''

        if command == '':
            bot.push_chat(0, [user], user, text)
        else:
            if not handle_command(command):
                shutdown_bot()

main()
