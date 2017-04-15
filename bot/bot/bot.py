#!/usr/bin/python3

import sqlite3 as sql
import os.path
import time
import threading
import spacy
from queue import Queue

nlp = spacy.load('en_core_web_md')

class Bot(object):
    def __init__(self, bot_mem_file, bot_person_file, update_time = .1):
        assert os.path.isfile(bot_mem_file)
        assert os.path.isfile(bot_person_file)

        self.running_stage = True

        self.bot_mem = sql.connect(bot_mem_file)
        self.bot_person_db = sql.connect(bot_person_file)
        self.update_time = update_time
        self.in_message_queue = Queue()
        self.out_message_queues = {}

        self.load_personality(self.bot_person_db)

        self.update_cycle()

    # Load bot personality traits from dabatase
    def load_personality(self, personality_db):
        return

    # Returns whether there is a message from the bot to the specified chat
    def has_chat(self, chat):
        if chat in self.out_message_queues:
            return not self.out_message_queues[chat].empty()
        return False

    # Returns oldest message from bot to the chat specified
    def pop_chat(self, chat):
        if chat in self.out_message_queues:
            return self.out_message_queues[chat].get()
        return None

    # Adds chat for processing
    def push_chat(self, chat, people_on_chat, source, message):
        if chat not in self.out_message_queues:
            self.out_message_queues[chat] = Queue()
        self.in_message_queue.put((chat, people_on_chat, source, message, time.time()))

    # For use of the bot: Adds a message to the output buffer
    def answer(self, chat, message):
        if chat not in self.out_message_queues:
            self.out_message_queues[chat] = Queue()
        self.out_message_queues[chat].put(message)

    # Stop bot thread
    def shutdown(self):
        self.running_stage = False

    # Processes language-based information
    def process_message(self, message):
        doc = nlp(message[3])
        vec = []
        self.answer(message[0], str(vec))
        return

    # Is like the 'clock' of the mind of the bot. Each cycle processes a limited
    # amount of data.
    def update_cycle(self):
        now = time.time()

        # Message processing

        message = None

        # Process maximum of one message for each update cycle
        if not self.in_message_queue.empty():
            message = self.in_message_queue.get()

        # Process message - that is, filter relevant content and put it into
        # short-term memory for further information processing
        if message is not None:
            self.process_message(message)

        # AI Processing - Decides the Bot's actions and processes thoughts. This
        # is where logical courses of action are decided and rated, from
        # knowledge of the current context (short-term memory) and past
        # knowledge + research results (long-term memory)

        

        # AI emotion - Applies emotional filters on the bot's possible courses
        # of action, decisions and thoughts, based on personality traits



        # Output generation - Generates output (chat answers), executes
        # actions, and moves things around the memories, possibly preparing for
        # the next update cycle



        # Schedules next processing cycle
        if self.running_stage:
            threading.Timer(self.update_time, self.update_cycle).start()
