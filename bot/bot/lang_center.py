#!/usr/bin/python3

import spacy
from spacy.symbols import *

class LanguageCenter():
    # LANGUAGE PROCESSING
    # Returns whether token has another as parent
    def has_parent(self, word, parent):
        if word.head is parent:
            return True
        elif word.head is word:
            return False
        return self.has_parent(word.head, parent)

    # Return all dependents on given word and itself
    def get_dependents(self, doc, word):
        ret = []
        for token in doc:
            if token is word or self.has_parent(token, word):
                ret.append(token)
        return ret

    # Gets children whose dependency relation is on list
    def get_children(self, doc, word, relations):
        children = []
        for token in doc:
            append = False
            for relation in relations:
                if token.dep == relation:
                    append = True

            if token.head is word and append:
                children.append(self.get_dependents(doc, token))
        return children

    # Returns subject expressions of verb
    def get_subject(self, doc, verb):
        return self.get_children(doc, verb,
                [nsubj, csubj, agent])

    # Returns object expressions of verb
    def get_object(self, doc, verb):
        return self.get_children(doc, verb,
                [acomp, xcomp, ccomp, pobj,
                dobj, iobj, nsubjpass, csubjpass, attr])

    # Returns word modifiers
    def get_mods(self, doc, word):
        return self.get_children(doc, word,
                [advmod, npadvmod, prep, advcl])

    # Recursive sentence parser
    def rec_parser(self, doc, used_verbs = []):
        verbs = []
        if len(doc) == 1:
            return doc[0]

        for token in doc:
            if token.pos == VERB and token.dep not in [auxpass, aux] and token not in used_verbs:
                used_verbs.append(token)
                verbs.append((
                    [self.rec_parser(subject, used_verbs) for subject in self.get_subject(doc, token)],
                    (self.get_children(doc, token, [aux, auxpass]), token),
                    [self.rec_parser(obj, used_verbs) for obj in self.get_object(doc, token)],
                    [self.rec_parser(mod, used_verbs) for mod in self.get_mods(doc, token)]
                    ))

        if len(verbs) == 0:
            return doc
        return verbs
