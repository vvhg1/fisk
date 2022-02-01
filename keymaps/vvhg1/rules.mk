# Build Options
#   change yes to no to disable
#
OLED_ENABLE = yes
ENCODER_ENABLE = yes       # ENables the use of one or more encoders

CASEMODES_ENABLE = yes       # ENables case modes
CUSTOM_LEADER_ENABLE = yes       # ENables custom leader function
CUSTOM_LEADER_TO_DL = yes       # makes leader key activate default layer
CUSTOM_ONE_SHOT_ENABLE = yes  # ENables custom one shot modifiers function
CUSTOM_WORD_LINE_SELECTION_ENABLE = yes  # ENables custom one shot modifiers function
POWER_BRACKETS_ENABLE = yes #enables empty or wrapping quote and bracket pairs
EOS_ENABLE = yes #end of sentence

CONSOLE_ENABLE = no        # Console for debug (adds 1152 b)
DYNAMIC_MACRO_ENABLE = no #(adds 548 b)



ifeq ($(strip $(ENCODER_ENABLE)), yes)
	SRC += features/encoder_utils.c
endif

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += features/oled_utils.c
endif
CASEMODES_ENABLE ?= yes       # ENables case modes
ifeq ($(strip $(CASEMODES_ENABLE)), yes)
	OPT_DEFS += -DCASEMODES_ENABLE
	SRC += features/casemodes.c
endif
CUSTOM_LEADER_ENABLE ?= yes       # ENables custom leader function
ifeq ($(strip $(CUSTOM_LEADER_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_LEADER_ENABLE
	OPT_DEFS += -DCUSTOM_LEADER_TO_DL
	SRC += features/leader.c
	SRC += features/leaderfuncs.c
endif
CUSTOM_ONE_SHOT_ENABLE ?= yes       # ENables custom one shot function
ifeq ($(strip $(CUSTOM_ONE_SHOT_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_ONE_SHOT_ENABLE
	SRC += features/custom_oneshot.c
endif
EOS_ENABLE ?= yes       # ENables custom one shot function
ifeq ($(strip $(EOS_ENABLE)), yes)
	OPT_DEFS += -DEOS_ENABLE
	SRC += features/eos_util.c
endif
POWER_BRACKETS_ENABLE ?= yes       # ENables power brackets
ifeq ($(strip $(POWER_BRACKETS_ENABLE)), yes)
	OPT_DEFS += -DPOWER_BRACKETS_ENABLE
	SRC += features/power_brackets.c
endif
CUSTOM_WORD_LINE_SELECTION_ENABLE ?= yes       # ENables power brackets
ifeq ($(strip $(CUSTOM_WORD_LINE_SELECTION_ENABLE)), yes)
	OPT_DEFS += -DCUSTOM_WORD_LINE_SELECTION_ENABLE
	SRC += features/word_line_selection.c
endif


