TOPDIR ?= ..

BOARDS := \
	am571x-idk.dts \
	am571x-idk-lcd-osd101t2587.dts \
	am571x-idk-lcd-osd.dts \
	am571x-idk-pru-excl-uio.dts \
	am572x-idk.dts \
	am572x-idk-lcd-osd101t2587.dts \
	am572x-idk-lcd-osd.dts \
	am572x-idk-pru-excl-uio.dts \
	am57xx-beagle-x15.dts \
	am57xx-beagle-x15-revb1.dts \
	am57xx-evm.dts \
	am57xx-evm-reva3.dts \
	am57xx-evm-reva3-no-cmem.dts \
	dra71-evm.dts \
	dra71-evm-lcd-auo-g101evn01.0.dts \
	dra72-evm.dts \
	dra72-evm-lcd-lg.dts \
	dra72-evm-lcd-osd101t2587.dts \
	dra72-evm-lcd-osd.dts \
	dra72-evm-revc.dts \
	dra72-evm-revc-lcd-osd101t2045.dts \
	dra72-evm-revc-lcd-osd101t2587.dts \
	dra7-evm.dts \
	dra7-evm-lcd-lg.dts \
	dra7-evm-lcd-osd101t2587.dts \
	dra7-evm-lcd-osd.dts

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

LCD_BOARDS := DRA71_EVM DRA72_EVM DRA72_EVM_REVC DRA7_EVM AM571X_IDK AM572X_IDK

BASE_LCD_BOARDS := $(sort $(foreach b, $(LCD_BOARDS), $(value $(b)_BASE_BOARD)))
BASE_LCD_BOARDS_DTBS := $(sort $(foreach b, $(BASE_LCD_BOARDS), $(b).dtb))

LCDS := $(sort $(foreach b, $(LCD_BOARDS), $(value $(b)_LCDS)))
LCD_DTBOS := $(sort $(foreach b, $(LCDS), $(b).dtbo))

LCD_BOARDS_TEST := $(sort $(foreach b, $(LCD_BOARDS), \
			$(foreach l, $(value $(b)_LCDS), \
				$(value $(b)_BASE_BOARD)-$(l))))
LCD_BOARDS_TEST_DTBS := $(sort $(foreach b, $(LCD_BOARDS_TEST), $(b).dtb))

DTBS := $(BASE_LCD_BOARDS_DTBS) $(LCD_BOARDS_TEST_DTBS)
DTBOS := $(LCD_DTBOS)

$(info LCD_BOARDS=$(LCD_BOARDS))
$(info BASE_LCD_BOARDS_DTBS=$(BASE_LCD_BOARDS_DTBS))
$(info LCDS=$(LCDS))
$(info LCD_DTBOS=$(LCD_DTBOS))
$(info $(F))
$(info LCD_BOARDS_TEST=$(LCD_BOARDS_TEST))

all: $(DTBS)

include $(TOPDIR)/Makefile.inc

.PHONY: test

test:
	@echo nothing


