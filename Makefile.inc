#
# Leaf makefile for 
#

.SUFFIXES:

CPP ?= cpp
CPPFLAGS ?= -I ./ -I $(TOPDIR)/dts \
	 -I $(TOPDIR)/include \
	 -I $(TOPDIR)/include/dt-bindings/input \
	 -nostdinc -undef -D__DTS__ -x assembler-with-cpp
DTC ?= dtc
DTCFLAGS ?= -q -@
FDTDUMP ?= fdtdump
YAMLDT ?= yamldt
DTS2YAML ?= dts2yaml
FDTOVERLAY ?= fdtoverlay

# pass extra validate flags
YAMLDTFLAGS ?= -C \
	$(if $(findstring validate, $(MAKECMDGOALS)), \
		-g $(TOPDIR)/validate/schema/codegen.yaml -S $(TOPDIR)/validate/bindings/)

DTS2YAMLFLAGS ?=
FDTDUMPFLAGS ?=

YAMLS    := $(addsuffix .yaml, $(filter-out $(basename $(BLACKLIST)),$(basename $(BOARDS))))
DTSS     := $(addsuffix .dts, $(filter-out $(basename $(BLACKLIST)),$(basename $(BOARDS))))
DTCYAMLS := $(addsuffix .dtc.yaml, $(basename $(BOARDS)))
DIFFS    := $(addsuffix .diff, $(basename $(YAMLS)))
DTBS     := $(addsuffix .dtb, $(basename $(YAMLS)))
YAMLDTBS := $(addsuffix .yaml.dtb, $(basename $(YAMLS)))
FDTDUMPS := $(addsuffix .fdtdump, $(basename $(DTBS))) $(addsuffix .fdtdump, $(basename $(YAMLDTBS)))
CPPS     := $(addsuffix .cpp, $(basename $(DTBS))) $(addsuffix .yaml.cpp, $(basename $(YAMLDTBS)))

BLACKYAMLS    := $(addsuffix .yaml, $(BLACKLIST))
BLACKDTSS     := $(addsuffix .dts, $(BLACKLIST))
BLACKDIFFS    := $(addsuffix .diff, $(BLACKLIST))

%.diff: %.yaml.fdtdump %.fdtdump
	cmp -s $^ || (diff -u $^ | tee $@; false)

%.cpp.dts: %.dts
	$(CPP) $(CPPFLAGS) $< > $@

%.cpp.yaml: %.yaml
	$(CPP) $(CPPFLAGS) $< > $@

%.dtb: %.dts
	$(CPP) $(CPPFLAGS) $< | $(DTC) $(DTCFLAGS) -I dts -O dtb - -o $@

%.yaml.dtb: %.yaml | genyamls
	$(CPP) $(CPPFLAGS) $^ | $(YAMLDT) $(YAMLDTFLAGS) - -o $@

%.dtc.yaml: %.dts
	$(CPP) $(CPPFLAGS) $< | $(DTC) $(DTCFLAGS) -I dts -O yaml - -o $@

# will also generate all yamli included files
# %.yaml: %.dts
#	$(DTS2YAML) $(DTS2YAMLFLAGS) -r $^

%.fdtdump: %.dtb
	$(FDTDUMP) $(FDTDUMPFLAGS) 2>/dev/null $< >$@

.PHONY: clean check genyamls genblackyamls checkblack

# .NOTPARALLEL:

check: $(DIFFS)

clean:
	find ./ -name '*.diff' -print | xargs rm -f
	find ./ -name '*.fdtdump' -print | xargs rm -f
	find ./ -name '*.dtb' -print | xargs rm -f
	find ./ -name '*.yaml' -print | xargs rm -f
	find ./ -name '*.yamli' -print | xargs rm -f
	rm -f *.cpp.yaml *.cpp.dts

$(YAMLS): $(DTSS)
$(YAMLS): genyamls

genyamls:
	$(DTS2YAML) $(DTS2YAMLFLAGS) -r $(DTSS) || true
	@echo "dts2yaml DONE"

checkblack: $(BLACKDIFFS)

genblackyamls:
	$(DTS2YAML) $(DTS2YAMLFLAGS) -r $(BLACKDTSS) || true
	@echo "dts2yaml DONE"

validate: check
