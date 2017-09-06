TOPDIR ?= ..

DRA71_EVM_BASE_BOARD := dra71-evm
DRA71_EVM_LCDS := lcd-auo-g101evn01.0

DRA72_EVM_BASE_BOARD := dra72-evm
DRA72_EVM_LCDS := lcd-lg lcd-osd101t2587 lcd-osd

DRA72_EVM_REVC_BASE_BOARD := dra72-evm-revc
DRA72_EVM_REVC_LCDS := lcd-osd101t2045 lcd-osd101t2587

DRA7_EVM_BASE_BOARD := dra7-evm
DRA7_EVM_LCDS := lcd-lg lcd-osd101t2587 lcd-osd

AM571X_IDK_BASE_BOARD := am571x-idk
AM571X_IDK_LCDS := lcd-osd101t2587 lcd-osd

AM572X_IDK_BASE_BOARD := am571x-idk
AM572X_IDK_LCDS := lcd-osd101t2587 lcd-osd

# Get all boards variables from finding out which end in _BASE_BOARD
BASE_BOARD_NAMES := $(sort $(patsubst %_BASE_BOARD, %, \
		    $(filter %_BASE_BOARD, $(.VARIABLES))))

# Get all boards
BASE_BOARDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), $(value $(b)_BASE_BOARD)))
BASE_BOARD_DTBS := $(sort $(foreach b, $(BASE_BOARDS), $(b).dtb))

LCDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), $(value $(b)_LCDS)))
LCD_DTBS := $(sort $(foreach b, $(LCDS), $(b).dtbo))

LCD_BOARD_NAMES := $(sort $(foreach b, $(BASE_BOARD_NAMES), \
			$(foreach l, $(value $(b)_LCDS), \
				$(value $(b)_BASE_BOARD)-$(l))))
LCD_BOARD_DTBS := $(sort $(foreach b, $(LCD_BOARD_NAMES), $(b)-overlay.dtb))

ALL_DTBS := $(BASE_BOARD_DTBS) $(LCD_BOARD_DTBS)

# $(info BASE_BOARD_NAMES = $(BASE_BOARD_NAMES))
# $(info BASE_BOARD_DTBS  = $(BASE_BOARD_DTBS))
# $(info LCDS             = $(LCDS))
# $(info LCD_DTBS         = $(LCD_DTBS))
# $(info LCD_BOARD_DTBS   = $(LCD_BOARD_DTBS))
# $(info ALL_DTBS         = $(ALL_DTBS))

all: $(ALL_DTBS)

include $(TOPDIR)/Makefile.inc

.PHONY: info

info:
	@echo "BASE_BOARD_NAMES = $(BASE_BOARD_NAMES)"
	@echo "BASE_BOARD_DTBS  = $(BASE_BOARD_DTBS)"
	@echo "LCDS             = $(LCDS)"
	@echo "LCD_DTBS         = $(LCD_DTBS)"
	@echo "LCD_BOARD_DTBS   = $(LCD_BOARD_DTBS)"
	@echo "ALL_DTBS         = $(ALL_DTBS)"


