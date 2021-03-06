TOPDIR ?= ..

# convert from lower-case (with punct) to upper with punct -> _
define TOVAR
$(shell echo $(1) | tr '[:lower:]' '[:upper:]' | tr '[:punct:]' _)
endef

define OVERLAY_TEST_RULE
$(strip $(1))-test.dtb: $(strip $(2)).dtb $(strip $(foreach o, $(3), $(o)-overlay.dtb))
	$(FDTOVERLAY) -i $(strip $(2)).dtb \
		      -o $(strip $(1))-test.dtb \
		      $(strip $(foreach o, $(3), $(o)-overlay.dtb))
endef

DRA71_EVM_BASE_BOARD := dra71-evm
DRA71_EVM_LCDS := lcd-auo-g101evn01.0

DRA72_EVM_BASE_BOARD := dra72-evm
DRA72_EVM_REVS := dra72-evm-revc
DRA72_EVM_LCDS := lcd-lg lcd-osd101t2587 lcd-osd
DRA72_EVM_REVC_LCDS := lcd-osd101t2045 lcd-osd101t2587

DRA7_EVM_BASE_BOARD := dra7-evm
DRA7_EVM_LCDS := lcd-lg lcd-osd101t2587 lcd-osd

AM571X_IDK_BASE_BOARD := am571x-idk
AM571X_IDK_LCDS := lcd-osd101t2587 lcd-osd

AM572X_IDK_BASE_BOARD := am572x-idk
AM572X_IDK_LCDS := lcd-osd101t2587 lcd-osd

AM57XX_BEAGLE_X15_BASE_BOARD := am57xx-beagle-x15
AM57XX_BEAGLE_X15_REVS := am57xx-evm am57xx-evm-reva3

# This is not based on -x15 as expected
AM57XX_BEAGLE_X15_REVB1_BASE_BOARD := am57xx-beagle-x15-revb1

# Get all boards variables from finding out which end in _BASE_BOARD
BASE_BOARD_NAMES := $(sort $(patsubst %_BASE_BOARD, %, \
		    $(filter %_BASE_BOARD, $(.VARIABLES))))

# Get all boards
BASE_BOARDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), $(value $(b)_BASE_BOARD)))
BASE_BOARD_DTBS := $(sort $(foreach b, $(BASE_BOARDS), $(b).dtb))

# Get the rev board name
REV_BOARDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), \
			$(foreach l, $(value $(b)_REVS), $(l))))
REV_BOARD_DTBS := $(sort $(foreach b, $(REV_BOARDS), $(b)-overlay.dtb))

REV_BOARD_NAMES := $(sort $(foreach b, $(REV_BOARDS), $(call TOVAR, $(b))))

# Get the names of the lcds from each $(BOARD)_LCDS
BASE_LCDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), $(value $(b)_LCDS)))
REV_LCDS := $(sort $(foreach b, $(REV_BOARD_NAMES), $(value $(b)_LCDS)))
LCDS := $(sort $(BASE_LCDS) $(REV_LCDS))

# Get the lcb board name
LCD_BASE_BOARDS := $(sort $(foreach b, $(BASE_BOARD_NAMES), \
			$(foreach l, $(value $(b)_LCDS), \
				$(value $(b)_BASE_BOARD)-$(l))))
LCD_REV_BOARDS := $(sort $(foreach b, $(REV_BOARDS), \
			$(foreach l, $(value $(call TOVAR, $(b))_LCDS), \
					$(b)-$(l))))
LCD_BOARDS := $(sort $(LCD_BASE_BOARDS) $(LCD_REV_BOARDS))
LCD_BOARD_DTBS := $(sort $(foreach b, $(LCD_BOARDS), $(b)-overlay.dtb))

REV_BOARDS_TEST := $(sort $(foreach b, $(REV_BOARDS), $(b)-test.dtb))

ALL_DTBS := $(BASE_BOARD_DTBS) $(REV_BOARD_DTBS) $(LCD_BOARD_DTBS)

# $(info BASE_BOARD_NAMES = $(BASE_BOARD_NAMES))
# $(info BASE_BOARD_DTBS  = $(BASE_BOARD_DTBS))
# $(info REV_BOARDS       = $(REV_BOARDS))
# $(info REV_BOARD_DTBS   = $(REV_BOARD_DTBS))
# $(info LCDS             = $(LCDS))
# $(info LCD_BOARD_DTBS   = $(LCD_BOARD_DTBS))
# $(info ALL_DTBS         = $(ALL_DTBS))

all: $(ALL_DTBS)

include $(TOPDIR)/Makefile.inc

TEST_DTBS := 

# REVs on top of base boards
$(foreach b, $(BASE_BOARD_NAMES), \
	$(foreach r, $(value $(b)_REVS), \
		$(eval $(call OVERLAY_TEST_RULE, $(r), \
			$(value $(b)_BASE_BOARD), $(r)) \
		 ) \
		 $(eval TEST_DTBS += $(r)-test.dtb) \
	 )\
 )

# LCDs on base boards
$(foreach b, $(BASE_BOARD_NAMES), \
	$(foreach l, $(value $(b)_LCDS), \
		$(eval $(call OVERLAY_TEST_RULE, \
			$(value $(b)_BASE_BOARD)-$(l), \
			$(value $(b)_BASE_BOARD), \
			$(value $(b)_BASE_BOARD)-$(l)) \
		 ) \
		 $(eval TEST_DTBS += $(value $(b)_BASE_BOARD)-$(l)-test.dtb) \
	 ) \
 )

# LCDs on top of rev boards
$(foreach b, $(BASE_BOARD_NAMES), \
	$(foreach r, $(value $(b)_REVS), \
		$(foreach l, $(value $(call TOVAR, $(r))_LCDS), \
			$(eval $(call OVERLAY_TEST_RULE, $(r)-$(l), \
				$(value $(b)_BASE_BOARD), $(r) $(r)-$(l)) \
			 ) \
			$(eval TEST_DTBS += $(r)-$(l)-test.dtb) \
		 ) \
	 ) \
 )

.PHONY: test

test: $(TEST_DTBS)

.PHONY: info

info:
	@echo "BASE_BOARD_NAMES = $(BASE_BOARD_NAMES)"
	@echo "BASE_BOARDS      = $(BASE_BOARDS)"
	@echo "BASE_BOARD_DTBS  = $(BASE_BOARD_DTBS)"
	@echo "REV_BOARDS       = $(REV_BOARDS)"
	@echo "REV_BOARD_DTBS   = $(REV_BOARD_DTBS)"
	@echo "LCDS             = $(LCDS)"
	@echo "LCD_BASE_BOARDS  = $(LCD_BASE_BOARDS)"
	@echo "REV_BOARD_NAMES  = $(REV_BOARD_NAMES)"
	@echo "LCD_REV_BOARDS   = $(LCD_REV_BOARDS)"
	@echo "LCD_BOARDS       = $(LCD_BOARDS)"
	@echo "LCD_BOARD_DTBS   = $(LCD_BOARD_DTBS)"
	@echo "REV_BOARDS_TEST  = $(REV_BOARDS_TEST)"
	@echo "ALL_DTBS         = $(ALL_DTBS)"
	@echo "TEST_DTBS        = $(TEST_DTBS)"
