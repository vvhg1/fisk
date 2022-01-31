# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite (adds 40 b)
OLED_ENABLE = yes
OLED_DRIVER = SSD1306      # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders

MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control (adds 470 b)
CONSOLE_ENABLE = yes        # Console for debug (adds 1152 b)
COMMAND_ENABLE = no        # Commands for debug and configuration (adds 408 b)
NKRO_ENABLE = yes          # Enable N-Key Rollover (adds 390 b)
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
AUDIO_ENABLE = no          # Audio output
SPLIT_KEYBOARD = yes       # Split common
LTO_ENABLE = yes

# DEFAULT_FOLDER = fisk

RGBLIGHT_ENABLE = no       # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)
RGB_MATRIX_SUPPORTED = no

SWAP_HANDS_ENABLE = yes   # Enables one hand typing via mirroring (adds 330 b)

LEADER_ENABLE = no        # Enable the Leader Key feature (adds 352 b)
SPACE_CADET_ENABLE = no    # Disable Space Cadet Shift
GRAVE_ESC_ENABLE = no      # Disable Grave Escape



# WPM_ENABLE = yes           # Enable WPM Counter (Works with default wpm files, but works better with vectorstorm updated wpm.c and wpm.h -> https://github.com/vectorstorm/qmk_firmware/tree/wpm_exact)
# KEY_OVERRIDE_ENABLE = yes  # Enable Key Overrides

# DEBOUNCE_TYPE = sym_eager_pk

# flags for reducing size
EXTRAFLAGS += -flto

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
