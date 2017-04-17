#!/usr/bin/python3

# Class for representing the bot's short term memory
class ShortTermMemory():
    def __init__(self, long_term, storage_size = 6):
        self.long_term_memory = long_term
        self.item_storage_size = storage_size
    
    # Retrieves data related to a subject
    # Returns None if no data related was found
    def get_data(self, subject):
        print ("Retrieving data from STM on " + str(subject))

    # Retrieves data from Long Term memory
    # Returs True if successful, or False if
    # no related data was found on Long Term memory
    def ret_long(self, subject):
        print ("Retrieving data from LTM on " + str(subject))

# Class for representing its long term memory
class LongTermMemory():
    def __init__(self):
        print (7)
